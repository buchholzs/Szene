#ifndef MX_EVENT_QUEUE_H
#define MX_EVENT_QUEUE_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/event/event.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxEventInQueue {

		  MxEvent event;
		  struct MxObject *target;

		  clock_t time;
	 } MxEventInQueue;

	 typedef struct MxEventQueue {

		  MxEventInQueue *qevent;
		  int count;

		  MxRegion dirtyinvert;

	 } MxEventQueue;

	 void MxEventQueueConstruct(void);
	 void MxEventQueueDestruct(void);

	 void MxEventQueueDispatch(void);

	 void MxEnqueue(struct MxObject *const object, const MxEvent * const event, const clock_t dispatch_time);
	 void MxEnqueueSimple(struct MxObject *const object, const MxEventType type, const clock_t ticks);

	 void MxEnqueueRefresh(struct MxObject *const object, unsigned int children);
	 void MxEnqueueRefreshRect(const MxRect * const rect);
	 void MxEnqueueRefreshRegion(const MxRegion * const region);

	 unsigned int MxEventQueueEmpty(void);
	 void MxEventQueuePurge(const struct MxObject *const object);

#ifdef __cplusplus
}
#endif
#endif
