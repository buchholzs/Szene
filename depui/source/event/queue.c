#include "depui/config.h"
#include "depui/macros.h"
#include "depui/debug/alloc.h"
#include "depui/event/queue.h"
#include "depui/desktop/desktop.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include <time.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxEventQueueConstruct(void)
{
	 Mx.queue.qevent = 0;
	 Mx.queue.count = 0;

	 MxRegionConstruct(&Mx.queue.dirtyinvert);
	 MxRegionAddRect(&Mx.queue.dirtyinvert, &Mx.desktop->base.object.position);
}

void MxEventQueueDestruct(void)
{
	 if (Mx.queue.qevent)
		  MxFree(Mx.queue.qevent);

	 Mx.queue.qevent = 0;
	 Mx.queue.count = 0;

	 MxRegionDestruct(&Mx.queue.dirtyinvert);
}

static void reallocate(MxEventQueue * queue)
{
	 if (queue->count) {
		  queue->qevent = (MxEventInQueue *) MxRealloc(queue->qevent, (queue->count + 1) * sizeof(MxEventInQueue));

		  /* We are removing the last element from the queue */
	 } else {
		  MxFree(queue->qevent);
		  queue->qevent = 0;
	 }
}

static void _add_to_event_queue(MxEventQueue * queue, const MxEvent * const event, MxObject * const target, const clock_t ticks)
{
	 MxEventInQueue qevent;

	 qevent.event = *event;
	 qevent.target = target;
	 qevent.time = (ticks) ? (clock() + ticks) : 0;

#ifdef MX_DEBUG_EVENT_QUEUE
	 fprintf(mx_stream, "Enqueue %s->%s\n", event_name[event->type], target->name);
#endif

	 /* Add it to the queue */
	 queue->qevent = (MxEventInQueue *) MxRealloc(queue->qevent, (queue->count + 1) * sizeof(MxEventInQueue));
	 queue->qevent[queue->count] = qevent;
	 ++queue->count;

#ifdef MX_DEBUG_EVENT_QUEUE
	 fprintf(mx_stream, "Queue count: %i\n", queue->count);
#endif
}

unsigned int MxEventQueueEmpty(void)
{
	 int i;
	 clock_t now = clock();

	 /* Are there screen portions to update, but don't actually invert to find 
	    out, since this function must be fast as it is a part of the main
	    response loop */
	 if (MxRegionNumber(Mx.queue.dirtyinvert) != 1) {
		  return MxFalse;

		  /* If there is only 1 rect in the update area, it must be different
		     than the basic desktop if there is actually area needed tp be
		     updated */
	 } else {
		  const MxRect *const s = MxRegionRect(Mx.queue.dirtyinvert, 0);
		  const MxRect *const r = &Mx.desktop->base.object.position;

		  if ((s->x1 != r->x1) || (s->y1 != r->y1) || (s->x2 != r->x2)
				|| (s->y2 != r->y2))
				return MxFalse;
	 }

#ifdef MX_DEBUG_EVENT_QUEUE
	 fprintf(mx_stream, "Queue count: %i\n", Mx.queue.count);
#endif

	 /* Are there events that can be sent */
	 for (i = 0; i < Mx.queue.count; i++) {

		  /* Is it time to send the event */
		  if ((Mx.queue.qevent[i].time == 0)
				|| (Mx.queue.qevent[i].time < now))
				return MxFalse;
	 }

	 return MxTrue;
}

void MxEnqueue(MxObject * const object, const MxEvent * const event, const clock_t ticks)
{
	 if ((!object) || (!event))
		  return;

	 _add_to_event_queue(&Mx.queue, event, object, ticks);
}

void MxEnqueueSimple(MxObject * const object, const MxEventType type, const clock_t ticks)
{
	 MxEvent event;

	 event.type = type;

	 MxEnqueue(object, &event, ticks);
}

void MxEnqueueRefreshRect(const MxRect * const rect)
{
	 MxRegionClipRect(&Mx.queue.dirtyinvert, rect);
}

void MxEnqueueRefreshRegion(const MxRegion * const region)
{
	 unsigned int i;

	 for (i = 0; i < MxRegionNumber(*region); i++)
		  MxEnqueueRefreshRect(MxRegionRect(*region, i));
}

void MxEnqueueRefresh(MxObject * const object, unsigned int children)
{
	 /* Refresh an object and't it's children */
	 if ((children) && (object->Fastdraw)) {

		  if (MxVisible(object))
				MxEnqueueRefreshRegion(&object->region);

		  /* Refresh an object but not it's children */
	 } else if ((!children) && (!object->Fastdraw)) {

		  if (MxVisible(object))
				MxEnqueueRefreshRegion(&object->region);

		  /* The object's region is not exactly what we want to update */
	 } else {
		  MxRegion region;
		  unsigned int visible = MxRegionVisibleConstruct(&region, object, children);

		  if (visible)
				MxEnqueueRefreshRegion(&region);

		  MxRegionDestruct(&region);
	 }
}

static void queue_strip(void)
{
	 int i;
	 int index = 0;
	 const int prev = Mx.queue.count;

	 for (i = 0; i < Mx.queue.count; i++) {
		  MxEventInQueue *Queued = &Mx.queue.qevent[i];

		  /* Remove events that we sent already */
		  if ((Queued->target) && (Queued->event.type != MxEventNone)) {
				Mx.queue.qevent[index] = Mx.queue.qevent[i];
				++index;
		  }
	 }

	 /* How many elements dow we have now */
	 if (index != prev) {
		  Mx.queue.count = index;
		  reallocate(&Mx.queue);
	 }
}

void MxEventQueueDispatch(void)
{
	 int i;
	 const int num = Mx.queue.count;

	 unsigned int needupdate = MxFalse;

	 const clock_t now = clock();

#ifdef MX_DEBUG_EVENT_QUEUE
	 fprintf(mx_stream, "Dispatch Start\n");
#endif

	 /* Only dispatch event that we have right now */
	 for (i = 0; i < num; i++) {

		  /* Get the event in the queue */
		  MxEventInQueue *Queued = &Mx.queue.qevent[i];

		  /* Do we send the event now */
		  if (((Queued->time == 0) || (Queued->time < now))
				&& (Queued->target)) {

				/* Get the event out of the queue */
				MxEvent event = Queued->event;
				MxObject *target = Queued->target;

				/* Now make the queued event harmless */
				Queued->target = 0;

#ifdef MX_DEBUG_EVENT_QUEUE
				fprintf(mx_stream, "Dispatch queue index %i\n", i);
				fflush(mx_stream);
#endif

				/* Send the event and get the next one */
				MxEventSend(target, &event);
		  }
	 }

	 /* Strip sent events out of the queue */
	 queue_strip();

	 /* Update the screen if the (inverted) area is not empty, but don't
	    actually invert to find out, since this function must be fast as it is 
	    a part of the main response loop */
	 if (MxRegionNumber(Mx.queue.dirtyinvert) != 1) {
		  needupdate = MxTrue;

		  /* If there is only 1 rect in the update area, it must be different
		     than the basic desktop */
	 } else {
		  const MxRect *const s = MxRegionRect(Mx.queue.dirtyinvert, 0);
		  const MxRect *const r = &Mx.desktop->base.object.position;

		  if ((s->x1 != r->x1) || (s->y1 != r->y1) || (s->x2 != r->x2)
				|| (s->y2 != r->y2))
				needupdate = MxTrue;
	 }

	 /* Update the screen if necessary */
	 if (needupdate) {

		  unsigned int i;
		  MxRegion update;

		  /* Invert the (inverted) update region to get the real update region */
		  MxRegionConstruct(&update);
		  MxRegionAddRect(&update, &Mx.desktop->base.object.position);

		  for (i = 0; i < MxRegionNumber(Mx.queue.dirtyinvert); i++) {
				const MxRect *const s = MxRegionRect(Mx.queue.dirtyinvert, i);

				MxRegionClipRect(&update, s);
		  }

		  /* Try to optimize and sort the region to make update as efficient as 
		     possible */
		  MxRegionOptimize(&update);
		  MxRegionSort(&update);

		  /* Actually call the update on the real screen regions */
		  MxRefreshRegion(&update);

		  /* Clean up */
		  MxRegionDestruct(&update);
		  MxRegionDestruct(&Mx.queue.dirtyinvert);

		  /* Prepare for more screen updates */
		  MxRegionConstruct(&Mx.queue.dirtyinvert);
		  MxRegionAddRect(&Mx.queue.dirtyinvert, &Mx.desktop->base.object.position);
	 }
#ifdef MX_DEBUG_EVENT_QUEUE
	 fprintf(mx_stream, "Dispatch Done\n");
#endif
}

void MxEventQueuePurge(const MxObject * const object)
{
	 int i;

#ifdef MX_DEBUG_EVENT_QUEUE
	 fprintf(mx_stream, "Purging queue of %s [%p]\n", object->name, object);
	 fflush(mx_stream);
#endif

	 /* Find out how many elements that we have now, and shove the sent event
	    elements down in the list */
	 for (i = 0; i < Mx.queue.count; i++) {
		  MxEventInQueue *Queued = &Mx.queue.qevent[i];

		  /* Remove events that we sent already */
		  if (Queued->target == object) {

#ifdef MX_DEBUG_EVENT_QUEUE
				fprintf(mx_stream, "Found object %s [%p] at index %i\n", object->name, object, i);
				fflush(mx_stream);
#endif
				Queued->target = 0;
				Queued->event.type = MxEventNone;
		  }
	 }
#ifdef MX_DEBUG_EVENT_QUEUE
	 fprintf(mx_stream, "Done Purging queue\n");
	 fflush(mx_stream);
#endif

}
