#ifndef MX_EVENT_EVENT_H
#define MX_EVENT_EVENT_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/platform/platform.h"
#include "depui/draw/region.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef enum MxEventType {
		  MxEventNone = 0,

		  MxEventPreInit,
		  MxEventPostInit,

		  MxEventExit,
		  MxEventOk,
		  MxEventCancel,

		  MxEventDestroy,

		  MxEventExpose,			  /* RegionPtrEvent type */
		  MxEventRegionMask,		  /* RegionPtrEvent type */

		  MxEventButtonLeftPress, /* PointerEvent type */
		  MxEventButtonLeftPressChild,	/* PointerEvent type */
		  MxEventButtonLeftRelease,	/* PointerEvent type */
		  MxEventButtonLeftReleaseChild,	/* PointerEvent type */

		  MxEventButtonRightPress,	/* PointerEvent type */
		  MxEventButtonRightPressChild,	/* PointerEvent type */
		  MxEventButtonRightRelease,	/* PointerEvent type */
		  MxEventButtonRightReleaseChild,	/* PointerEvent type */

		  MxEventButtonCenterPress,	/* PointerEvent type */
		  MxEventButtonCenterPressChild,	/* PointerEvent type */
		  MxEventButtonCenterRelease,	/* PointerEvent type */
		  MxEventButtonCenterReleaseChild,	/* PointerEvent type */

		  MxEventPointerEnter,
		  MxEventPointerLeave,
		  MxEventPointerMove,	  /* PointerEvent type */

		  MxEventKey,				  /* KeypressEvent type */
		  MxEventKeyChild,		  /* KeypressEvent type */
		  MxEventKeyUnbound,		  /* KeypressEvent type */

		  MxEventHotkey,

		  MxEventSlider,			  /* MxEventSliderMove type */

		  MxEventFocusGot,
		  MxEventFocusLost,
		  MxEventFocusChild,		  /* MxEventObject type */
		  MxEventActiveGot,
		  MxEventActiveLost,

		  MxEventGeomRequest,	  /* GeomEvent type */
		  MxEventGeomChanged,	  /* GeomEvent type */

		  MxEventGeomParentChanged,
		  MxEventGeomChildChanged,

		  MxEventZOrderRequest,	  /* MxEventObject type */
		  MxEventZOrderInform,	  /* ZOrderEvent type */

		  MxEventSelect,
		  MxEventDeselect,
		  MxEventIsSelected,

		  MxEventListareaSelected,	/* MxListareaElem type */
		  MxEventListareaEnter,	  /* MxListareaElem type */
		  MxEventListareaLeave,	  /* MxListareaElem type */
		  MxEventListareaDrag,	  /* MxListareaElem type */

		  MxEventGetCaption,

		  MxEventDropTarget,		  /* MxEventDragDrop type */
		  MxEventDrop,				  /* MxEventDragDrop type */

		  MxEventMoverResized,
		  MxEventMoverMoved,

		  MxEventCursorBlink,

		  MxEventScrollRect,

		  MxEventTextareaPreparse,
		  MxEventTextareaPostparse,

		  MxEventUserType,		  /* UserEvent type */

		  MxEventLast = 0x7fff	  /* Force the enum to at least 16 bits */
	 } MxEventType;

	 typedef struct MxEventSimple {
		  MxEventType type;
	 } MxEventSimple;

	 typedef struct MxEventRegion {
		  MxEventType type;
		  MxRegion *region;
	 } MxEventRegion;

	 typedef struct MxEventRect {
		  MxEventType type;
		  MxRect rect;
	 } MxEventRect;

	 typedef struct MxEventPoint {
		  MxEventType type;
		  int x;
		  int y;
	 } MxEventPoint;

	 typedef struct MxEventKeypress {
		  MxEventType type;
		  unsigned int raw;
		  unsigned int code;
		  MxKey key;
	 } MxEventKeypress;

	 typedef struct MxEventGeom {
		  MxEventType type;
		  struct MxObject *dest;
		  struct MxGeomData *data;
	 } MxEventGeom;

	 typedef struct MxEventSlidermove {
		  MxEventType type;
		  int offset;
		  struct MxSlider *source;
	 } MxEventSlidermove;

	 typedef struct MxEventObject {
		  MxEventType type;
		  struct MxObject *object;
	 } MxEventObject;

	 typedef struct MxEventZOrder {
		  MxEventType type;
		  struct MxObject *target;
		  int newz;
	 } MxEventZOrder;

	 typedef struct MxEventListareaElement {
		  MxEventType type;
		  struct MxListDef *def;
	 } MxEventListareaElement;

	 typedef struct MxEventDragdrop {
		  MxEventType type;
		  struct MxDragdrop *dragdrop;
	 } MxEventDragdrop;

	 typedef struct MxEventUser {
		  MxEventType type;
		  void *data;
	 } MxEventUser;

	 typedef union MxEvent {
		  MxEventType type;
		  MxEventSimple simple;
		  MxEventRegion region;
		  MxEventRect rect;
		  MxEventPoint point;
		  MxEventKeypress key;
		  MxEventGeom geom;
		  MxEventSlidermove slider;
		  MxEventObject object;
		  MxEventZOrder zorder;
		  MxEventDragdrop dragdrop;
		  MxEventListareaElement listelem;
		  MxEventUser user;
	 } MxEvent;

/* If we are debugging we have to log the events */
#ifdef MX_DEBUG_EVENT
#define MxEventSend(object, event) mx_event_send((object), (event));
	 void *mx_event_send(struct MxObject *const object, const MxEvent * const event);

/* Otherwise we can call a faster event method */
#else
#define MxEventSend(object, event) ((object)->handler((object), (event)))
#endif

	 /* Helper functions for event sending */
	 void *MxEventSendSimple(struct MxObject *const object, const MxEventType type);
	 void *MxEventSendObject(struct MxObject *const object, const MxEventType type, struct MxObject *const target);
	 void *MxEventSendSimpleToChildren(const struct MxObject *const object, const MxEventType type, const struct MxObject *const skip);

	 unsigned int MxEventReserve(MxEventType * type);
	 unsigned int MxEventReserveEvent(MxEvent * event);

#ifdef MX_EVENT_NAMES
	 extern const char *event_name[];
#endif

#ifdef __cplusplus
}
#endif
#endif
