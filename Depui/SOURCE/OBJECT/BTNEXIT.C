#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/button.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxExitButtonHandler(MxObject * object, const MxEvent * const event)
{
	 void *ret = MxPushButtonHandler(object, event);

	 /* If an object was selected, we can close the alert */
	 if (event->type == MxEventSelect)
		  MxEventSendSimple(MxParent(object), MxEventExit);

	 return ret;
}

void MxExitButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * userargs)
{
	 MxButtonArgs args;

	 assert(button);
	 MxUserArgsInit(args, userargs);

	 /* Set the special callback for the exit button */
	 if (!args.stext.caption)
		  args.stext.caption = "Exit";

	 /* Construct the internal object */
	 MxPushButtonConstruct(button, 0, x, y, w, h, &args);
	 button->base.object.handler = MxExitButtonHandler;

#ifdef MX_WINDOW_NAMES
	 button->base.object.name = "MxExitButton";
#endif

	 if (parent)
		  MxInsert(&button->base.object, parent, MxFalse);
}

MxButton *MxExitButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args)
{
	 return (MxButton *) MxNewObject(sizeof(MxButton), (MxVoidFunc) MxExitButtonConstruct, parent, x, y, w, h, &args->object);
}
