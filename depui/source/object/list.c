#include "depui/config.h"
#include "depui/object/list.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxListHandler(MxObject * object, const MxEvent * const event)
{
	 return MxScrollHandler(object, event);
}

void MxListConstruct(MxList * list, MxObject * parent, int x, int y, int w, int h, MxListArgs * userargs)
{
	 MxListArgs args;

	 assert(list);
	 MxUserArgsInit(args, userargs);

	 /* Construct the underlying list */
	 MxListareaConstruct(&list->listarea, 0, 0, 0, w - 4, h - 4, &args.listarea);

	 /* Construct the scroller itself */
	 args.scroll.client = &list->listarea.base.object;

	 MxScrollConstruct(&list->base.scroll, parent, x, y, w, h, &args.scroll);
	 list->base.object.handler = MxListHandler;

#ifdef MX_WINDOW_NAMES
	 list->base.object.name = "MxList";
#endif
}

MxList *MxListNew(MxObject * parent, int x, int y, int w, int h, MxListArgs * args)
{
	 return (MxList *) MxNewObject(sizeof(MxList), (MxVoidFunc) MxListConstruct, parent, x, y, w, h, &args->object);
}
