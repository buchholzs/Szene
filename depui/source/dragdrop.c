#include "depui/config.h"
#include "depui/types.h"
#include "depui/dragdrop.h"
#include "depui/desktop/desktop.h"
#include "depui/desktop/driver.h"
#include "depui/draw/draw.h"
#include "depui/graphics/frame.h"
#include "depui/object/object.h"
#include "depui/geometry/geometry.h"
#include "depui/pointer/pointer.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static MxDragdropType dragdrop_type_count = (MxDragdropType) (MxDragdropLast - 1);

unsigned int MxDragdropReserve(MxDragdropType * type)
{
	 MX_TRACE("");

	 /* check if it has been reserved already */
	 if ((*type == MxDragdropUser)
		  && ((dragdrop_type_count - 1) > MxDragdropUser)) {

		  *type = dragdrop_type_count;
		  dragdrop_type_count = (MxDragdropType) (dragdrop_type_count - 1);

		  return MxTrue;
	 }
	 return MxFalse;
}

static void draw_dragdrop(MxDragdrop * dragdrop, int x1, int y1, int x2, int y2)
{
	 if (!dragdrop->base.object.Transparent) {
		  const int color1 = Mx.droptarget ? MxColorSelectedFore : MxColorDisabled;
		  const int color2 = Mx.droptarget ? MxColorSelectedBack : MxColorObjectBack;

		  MxFrameEmpty(x1, y1, x2, y2, 1, MxColorLight, MxColorDark);
		  MxFrameEmpty(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 2, color2, color2);

		  MxFontScreenRender(0, dragdrop->caption, MxFontDefault, x1 + 3, y1 + 3, color1, color2);
	 }
}

static void check_drop(MxDragdrop * dragdrop, MxObject * object)
{
	 /* Find out if this is a good target for dropping */
	 MxEvent dropevent;

	 MX_TRACE("");

	 dropevent.type = MxEventDropTarget;
	 dropevent.dragdrop.dragdrop = dragdrop;

	 /* Can you be a good target */
	 Mx.droptarget = (MxObject *) MxEventSend(object, &dropevent);

	 /* Make sure we don't try to send to a bad target, i.e. back to the drag
	    object */
	 if (Mx.droptarget == dragdrop->source)
		  Mx.droptarget = 0;
}

void *MxDragdropHandler(MxObject * object, const MxEvent * const event)
{
	 MxDragdrop *dragdrop = (MxDragdrop *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw_dragdrop(dragdrop, object->position.x1, object->position.y1, object->position.x2, object->position.y2);

		  break;

	 case MxEventDestroy:
		  /* Free the caption that we have allocated */
		  if ((dragdrop->caption) && (dragdrop->ownscaption))
				MxFree((char *) dragdrop->caption);

		  /* Free the data with the destructor */
		  if (dragdrop->destruct)
				dragdrop->destruct(dragdrop->data);

		  break;

	 case MxEventPointerEnter:
		  return object;

	 case MxEventPointerMove:{

				/* What object are we really pointing at */
				MxObject *next = MxObjectXY(event->point.x, event->point.y);

				/* Will the drop be accepted */
				MxObject *oldtarget = Mx.droptarget;

				check_drop(dragdrop, next);

				/* If the validity has changed, redraw the drapdrop object */
				if (Mx.droptarget != oldtarget)
					 MxEnqueueRefresh(&dragdrop->base.object, MxFalse);

				MxMove(object, event->point.x + 10, event->point.y + 16);
				break;
		  }

	 case MxEventButtonLeftRelease:{

				/* Make the object disappear before we go any further */
				object->Transparent = MxTrue;
				MxRegionInvalidate(object);
				MxEnqueueRefresh(object, MxFalse);

				/* Can we drop the data to the object */
				if (Mx.droptarget) {
					 MxEvent dropevent;

					 dropevent.type = MxEventDrop;
					 dropevent.dragdrop.dragdrop = dragdrop;

					 /* Do the drop */
					 MxEventSend(Mx.droptarget, &dropevent);
					 Mx.droptarget = 0;
				}

				/* Destroy ourselves and cleanup */
				MxDestroy(object);
				break;
		  }

	 default:
		  break;
	 }
	 return 0;
}

void MxDragdropStart(const MxObject * const source, void *data, MxDragdropType type, MxDragdropDataDestruct destruct,
							const char *caption, const unsigned int ownscaption)
{
	 /* Create and construct an object to show that we are dragging and
	    dropping */
	 MxDragdrop *dragdrop = (MxDragdrop *) MxMalloc(sizeof(MxDragdrop));

	 MX_TRACE("");

	 assert(source);
	 assert(caption);

	 if (dragdrop) {
		  memset(dragdrop, 0, sizeof(MxDragdrop));

		  MxObjectConstruct(&dragdrop->base.object, mx_desk, Mx.mouse_x + 10, Mx.mouse_y + 16, MxFontLength(MxFontDefault, caption) + 5,
								  MxFontHeight(MxFontDefault) + 5, 0);
		  dragdrop->base.object.handler = MxDragdropHandler;

		  dragdrop->caption = caption;
		  dragdrop->ownscaption = ownscaption;

		  /* Set the Drag and drop data */
		  dragdrop->data = data;
		  dragdrop->type = type;
		  dragdrop->destruct = destruct;
		  dragdrop->source = source;
		  Mx.droptarget = 0;

		  /* Remember that the memory has to be deleted at some point */
		  dragdrop->base.object.allocated = MxTrue;
#ifdef MX_WINDOW_NAMES
		  dragdrop->base.object.name = "MxDragdrop";
#endif
		  /* We want the pointer so we can move with the pointer */
		  MxPointerGrab(&dragdrop->base.object);
		  MxPointerWantMove(&dragdrop->base.object, MxTrue);
	 }
}
