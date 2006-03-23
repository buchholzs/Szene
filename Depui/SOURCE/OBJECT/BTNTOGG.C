#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/button.h"
#include "depui/object/defsize.h"
#include "depui/args/args.h"
#include "depui/event/queue.h"
#include "depui/event/focus.h"
#include "depui/draw/region.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxToggleButtonHandler(MxObject * object, const MxEvent * const event)
{
	 MxButton *button = (MxButton *) object;	/* button returned here */

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  mx_draw_button(button, object->position.x1, object->position.y1, object->position.x2, object->position.y2, button->pressed, 1,
							  button->Style, MxColorFore, MxColorBack);
		  break;

	 case MxEventHotkey:
	 case MxEventButtonLeftPress:

		  MxFocusSet(object);

		  /* Toggle the state of the button */
		  MxEventSendSimple(object, button->pressed ? MxEventDeselect : MxEventSelect);
		  return object;

	 case MxEventSelect:
		  if (button->disabled)
				break;

		  if (!button->pressed) {
				button->pressed = MxTrue;
				MxEnqueueRefresh(object, MxFalse);

				if (button->callback)
					 button->callback(&button->base.object, button->data, MxTrue);
		  }
		  break;

	 case MxEventDeselect:
		  if (button->disabled)
				break;

		  if (button->pressed) {
				button->pressed = MxFalse;
				MxEnqueueRefresh(object, MxFalse);

				if (button->callback)
					 button->callback(&button->base.object, button->data, MxFalse);
		  }
		  break;

	 case MxEventKeyUnbound:

		  if (button->disabled)
				break;

		  /* Grab unbound keypresses and select us if we are the default key */
		  if (button->defaultbutton) {
				if ((event->key.code == ' ') || (event->key.code == 0x0d)) {
					 MxEventSendSimple(object, MxEventHotkey);
					 return object;
				}
		  }
		  break;

	 case MxEventIsSelected:
		  if (button->pressed)
				return object;
		  break;

	 case MxEventFocusGot:
	 case MxEventFocusLost:
		  if (button->disabled)
				break;

		  MxEnqueueRefresh(object, MxFalse);
		  return object;

	 case MxEventPostInit:
		  MxStatictextHandler(object, event);
		  mx_statictext_justify(&button->base.stext, object->position.x1 + 4, object->position.y1 + 4, object->position.x2 - 4,
										object->position.y2 - 4);
		  break;

	 default:
		  return MxStatictextHandler(object, event);
	 }
	 return 0;
}

void MxToggleButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * userargs)
{
	 int defw, defh;

	 MxButtonArgs args;

	 assert(button);
	 MxUserArgsInit(args, userargs);

	 if (args.stext.caption) {
		  defw = MxFontLength(MxFontDefault, args.stext.caption) + 8;
		  args.stext.len = strlen(args.stext.caption);
	 } else
		  defw = 10;

	 defh = MxFontHeight(MxFontDefault) + 8;
	 MxDefaultSize(&w, &h, defw, defh);

	 /* Construct the internal object */
	 memset(button, 0, sizeof(MxButton));
	 MxStatictextConstruct(&button->base.stext, 0, x, y, w, h, &args.stext);
	 button->base.object.handler = MxToggleButtonHandler;

	 /* Set the button specific values from the arguments */
	 button->pressed = MxFalse;
	 button->Style = args.Style;

	 button->callback = args.callback;
	 button->data = args.data;

	 button->disabled = args.disabled;
	 button->defaultbutton = args.defaultbutton;

#ifdef MX_WINDOW_NAMES
	 button->base.object.name = "MxToggleButton";
#endif

	 if (parent)
		  MxInsert(&button->base.object, parent, MxFalse);
}

MxButton *MxToggleButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args)
{
	 return (MxButton *) MxNewObject(sizeof(MxButton), (MxVoidFunc) MxToggleButtonConstruct, parent, x, y, w, h, &args->object);
}
