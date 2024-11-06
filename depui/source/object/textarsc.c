#include "depui/config.h"
#include "depui/args/args.h"
#include "depui/object/text.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxScrollTextareaTextareaHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

		  /* Pass the drop event to the scroller */
	 case MxEventDropTarget:
		  return MxEventSend(MxParent(MxParent(object)), event);

	 default:
		  return MxTextareaHandler(object, event);
	 }
	 return 0;
}

void *MxScrollTextareaHandler(MxObject * object, const MxEvent * const event)
{
	 return MxScrollHandler(object, event);
}

void MxScrollTextareaConstruct(MxScrollTextarea * box, MxObject * parent, int x, int y, int w, int h, MxScrollTextareaArgs * userargs)
{
	 MxScrollTextareaArgs args;

	 assert(box);
	 MxUserArgsInit(args, userargs);

	 /* Construct the underlying box */
	 memset(box, 0, sizeof(MxScrollTextarea));
	 MxTextareaConstruct(&box->textarea, 0, 0, 0, w - 4, h - 4, &args.textarea);
	 box->textarea.base.object.handler = MxScrollTextareaTextareaHandler;

	 /* Construct the scroller itself */
	 if (!args.scroll.client)
		  args.scroll.client = &box->textarea.base.object;

//    args.scroll.slider_border -= 1;

	 MxScrollConstruct(&box->base.scroll, parent, x, y, w, h, &args.scroll);

#ifdef MX_WINDOW_NAMES
	 box->base.object.name = "MxScrollTextarea";
#endif
}

MxScrollTextarea *MxScrollTextareaNew(MxObject * parent, int x, int y, int w, int h, MxScrollTextareaArgs * args)
{
	 return (MxScrollTextarea *) MxNewObject(sizeof(MxScrollTextarea), (MxVoidFunc)
														  MxScrollTextareaConstruct, parent, x, y, w, h, &args->object);
}
