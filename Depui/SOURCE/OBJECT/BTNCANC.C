#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/button.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxCancelButtonHandler(MxObject * object, const MxEvent * const event)
{
	 void *ret = MxPushButtonHandler(object, event);

	 if (event->type == MxEventSelect)
		  MxEventSendSimple(MxParent(object), MxEventCancel);

	 return ret;
}

void MxCancelButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * userargs)
{
	 MxButtonArgs args;

	 assert(button);
	 MxUserArgsInit(args, userargs);

	 /* Create the special buttons exit type */
	 if (!args.stext.caption)
		  args.stext.caption = "Cancel";

	 /* Construct the internal object */
	 MxPushButtonConstruct(button, 0, x, y, w, h, &args);
	 button->base.object.handler = MxCancelButtonHandler;

#ifdef MX_WINDOW_NAMES
	 button->base.object.name = "MxCancelButton";
#endif

	 if (parent)
		  MxInsert(&button->base.object, parent, MxFalse);
}

MxButton *MxCancelButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args)
{
	 return (MxButton *) MxNewObject(sizeof(MxButton), (MxVoidFunc) MxCancelButtonConstruct, parent, x, y, w, h, &args->object);
}
