#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/event/event.h"
#include "depui/draw/draw.h"
#include "depui/object/object.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static MxEventType _event_type_count = (MxEventType) (MxEventLast - 1);

#ifdef MX_EVENT_NAMES
#include <assert.h>

const char *event_name[] = {
	 "MxEventNone",

	 "MxEventPreInit",
	 "MxEventPostInit",

	 "MxEventExit",
	 "MxEventOk",
	 "MxEventCancel",

	 "MxEventDestroy",

	 "MxEventExpose",				  /* RegionPtrEvent type */
	 "MxEventRegionMask",		  /* RegionPtrEvent type */

	 "MxEventButtonLeftPress",	  /* PointerEvent type */
	 "MxEventButtonLeftPressChild",	/* PointerEvent type */
	 "MxEventButtonLeftRelease", /* PointerEvent type */
	 "MxEventButtonLeftReleaseChild",	/* PointerEvent type */

	 "MxEventButtonRightPress",  /* PointerEvent type */
	 "MxEventButtonRightPressChild",	/* PointerEvent type */
	 "MxEventButtonRightRelease",	/* PointerEvent type */
	 "MxEventButtonRightReleaseChild",	/* PointerEvent type */

	 "MxEventButtonCenterPress", /* PointerEvent type */
	 "MxEventButtonCenterPressChild",	/* PointerEvent type */
	 "MxEventButtonCenterRelease",	/* PointerEvent type */
	 "MxEventButtonCenterReleaseChild",	/* PointerEvent type */

	 "MxEventPointerEnter",
	 "MxEventPointerLeave",
	 "MxEventPointerMove",		  /* PointerEvent type */

	 "MxEventKey",					  /* KeypressEvent type */
	 "MxEventKeyChild",			  /* KeypressEvent type */
	 "MxEventKeyUnbound",		  /* KeypressEvent type */

	 "MxEventHotkey",

	 "MxEventSlider",				  /* MxEventSliderMove type */

	 "MxEventFocusGot",
	 "MxEventFocusLost",
	 "MxEventFocusChild",		  /* MxEventObject type */
	 "MxEventActiveGot",
	 "MxEventActiveLost",

	 "MxEventGeomRequest",		  /* GeomEvent type */
	 "MxEventGeomChanged",		  /* GeomEvent type */

	 "MxEventGeomParentChanged",
	 "MxEventGeomChildChanged",

	 "MxEventZOrderRequest",	  /* MxEventObject type */
	 "MxEventZOrderInform",		  /* ZOrderEvent type */

	 "MxEventSelect",
	 "MxEventDeselect",
	 "MxEventIsSelected",

	 "MxEventListareaSelected",  /* MxListareaElem type */
	 "MxEventListareaEnter",	  /* MxListareaElem type */
	 "MxEventListareaLeave",	  /* MxListareaElem type */
	 "MxEventListareaDrag",		  /* MxListareaElem type */

	 "MxEventGetCaption",

	 "MxEventDropTarget",		  /* MxEventDragDrop type */
	 "MxEventDrop",				  /* MxEventDragDrop type */

	 "MxEventMoverResized",
	 "MxEventMoverMoved",

	 "MxEventCursorBlink",

	 "MxEventScrollRect",

	 "MxEventTextareaPreparse",
	 "MxEventTextareaPostparse",

	 "MxEventUserType"			  /* UserEvent type */
};
#endif

#ifdef MX_DEBUG_EVENT
void *mx_event_send(MxObject * const object, const MxEvent * const event)
{
	 const int type = (event->type > MxEventUserType) ? MxEventUserType : event->type;

	 MX_CHECKSTACK(object);

	 assert(object);
	 assert(event);

	 /* User type is just a marger and should not actually be sent */
	 assert(event->type != MxEventUserType);

	 /* Dont send invalid messages or events */
	 if ((!object) || (!event)) {
		  assert("!! Invalid MxObject/MxEvent\n" == 0);
		  return 0;
	 }

	 /* Ignore event to unitialized object, except to destroy or insert */
	 if ((!object->init) && (event->type != MxEventDestroy)) {

#ifdef MX_DEBUG_EVENT_LOST
		  fprintf(mx_stream, "Message to unitialized object %s->%s [%p]\n", event_name[type], object->name, object);
		  fflush(mx_stream);
		  assert("Ignoring message to unitialized object" == 0);
#endif
//      return 0;
	 }

	 if (event->type != MxEventExpose) {
		  fprintf(mx_stream, "%s->%s [%p]\n", event_name[type], object->name, object);
		  fflush(mx_stream);
	 }

	 /* Actually call the classes handler */
	 return object->handler(object, event);
}
#endif

/* Reserves a event type number for another use */
unsigned int MxEventReserve(MxEventType * type)
{
	 assert(type);

	 /* Check if it has been reserved already, or there is not enough room */
	 if ((*type == MxEventUserType) && ((_event_type_count - 1) > MxEventUserType)) {

		  *type = _event_type_count;
		  _event_type_count = (MxEventType) (_event_type_count - 1);
		  return MxTrue;
	 }
	 return MxFalse;
}

unsigned int MxEventReserveEvent(MxEvent * event)
{
	 return MxEventReserve(&event->type);
}

void *MxEventSendSimple(MxObject * const object, const MxEventType type)
{
	 MxEvent event;

	 event.type = type;

	 return MxEventSend(object, &event);
}

void *MxEventSendObject(MxObject * const object, const MxEventType type, MxObject * const target)
{
	 MxEvent event;

	 event.type = type, event.object.object = target;

	 return MxEventSend(object, &event);
}
