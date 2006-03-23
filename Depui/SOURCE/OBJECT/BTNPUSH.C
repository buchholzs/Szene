/* After event sending we should do nothing with the object.  The event
   may have caused the object to destroyed. */
#include "depui/config.h"
#include "depui/desktop/driver.h"
#include "depui/object/button.h"
#include "depui/event/queue.h"
#include "depui/event/focus.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxPushButtonHandler(MxObject * object, const MxEvent * const event)
{
	 MxButton *button = (MxButton *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  mx_draw_button(button, object->position.x1, object->position.y1, object->position.x2, object->position.y2, button->pressed, 1,
							  button->Style, MxColorFore, MxColorBack);
		  break;

	 case MxEventButtonLeftPress:

		  if (button->disabled)
				break;

		  MxFocusSet(object);

		  if (!button->pressed)
				MxEnqueueRefresh(object, MxFalse);

		  button->pressed = MxTrue;
		  button->armed = MxTrue;

		  return object;

	 case MxEventButtonLeftRelease:

		  if (button->disabled)
				break;

		  if ((button->pressed) && (button->armed)) {
				button->armed = MxFalse;
				button->pressed = MxFalse;
				MxEnqueueSimple(object, MxEventDeselect, 0);
				MxEventSendSimple(object, MxEventSelect);
		  }
		  return object;

	 case MxEventPointerLeave:

		  if (button->disabled)
				break;

		  if (button->pressed)
				MxEnqueueRefresh(object, MxFalse);

		  button->armed = MxFalse;
		  button->pressed = MxFalse;
		  break;

	 case MxEventHotkey:
		  if (button->disabled)
				break;

		  MxEnqueueSimple(object, MxEventDeselect, 0);
		  MxEventSendSimple(object, MxEventSelect);
		  return object;

	 default:
		  return MxToggleButtonHandler(object, event);
	 }
	 return 0;
}

void MxPushButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * userargs)
{
	 assert(button);
	 MxToggleButtonConstruct(button, 0, x, y, w, h, userargs);
	 button->base.object.handler = MxPushButtonHandler;

#ifdef MX_WINDOW_NAMES
	 button->base.object.name = "MxPushButton";
#endif

	 if (parent)
		  MxInsert(&button->base.object, parent, MxFalse);
}

MxButton *MxPushButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args)
{
	 return (MxButton *) MxNewObject(sizeof(MxButton), (MxVoidFunc) MxPushButtonConstruct, parent, x, y, w, h, &args->object);
}
