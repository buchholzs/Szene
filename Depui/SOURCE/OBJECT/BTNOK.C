#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/button.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxOkButtonHandler(MxObject * object, const MxEvent * const event)
{
	 void *ret = MxPushButtonHandler(object, event);

	 /* If an object was selected, we can close the alert */
	 if (event->type == MxEventSelect)
		  MxEventSendSimple(MxParent(object), MxEventOk);

	 return ret;
}

void MxOkButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * userargs)
{
	 MxButtonArgs args;

	 assert(button);
	 MxUserArgsInit(args, userargs);

	 /* Create the special buttons Ok type */
	 if (!args.stext.caption)
		  args.stext.caption = "Ok";

	 /* Construct the internal object */
	 MxPushButtonConstruct(button, 0, x, y, w, h, &args);
	 button->base.object.handler = MxOkButtonHandler;

#ifdef MX_WINDOW_NAMES
	 button->base.object.name = "MxOkButton";
#endif

	 if (parent)
		  MxInsert(&button->base.object, parent, MxFalse);
}

MxButton *MxOkButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args)
{
	 return (MxButton *) MxNewObject(sizeof(MxButton), (MxVoidFunc) MxOkButtonConstruct, parent, x, y, w, h, &args->object);
}
