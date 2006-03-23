#include "depui/config.h"
#include "depui/object/menu.h"
#include "depui/object/defsize.h"
#include "depui/args/args.h"
#include "depui/desktop/driver.h"
#include "depui/geometry/geometry.h"
#include "depui/pointer/pointer.h"
#include "depui/desktop/desktop.h"
#include "depui/event/focus.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void draw(MxMenu * menu, int x1, int y1, int x2, int y2)
{
	 int rhs;
	 const int border = abs(menu->base.listarea.border);
	 MxListDef *ptr = menu->base.listarea.def;
	 MxListDef *lastptr = 0;

	 /* Draw the border and reduce the remaining size */
	 MxFrameEmpty(x1, y1, x2, y2, menu->base.listarea.border, MxColorLight, MxColorDark);
	 x1 += border;
	 y1 += border;
	 x2 -= border;
	 y2 -= border;
	 rhs = x1;

	 /* Draw each of the entries of the menu */
	 while ((ptr) && (ptr->caption)) {

		  int next = rhs + ptr->w;
		  int fore = ptr->selected ? MxColorSelectedFore : MxColorFore;
		  int back = ptr->selected ? MxColorSelectedBack : MxColorBack;

		  MxFrameEmpty(rhs, y1, next - 1, y2, 2, back, back);
		  MxFontScreenRender(0, ptr->caption, MxFontDefault, rhs + 2, y1 + 2, fore, back);

		  rhs = next;
		  lastptr = ptr;
		  ++ptr;
	 }

	 /* Possibly fill in the blank area to the right */
	 if (rhs <= x2)
		  MxScreenRectFill(0, rhs, y1, x2, y2, MxColorBack);
}

/* Since the list will try to make us vertical, we have to correct it
   and adjust the size to make it horizontal */
static void size_correction(MxMenu * menu)
{
	 unsigned int width = 0;
	 MxListDef *ptr = menu->base.listarea.def;

	 while ((ptr) && (ptr->caption)) {

		  /* Switch the Y and X axis to make our menu horizontal */
		  ptr->y = width;

		  /* Find the total width */
		  width += ptr->w;

		  ++ptr;
	 }
	 /* Make our menu wide but not tall */
	 menu->base.listarea.maxw = width + 2 * abs(menu->base.listarea.border) - 1;
	 menu->base.listarea.maxh = MxFontHeight(MxFontDefault) + 3 + 2 * abs(menu->base.listarea.border);
}

/* Find out what entry an x-pixel lands on */
static MxListDef *whichdef(MxMenu * menu, int x)
{
	 MxListDef *ptr = menu->base.listarea.def;

	 /* Compensate for the menu's position */
	 x -= menu->base.object.position.x1 + abs(menu->base.listarea.border);

	 while ((ptr) && (ptr->caption)) {

		  /* Remember here Y and X are switched */
		  if ((x >= (int) ptr->y) && (x < (int) ptr->y + (int) ptr->w))
				return ptr;

		  ++ptr;
	 }
	 return 0;
}

/* The mouse has entered an menu element, open a submenu if possible */
static void activate(MxMenu * menu, MxListDef * def)
{
	 MxListDef *newdef = (MxListDef *) def->data;

	 /* Close any previous menus */
	 MxPopupClean();

	 /* Select the base menu of which element is opened */
	 MxListareaSelect(&menu->base.listarea, def, 0);

	 /* Open the menu if there is one */
	 if (newdef) {
		  MxMenupulldown *pop;
		  MxMenupulldownArgs args;

		  const int x = menu->base.object.position.x1 + def->y;
		  const int y = menu->base.object.position.y2 + 1;

		  MxArgsInit(&args);
		  args.listarea.def = newdef;

		  pop = MxMenupulldownStart(x, y, &args);
		  pop->top = menu;

		  mx_desk->popup = MxTrue;
		  menu->active = MxTrue;
		  menu->waiting = MxTrue;
	 }
}

/* Execute a menu element and close the menu */
void mx_menu_execute(MxMenu * menu, MxMenupulldown * menupd, MxListDef * def)
{
	 if (def) {

		  MxObject *object = (menu) ? &menu->base.object : &menupd->base.object;

		  /* Select the element, nad make sure the callback gets called */
		  def->selected = MxFalse;

		  /* Is it a pulldown menu bieng pressed */
		  if (menupd)
				MxListareaSelect(&menupd->base.listarea, def, object);

		  /* It is a toplevel menu being pressed */
		  else if (menu)
				MxListareaSelect(&menu->base.listarea, def, object);
	 }

	 /* Deselect the main menu and make us unactive */
	 if (menu) {
		  MxListareaSelect(&menu->base.listarea, 0, 0);
		  menu->active = MxFalse;
	 }
	 MxPopupClean();
}

void *MxMenuHandler(MxObject * object, const MxEvent * const event)
{
	 MxMenu *menu = (MxMenu *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw(menu, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

	 case MxEventListareaEnter:
		  if (menu->active)
				activate(menu, event->listelem.def);
		  break;

	 case MxEventListareaSelected:

		  /* Do we have a submenu to open */
		  if (event->listelem.def->data)
				activate(menu, event->listelem.def);

		  /* Otherwise run the callback and close everyting */
		  else
				mx_menu_execute(menu, 0, event->listelem.def);

		  break;

	 case MxEventButtonLeftPress:
		  menu->base.listarea.clicked = whichdef(menu, event->point.x);

		  if (menu->base.listarea.clicked) {
				menu->active = MxTrue;

				mx_listarea_inform(&menu->base.listarea, MxEventListareaSelected, menu->base.listarea.clicked);

				MxEnqueueRefresh(&menu->base.listarea.base.object, MxFalse);
		  }
		  break;

	 case MxEventPointerEnter:
		  MxPointerWantMove(object, MxTrue);

		  /* Fall through */

	 case MxEventPointerMove:{

				/* Which element is pointed to now */
				MxListDef *pointed = whichdef(menu, event->point.x);

				/* Has the pointed to element changed */
				if (pointed != menu->base.listarea.pointed) {

					 /* Tell the old one that they lost the pointer */
					 if (menu->base.listarea.pointed)
						  mx_listarea_inform(&menu->base.listarea, MxEventListareaLeave, menu->base.listarea.pointed);

					 /* Tell the new one that they got the pointer */
					 menu->base.listarea.pointed = pointed;
					 if (pointed)
						  mx_listarea_inform(&menu->base.listarea, MxEventListareaEnter, pointed);
				}
				break;
		  }

		  /* If we lost the pointer then forget which element was pointed to */
	 case MxEventPointerLeave:
		  if (menu->base.listarea.pointed)
				mx_listarea_inform(&menu->base.listarea, MxEventListareaLeave, menu->base.listarea.pointed);
		  menu->base.listarea.pointed = 0;
		  break;

		  /* If the parent changed size, we have to set our size too */
	 case MxEventGeomParentChanged:
		  MxResize(object, MxW(MxParent(object)) - 2, MxDefault);
		  break;

	 default:
		  return MxListareaHandler(object, event);
	 }
	 return 0;
}

void MxMenuConstruct(MxMenu * menu, MxObject * parent, int x, int y, int w, int h, MxMenuArgs * userargs)
{
	 MxMenuArgs args;

	 assert(menu);
	 MxUserArgsInit(args, userargs);

	 memset(menu, 0, sizeof(MxMenu));
	 MxListareaConstruct(&menu->base.listarea, parent, x, y, w, h, &args.listarea);
	 menu->base.object.handler = MxMenuHandler;

	 /* The list will make us vertical, so make us horizontal */
	 size_correction(menu);
	 MxGeomSize(&menu->base.object, (int) menu->base.listarea.maxw, (int) menu->base.listarea.maxh);

#ifdef MX_WINDOW_NAMES
	 menu->base.object.name = "MxMenu";
#endif
}

MxMenu *MxMenuNew(MxObject * parent, int x, int y, int w, int h, MxMenuArgs * args)
{
	 return (MxMenu *) MxNewObject(sizeof(MxMenu), (MxVoidFunc) MxMenuConstruct, parent, x, y, w, h, &args->object);
}
