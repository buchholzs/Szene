#include "depui/config.h"
#include "depui/macros.h"
#include "depui/types.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/desktop/desktop.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#ifdef MX_DEBUG_EXPOSE_RECT
#include "depui/graphics/frame.h"
#endif

static void update_object_region(MxObject * const object, MxRegion * const region)
{
	 assert(object);
	 assert(region);

	 if (object->regionvalid)
		  MxRegionDestruct(region);

	 MxRegionVisibleConstruct(region, object, object->Fastdraw ? MxFalse : MxTrue);
	 MxRegionOptimize(region);
	 MxRegionSort(region);

	 object->regionvalid = MxTrue;

#ifdef MX_DEBUG_EVENT
	 fprintf(mx_stream, "RegionUpdated: %s [%p]\n", object->name, object);
#endif
}

static void mx_region_expose(MxObject * const object, const MxRegion * const region, const MxRect * const rect)
{
	 unsigned int i;
	 MxRect current;

	 assert(object);
	 MX_CHECKSTACK(object);

	 /* Create the clipping region */
	 for (i = 0; i < MxRegionNumber(*region); i++) {
		  const MxRect *const s = MxRegionRect(*region, i);

		  MX_INTERSECT_RECTS(*s, *rect, current);
		  if (MX_VALID_RECT(current))
				MxRegionAddRect(&mx_region, &current);
	 }

	 /* Make sure the clipping region is efficient */
	 MxRegionOptimize(&mx_region);
	 MxRegionSort(&mx_region);

#ifdef MX_DEBUG_EXPOSE_RECT
	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

//      MxFrameEmpty(s->x1, s->y1, s->x2, s->y2, 1, rand(), rand());
		  MxScreenRectFill(0, s->x1, s->y1, s->x2, s->y2, MxColorFore);
//        delay(1);
	 }
	 if (MxRegionNumber(mx_region))
		  rest(100);
#endif

	 /* Expose the clipping region if we have a region */
	 if (MxRegionNumber(mx_region)) {
		  MxEvent expose;

		  expose.type = MxEventExpose;
		  expose.region.region = &mx_region;

		  MxEventSend(object, &expose);

#ifdef MX_DEBUG_REGION_RECT
		  for (i = 0; i < MxRegionNumber(mx_region); i++) {
				const MxRect *const s = MxRegionRect(mx_region, i);

				MxFrameEmpty(s->x1, s->y1, s->x2, s->y2, 1, rand(), rand());
		  }
#endif
	 }

	 /* Cleanup */
	 MxRegionDestruct(&mx_region);
	 MxRegionConstruct(&mx_region);

	 /* Tell the desktop that something has changed on the screen */
	 Mx.needflush = MxTrue;
}

static void _refresh_rect(MxObject * object, const MxRect * const rect)
{
	 assert(object);
	 assert(rect);

	 MX_CHECKSTACK(object);

	 if (!MX_VALID_RECT(*rect))
		  return;

	 if (!object->regionvalid)
		  update_object_region(object, &object->region);

	 if (MX_RECTS_OVERLAP(object->position, *rect))
		  mx_region_expose(object, &object->region, rect);
	 else
		  return;

	 for (object = MxLastChild(object); object; object = MxPrev(object))
		  if (MX_RECTS_OVERLAP(object->position, *rect))
				_refresh_rect(object, rect);
}

/* refreshes the whole object tree in the area of the object */
void MxRefreshRect(const MxRect * const rect)
{
#ifdef MX_DEBUG_EXPOSE_RECT
//    MxFrameEmpty(rect->x1, rect->y1, rect->x2, rect->y2, 10, rand(), rand());
//    rest(10);
#endif
	 assert(rect);

	 /* Store the old clipping area */
	 mx_output->DrawingArea(rect->x1, rect->y1, rect->x2, rect->y2);
	 mx_output->screen_vtable.Aquire(0);

	 _refresh_rect(mx_desk, rect);

	 mx_output->screen_vtable.Release(0);
	 mx_output->DoneDrawingArea();
}

void MxRefreshRegion(const MxRegion * const region)
{
	 unsigned int i;

	 assert(region);

	 for (i = 0; i < MxRegionNumber(*region); i++)
		  MxRefreshRect(MxRegionRect(*region, i));
}

unsigned int MxVisible(struct MxObject *const object)
{
	 assert(object);

	 if (!object->init)
		  return MxFalse;

	 if (!object->regionvalid)
		  update_object_region(object, &object->region);

	 if (!MxRegionEmpty(&object->region))
		  return MxTrue;

	 return MxFalse;
}

void MxRefresh(MxObject * const object)
{
	 assert(object);

	 if (MxVisible(object))
		  MxRefreshRegion(&object->region);
}

static void _region_invalidate(MxObject * const object)
{
	 MxObject *ptr;

	 assert(object);
	 MX_CHECKSTACK(object);

	 /* Don't go down the tree if the object is already invalidated */
	 if (!object->regionvalid)
		  return;

	 /* Invalidate the regions of the children also */
	 for (ptr = MxFirstChild(object); ptr; ptr = MxNext(ptr))
		  _region_invalidate(ptr);

	 /* Invalidate our region */
	 if (object->regionvalid)
		  MxRegionDestruct(&object->region);
	 object->regionvalid = MxFalse;
}

void MxRegionInvalidate(MxObject * object)
{
	 MxObject *parent = MxParent(object);

	 assert(object);

	 if (parent) {
		  if (parent->regionvalid)
				MxRegionDestruct(&parent->region);
		  parent->regionvalid = MxFalse;
	 }

	 while (object) {
		  _region_invalidate(object);
		  object = MxNext(object);
	 }
}
