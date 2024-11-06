#include "depui/config.h"
#include "depui/args/args.h"
#include "depui/desktop/driver.h"
#include "depui/desktop/desktop.h"
#include "depui/draw/draw.h"
#include "depui/geometry/geometry.h"
#include "depui/draw/region.h"
#include "depui/graphics/frame.h"
#include "depui/object/mover.h"
#include "depui/object/object.h"
#include "depui/pointer/pointer.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void do_it(const MxMover * const mover)
{
	 /* Actually move or resize the source */
	 if (!mover->resize) {
		  const int x = mover->base.object.position.x1;
		  const int y = mover->base.object.position.y1;

		  MxMove(mover->source, x, y);
		  MxEventSendSimple(mover->source, MxEventMoverMoved);

	 } else {
		  const int w = MxW(&mover->base.object) - 1;
		  const int h = MxH(&mover->base.object) - 1;

		  MxResize(mover->source, w, h);
		  MxEventSendSimple(mover->source, MxEventMoverResized);
	 }
}

void *MxMoverHandler(MxObject * object, const MxEvent * const event)
{
	 const MxMover *const mover = (MxMover *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  if (!mover->opaque) {
				const int x1 = object->position.x1;
				const int y1 = object->position.y1;
				const int x2 = object->position.x2;
				const int y2 = object->position.y2;

				MxFrameEmpty(x1, y1, x2, y2, 1, MxColorLight, MxColorDark);
				MxFrameEmpty(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 1, MxColorDark, MxColorLight);
		  }
		  break;

	 case MxEventRegionMask:{
				MxRect clip;

				clip.x1 = object->position.x1 + 2;
				clip.y1 = object->position.y1 + 2;
				clip.x2 = object->position.x2 - 2;
				clip.y2 = object->position.y2 - 2;

				MxRegionClipRect(event->region.region, &clip);
				break;
		  }

	 case MxEventPointerMove:
		  if (!mover->resize)
				MxMove(object, event->point.x - mover->offset_x, event->point.y - mover->offset_y);
		  else
				MxResize(object, event->point.x + mover->offset_x - object->position.x1,
							event->point.y + mover->offset_y - object->position.y1);

		  /* Do we move the object as the mouse moves */
		  if (mover->opaque)
				do_it(mover);

		  break;

	 case MxEventButtonLeftRelease:

		  /* Actually move or resize the source if we haven't done already */
		  if (!mover->opaque)
				do_it(mover);

		  /* Destroy ourselves and cleanup, this will automatically release the 
		     pointer if necessary and cleanup the screen */
		  MxEnqueueRefreshRect(&object->position);
		  MxDestroy(object);
		  break;

	 default:
		  break;
	 }
	 return 0;
}

void MxMoverStart(MxObject * const source, const unsigned int resize, int x, int y)
{
	 MxMover *mover;

	 /* We cannot move object without an object or a parent */
	 if ((!source) || (!MxParent(source)))
		  return;

	 assert(source);

	 mover = (MxMover *) MxMalloc(sizeof(MxMover));

	 if (mover) {
		  memset(mover, 0, sizeof(MxMover));

		  MxObjectConstruct(&mover->base.object, mx_desk, source->position.x1, source->position.y1,
								  source->position.x2 - source->position.x1, source->position.y2 - source->position.y1, 0);
		  mover->base.object.handler = MxMoverHandler;

		  mover->source = source;
		  mover->resize = resize;

		  if (!resize) {
				mover->offset_x = x - source->position.x1;
				mover->offset_y = y - source->position.y1;
		  } else {
				mover->offset_x = source->position.x2 - x;
				mover->offset_y = source->position.y2 - y;
		  }

		  /* Remember that the memory has to be deleted at some point */
		  mover->base.object.allocated = MxTrue;

		  /* Decide to do outline or opaque moves */
		  mover->opaque = Mx.OpaqueMove;

		  mover->base.object.Transparent = mover->opaque;
		  mover->base.object.Hasmask = !mover->opaque;

#ifdef MX_WINDOW_NAMES
		  mover->base.object.name = "MxMover";
#endif
		  /* We want the pointer so we can move with the pointer */
		  MxPointerGrab(&mover->base.object);
		  MxPointerWantMove(&mover->base.object, MxTrue);
	 }
}
