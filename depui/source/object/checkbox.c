#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/button.h"
#include "depui/object/defsize.h"
#include "depui/desktop/driver.h"
#include "depui/event/focus.h"
#include "depui/event/event.h"
#include "depui/event/queue.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/decorate.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxCheckboxHandler(MxObject * object, const MxEvent * const event)
{
	 MxButton *button = (MxButton *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw_check(button, object->position.x1, object->position.y1, object->position.x2, object->position.y2, MxDecorationCheckon,
						 MxDecorationCheckoff);
		  break;

	 case MxEventFocusGot:
	 case MxEventFocusLost:
		  MxEnqueueRefresh(object, MxFalse);
		  return object;

		  /* Otherwise act like a push button */
	 default:
		  return MxToggleButtonHandler(object, event);
	 }
	 return 0;
}

void MxCheckboxConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * userargs)
{
	 int defw, defh;

	 MxButtonArgs args;

	 assert(button);
	 MxUserArgsInit(args, userargs);

	 defw = MxFontLength(MxFontDefault, args.stext.caption) + MxFontHeight(MxFontDefault) + 8;
	 defh = MxFontHeight(MxFontDefault) + 2;
	 MxDefaultSize(&w, &h, defw, defh);

	 MxToggleButtonConstruct(button, 0, x, y, w, h, &args);
	 button->base.object.handler = MxCheckboxHandler;
	 button->base.object.Transparent = MxTrue;

#ifdef MX_WINDOW_NAMES
	 button->base.object.name = "MxCheckbox";
#endif

	 if (parent)
		  MxInsert(&button->base.object, parent, MxFalse);
}

MxButton *MxCheckboxNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args)
{
	 return (MxButton *) MxNewObject(sizeof(MxButton), (MxVoidFunc) MxCheckboxConstruct, parent, x, y, w, h, &args->object);
}
