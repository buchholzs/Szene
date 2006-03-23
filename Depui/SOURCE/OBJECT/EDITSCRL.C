#include "depui/config.h"
#include "depui/args/args.h"
#include "depui/object/edit.h"
#include "depui/event/focus.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxScrollEditareaEditareaHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

		  /* Pass the drop event to the scroller */
	 case MxEventDropTarget:
		  return MxEventSend(MxParent(MxParent(object)), event);

		  /* Element asks for a scroll, pass it up to the scroller */
	 case MxEventScrollRect:
		  MxEventSend(MxParent(object), event);
		  break;

	 default:
		  return MxEditareaHandler(object, event);
	 }
	 return 0;
}

void *MxScrollEditareaPanelHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

		  /* Pass the focus to the editable textarea object when we are clicked 
		   */
	 case MxEventButtonLeftPress:
		  MxFocusSet(MxFirstChild(object));
		  break;

	 default:
		  return MxScrollVisibleHandler(object, event);
	 }
	 return 0;
}

void *MxScrollEditareaHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 return MxScrollHandler(object, event);
}

void MxScrollEditareaConstruct(MxScrollEditarea * area, MxObject * parent, int x, int y, int w, int h, MxScrollEditareaArgs * userargs)
{
	 MxScrollEditareaArgs args;

	 assert(area);
	 MxUserArgsInit(args, userargs);

	 args.scroll.border -= 1;

	 /* Construct the underlying area */
	 memset(area, 0, sizeof(MxScrollEditarea));
	 MxEditareaConstruct(&area->editarea, 0, 0, 0, w - 4, h - 4, &args.editarea);
	 area->editarea.base.object.handler = MxScrollEditareaEditareaHandler;

	 /* Construct the scroller itself */
	 if (!args.scroll.client)
		  args.scroll.client = &area->editarea.base.object;

	 MxScrollConstruct(&area->base.scroll, parent, x, y, w, h, &args.scroll);
	 area->base.scroll.visible.base.object.handler = MxScrollEditareaPanelHandler;

#ifdef MX_WINDOW_NAMES
	 area->base.object.name = "MxScrollEditarea";
#endif
}

MxScrollEditarea *MxScrollEditareaNew(MxObject * parent, int x, int y, int w, int h, MxScrollEditareaArgs * args)
{
	 return (MxScrollEditarea *) MxNewObject(sizeof(MxScrollEditarea), (MxVoidFunc)
														  MxScrollEditareaConstruct, parent, x, y, w, h, &args->object);
}
