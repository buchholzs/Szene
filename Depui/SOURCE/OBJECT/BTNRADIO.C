#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/button.h"
#include "depui/desktop/driver.h"
#include "depui/event/focus.h"
#include "depui/event/event.h"
#include "depui/event/queue.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/decorate.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxRadioButtonHandler(MxObject * object, const MxEvent * const event)
{
	 MxButton *button = (MxButton *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw_check(button, object->position.x1, object->position.y1, object->position.x2, object->position.y2, MxDecorationRadioon,
						 MxDecorationRadiooff);
		  break;

	 case MxEventHotkey:
	 case MxEventButtonLeftPress:

		  MxFocusSet(object);

		  /* Toggle the state of the button */
		  if (!button->pressed) {
				MxEventSendSimple(object, MxEventSelect);
				MxEnqueueRefresh(object, MxFalse);
		  }
		  return object;

	 case MxEventSelect:

		  /* Deselect the others */
		  MxEventSendSimpleToChildren(MxParent(object), MxEventDeselect, object);

		  /* Select ourselves */
		  return MxCheckboxHandler(object, event);

		  /* Otherwise act like a checkbox */
	 default:
		  return MxCheckboxHandler(object, event);
	 }
	 return 0;
}

void MxRadioButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * userargs)
{
	 MxCheckboxConstruct(button, 0, x, y, w, h, userargs);
	 button->base.object.handler = MxRadioButtonHandler;

#ifdef MX_WINDOW_NAMES
	 button->base.object.name = "MxRadioButton";
#endif

	 if (parent)
		  MxInsert(&button->base.object, parent, MxFalse);
}

MxButton *MxRadioButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args)
{
	 return (MxButton *) MxNewObject(sizeof(MxButton), (MxVoidFunc) MxRadioButtonConstruct, parent, x, y, w, h, &args->object);
}
