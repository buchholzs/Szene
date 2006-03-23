#include "depui/config.h"
#include "depui/object/menu.h"
#include "depui/args/args.h"
#include "depui/geometry/geometry.h"
#include "depui/desktop/driver.h"
#include "depui/desktop/desktop.h"
#include "depui/event/focus.h"
#include "depui/event/queue.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Destroy and childmenus we might have open */
static void close_submenu(MxMenupulldown * menu)
{
	 menu->top->waiting = MxFalse;
	 if (menu->child) {
		  MxMenupulldown *pop = menu->child;

		  while (pop) {
				MxMenupulldown *next = pop->child;

				MxDestroy(&pop->base.object);

				pop = next;
		  }
		  menu->child = 0;
	 }
	 menu->top->waiting = MxTrue;
}

static void activate(MxMenupulldown * menu, MxListDef * clicked)
{
	 MxListDef *def = (MxListDef *) clicked->data;

	 close_submenu(menu);

	 MxListareaSelect(&menu->base.listarea, clicked, 0);

	 if ((def) && (clicked)) {
		  MxMenupulldown *pop;
		  MxMenupulldownArgs args;

		  const int x = menu->base.object.position.x2 + 1;
		  const int y = menu->base.object.position.y1 + clicked->y;

		  MxArgsInit(&args);
		  args.listarea.def = def;

		  /* Make the new submenu */
		  pop = MxMenupulldownStart(x, y, &args);

		  pop->top = menu->top;
		  menu->child = pop;
	 }
}

void *MxMenupulldownHandler(MxObject * object, const MxEvent * const event)
{
	 MxMenupulldown *menu = (MxMenupulldown *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  mx_listarea_draw(&menu->base.listarea, object->position.x1, object->position.y1, object->position.x2, object->position.y2,
								 event->region.region, MxColorFore, MxColorBack);
		  break;

	 case MxEventButtonLeftPress:
		  mx_listarea_press(&menu->base.listarea, event->point.y, MxFalse);
		  break;

	 case MxEventListareaEnter:
		  activate(menu, event->listelem.def);
		  break;

	 case MxEventListareaSelected:

		  /* Do we have a submenu to open */
		  if (event->listelem.def->data)
				activate(menu, event->listelem.def);

		  /* Otherwise run the callback and close everyting */
		  else
				mx_menu_execute(menu->top, menu, event->listelem.def);

		  break;

	 case MxEventZOrderInform:
		  MxZOrder(object, 0);
		  break;

	 case MxEventDestroy:
		  if ((menu->top) && (menu->top->waiting)) {
				menu->top->active = MxFalse;

				if (menu->top->base.listarea.clicked)
					 MxListareaSelect(&menu->top->base.listarea, 0, 0);
		  }
		  /* Fall through */

	 default:
		  return MxListareaHandler(object, event);
	 }
	 return 0;
}

MxMenupulldown *MxMenupulldownStart(int x, int y, MxMenupulldownArgs * userargs)
{
	 MxMenupulldown *menu = (MxMenupulldown *) MxMalloc(sizeof(MxMenupulldown));

	 assert(menu);

	 if (menu) {
		  MxMenupulldownArgs args;

		  memset(menu, 0, sizeof(MxMenupulldown));

		  MxUserArgsInit(args, userargs);

		  /* Default we have a border */
		  args.listarea.border += 1;

		  MxListareaConstruct(&menu->base.listarea, mx_desk, x, y, 0, 0, &args.listarea);
		  menu->base.object.handler = MxMenupulldownHandler;
		  menu->base.object.popup = MxTrue;

		  /* We have to release memory when we get destroyed */
		  menu->base.object.allocated = MxTrue;

		  /* Start with the corret size */
		  MxGeomSize(&menu->base.object, (int) menu->base.listarea.maxw, (int) menu->base.listarea.maxh);

		  /* Start with deselected elements */
		  MxListareaSelect(&menu->base.listarea, 0, 0);

#ifdef MX_WINDOW_NAMES
		  menu->base.object.name = "MxMenu";
#endif
	 }
	 return menu;
}
