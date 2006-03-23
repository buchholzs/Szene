#include "depui/config.h"
#include "depui/macros.h"
#include "depui/args/args.h"
#include "depui/object/list.h"
#include "depui/event/queue.h"
#include "depui/event/focus.h"
#include "depui/desktop/driver.h"
#include "depui/geometry/geometry.h"
#include "depui/pointer/pointer.h"
#include "depui/object/text.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void drawline(MxListarea * list, const MxListDef * const def, int x1, int y1, int x2, int y2, MxColor fore, MxColor back)
{
	 /* Find the correct colors for the element */
	 MxColor ring = back;

	 if ((def) && (def->selected)) {
		  fore = MxColorSelectedFore;
		  back = MxColorSelectedBack;
		  ring = MxColorSelectedBack;
	 }

	 if ((def) && (def->disabled))
		  fore = MxColorDisabled;

	 /* Maybe draw a focus ring around it */
	 if ((MxFocus() == &list->base.object) && (def == list->clicked))
		  ring = MxColorFocus;

	 /* Is it a normal list entry */
	 if (def->caption[0])
		  mx_draw_tab_text(&list->base.object, list->tabstop, def->caption, x1, y1, x2, y2, 2, fore, back, ring);

	 /* Or is it a seperator */
	 else {
		  MxScreenRectFill(0, x1, y1, x2, y2, back);
		  MxScreenHLine(0, x1 + 2, (y1 + y2) / 2, x2 - 2, fore);
	 }
}

void mx_listarea_draw(MxListarea * list, int x1, int y1, int x2, int y2, const MxRegion * const region, MxColor fore, MxColor back)
{
	 int bot;
	 const int border = abs(list->border);
	 MxListDef *ptr = list->def;
	 MxListDef *lastptr = 0;

	 /* Get the extent of the region so we can maybe skip some lines */
	 MxRect rect;
	 const unsigned int regionvalid = MxRegionExtent(region, &rect);

	 assert(list);
	 assert(region);

	 /* Draw the border and reduce the remaining size */
	 MxFrameEmpty(x1, y1, x2, y2, list->border, MxColorLight, MxColorDark);
	 x1 += border;
	 y1 += border;
	 x2 -= border;
	 y2 -= border;

	 bot = y1;

	 while ((ptr) && (ptr->caption)) {

		  /* Assume we have to draw the line */
		  unsigned int mustdraw = MxTrue;

		  /* Can we skip the line */
		  if (regionvalid) {
				if ((y1 + (int) ptr->y > rect.y2) || (y1 + (int) ptr->y + (int) ptr->h < rect.y1))
					 mustdraw = MxFalse;
		  }

		  /* Draw the line if we have to */
		  if (mustdraw)
				drawline(list, ptr, x1, y1 + ptr->y, x2, y1 + ptr->y + ptr->h - 1, fore, back);

		  lastptr = ptr;
		  ++ptr;
	 }

	 /* Possibly fill in the blank area underneath */
	 if (lastptr)
		  bot += lastptr->y + lastptr->h;

	 if (bot <= y2)
		  MxScreenRectFill(0, x1, bot, x2, y2, back);
}

/* Find out what entry a y-pixel lands on */
static MxListDef *whichdef(MxListarea * list, int y)
{
	 MxListDef *ptr = list->def;

	 /* Correct for the objects position */
	 y -= list->base.object.position.y1 + abs(list->border);

	 while ((ptr) && (ptr->caption)) {

		  if ((y >= (int) ptr->y) && (y < (int) ptr->y + (int) ptr->h) && (ptr->caption[0]))
				return ptr;

		  ++ptr;
	 }
	 return 0;
}

void mx_listarea_inform(MxListarea * list, MxEventType type, MxListDef * hit)
{
	 MxEvent event;

	 event.type = type;
	 event.listelem.def = hit;

	 MxEventSend(&list->base.object, &event);
}

void MxListareaSelect(MxListarea * list, MxListDef * hit, MxObject * object)
{
	 MxListDef *ptr = list->def;
	 unsigned int wasselected = (hit) ? hit->selected : MxTrue;

	 assert(list);

	 /* Remember what the last selected was */
	 list->clicked = hit;

	 /* Maybe we have multiple selections */
	 if ((hit) && (list->multiple)) {
		  hit->selected = !hit->selected;

		  /* We know the elements state has changed, so call the callback */
		  if ((object) && (hit->callback))
				hit->callback(object, hit->data, hit->selected);

		  return;
	 }

	 /* Select our one element */
	 if (hit)
		  hit->selected = MxTrue;

	 /* If the elements state has changed, call the callback */
	 if ((object) && (hit) && (hit->callback) && (!wasselected))
		  hit->callback(object, hit->data, MxTrue);

	 /* Deselect other list elements */
	 while ((ptr) && (ptr->caption)) {

		  /* Only if it was npt already selected */
		  if ((ptr != hit) && (ptr->selected)) {
				ptr->selected = MxFalse;

				/* If the elements state has changed, call the callback */
				if ((object) && (ptr->callback))
					 ptr->callback(object, ptr->data, MxFalse);
		  }
		  /* Look at the next list entry */
		  ++ptr;
	 }

	 /* Refresh the object if we need to */
	 if (list->base.object.init)
		  MxEnqueueRefresh(&list->base.object, MxFalse);
}

void mx_listarea_press(MxListarea * list, int y, unsigned int focus)
{
	 list->clicked = whichdef(list, y);

	 if (list->clicked) {
		  if (focus) {
				MxFocusSet(&list->base.object);
				MxEnqueueRefresh(&list->base.object, MxFalse);
		  }
		  mx_listarea_inform(list, MxEventListareaSelected, list->clicked);
	 }
}

void *MxListareaHandler(MxObject * object, const MxEvent * const event)
{
	 MxListarea *list = (MxListarea *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  mx_listarea_draw(list, object->position.x1, object->position.y1, object->position.x2, object->position.y2,
								 event->region.region, MxColorObjectFore, MxColorObjectBack);
		  break;

	 case MxEventButtonLeftPress:
		  mx_listarea_press(list, event->point.y, MxTrue);
		  break;

	 case MxEventListareaSelected:
		  MxListareaSelect(list, event->listelem.def, object);
		  break;

	 case MxEventGeomRequest:
		  if (event->geom.data->flags & MxGeomW)
				event->geom.data->w = MX_MAX(event->geom.data->w, (int) list->maxw);

		  if (event->geom.data->flags & MxGeomH)
				event->geom.data->h = MX_MAX(event->geom.data->h, (int) list->maxh);
		  break;

	 case MxEventDestroy:

		  /* Cleanup our parsing info also */
		  if ((list->ownsdef) && (list->def))
				MxFree(list->def);

		  break;

	 case MxEventPointerEnter:
		  MxPointerWantMove(object, MxTrue);

		  /* Fall through */

	 case MxEventPointerMove:{

				/* Which element is pointed to now */
				MxListDef *pointed = whichdef(list, event->point.y);

				/* Has the pointed to element changed */
				if (pointed != list->pointed) {

					 /* Tell the old one that they lost the pointer */
					 if (list->pointed)
						  mx_listarea_inform(list, MxEventListareaLeave, list->pointed);

					 /* Tell the new one that they got the pointer */
					 list->pointed = pointed;
					 if (pointed)
						  mx_listarea_inform(list, MxEventListareaEnter, pointed);
				}
				break;
		  }

		  /* If we lost the pointer then forget which element was pointed to */
	 case MxEventPointerLeave:
		  if ((object->clicked) && (list->clicked))
				mx_listarea_inform(list, MxEventListareaDrag, list->clicked);

		  if (list->pointed)
				mx_listarea_inform(list, MxEventListareaLeave, list->pointed);
		  list->pointed = 0;
		  break;

		  /* Fall through */
	 case MxEventFocusLost:
		  MxEnqueueRefresh(object, MxFalse);
		  break;

	 default:
		  return 0;
	 }
	 return 0;
}

void MxListareaConstruct(MxListarea * list, MxObject * parent, int x, int y, int w, int h, MxListareaArgs * userargs)
{
	 MxListareaArgs args;

	 assert(list);
	 MxUserArgsInit(args, userargs);

	 memset(list, 0, sizeof(MxListarea));
	 MxObjectConstruct(&list->base.object, parent, x, y, w, h, &args.object);
	 list->base.object.handler = MxListareaHandler;

	 list->border = args.border;
	 list->tabstop = args.tabstop;
	 list->multiple = args.multiple;

	 /* Set the list definition */
	 if (args.def)
		  MxListDefSet(list, args.def, args.ownsdef);

#ifdef MX_WINDOW_NAMES
	 list->base.object.name = "MxListarea";
#endif
}

MxListarea *MxListareaNew(MxObject * parent, int x, int y, int w, int h, MxListareaArgs * args)
{
	 return (MxListarea *) MxNewObject(sizeof(MxListarea), (MxVoidFunc) MxListareaConstruct, parent, x, y, w, h, &args->object);
}

void MxListDefSet(MxListarea * list, MxListDef * def, unsigned int owns)
{
	 const unsigned int height = MxFontHeight(MxFontDefault) + 4;

	 assert(list);

	 MX_TRACE("");

	 /* Cleanup old definitions */
	 if ((list->ownsdef) && (list->def) && (list->def != def))
		  MxFree(list->def);
	 list->def = def;
	 list->ownsdef = owns;

	 /* Cleanup object state */
	 list->maxw = 0;
	 list->maxh = 0;
	 list->clicked = 0;
	 list->pointed = 0;

	 /* Parse each line of the list */
	 while ((def) && (def->caption)) {

		  /* Fill in info about the list definition */
		  def->y = list->maxh;
		  def->w = MxFontLength(MxFontDefault, def->caption) + 4;
		  if (def->caption[0])
				def->h = height;
		  else
				def->h = height / 2;

		  /* Keep track of our max size */
		  if (def->w > list->maxw)
				list->maxw = def->w;
		  list->maxh += def->h;

		  /* Goto the next line */
		  ++def;
	 }

	 /* Make the requested size larger for a border */
	 list->maxh += 2 * abs(list->border) - 1;
	 list->maxw += 2 * abs(list->border) - 1;

	 /* Update if necessary */
	 if (list->base.object.init) {
		  MxResize(&list->base.object, list->maxw, list->maxh);
		  MxEventSendSimple(MxParent(&list->base.object), MxEventGeomChildChanged);
		  MxEnqueueRefresh(&list->base.object, MxFalse);
	 }
}

void MxListareaAppend(MxListarea * list, const MxListDef * const def)
{
	 MxListDef *temp = MxListDefAppend(list->def, def);

	 MxListDefSet(list, temp, MxTrue);
}

void MxListareaRemove(MxListarea * list, const MxListDef * const def)
{
	 const unsigned int found = MxListDefRemove(list->def, def);

	 if (found)
		  MxListDefSet(list, list->def, list->ownsdef);
}
