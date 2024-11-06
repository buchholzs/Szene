#include "depui/config.h"
#include "depui/object/scroll.h"
#include "depui/object/defsize.h"
#include "depui/args/args.h"
#include "depui/draw/draw.h"
#include "depui/desktop/driver.h"
#include "depui/event/focus.h"
#include "depui/event/queue.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/draw.h"
#include "depui/geometry/geometry.h"
#include <stdlib.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxScrollVisibleHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

		  /* Does someone want to drop something on us, then pass the event to
		     the scroller i.e. the list */
	 case MxEventDropTarget:
		  return MxEventSend(MxParent(object), event);

		  /* If the underlying object has changed size, pass it to the scroller 
		   */
	 case MxEventGeomChildChanged:
		  MxEventSend(MxParent(object), event);
		  break;

		  /* Client asks for a scroll, pass it up to the scroller */
	 case MxEventScrollRect:
		  MxEventSend(MxParent(object), event);
		  break;

	 default:
		  return MxPanelHandler(object, event);
	 }
	 return 0;
}

static void draw_scroll(const MxScroll * const scroll, int x1, int y1, int x2, int y2)
{
	 const int hoff = scroll->vslider ? scroll->slider_size + 1 : 0;
	 const int voff = scroll->hslider ? scroll->slider_size + 1 : 0;

	 if (scroll->border)
		  MxFrameEmpty(x1, y1, x2 - hoff, y2 - voff, scroll->border, MxColorDark, MxColorLight);

	 /* Fill in the lower corner if we have two scroll bars */
	 if ((hoff) && (voff))
		  MxScreenRectFill(0, x2 - hoff + 1, y2 - voff + 1, x2, y2, MxColorBack);
}

static void _scroll_geometry(MxScroll * scroll)
{
	 MxGeomFlags clientflags = (MxGeomFlags) (MxGeomW | MxGeomH);
	 int clientx = 0;
	 int clienty = 0;

	 int cw = 0;
	 int ch = 0;

	 const MxObject *object = &scroll->base.object;
	 MxSliderArgs sliderargs;

	 const int border = abs(scroll->border);
	 const int dborder = 2 * border;

	 int vw = MxW(object) - dborder;
	 int vh = MxH(object) - dborder;

	 unsigned int needv = MxFalse, needh = MxFalse;

	 MxSlider *had_vslider = scroll->vslider;
	 MxSlider *had_hslider = scroll->hslider;

	 MX_TRACE(scroll->base.object.name);

	 /* How big does the client need to be? Ask them to be small and see what
	    size they want */
	 if (scroll->client) {
		  cw = vw - (scroll->slider_size + 1);
		  ch = vh - (scroll->slider_size + 1);

		  MxGeomQuery(scroll->client, 0, 0, &cw, &ch, (MxGeomFlags) (MxGeomW | MxGeomH));
	 }

	 /* Do we need a vertical scrollbar */
	 if ((vh < ch) && (!scroll->no_vscroll)) {
		  needv = MxTrue;
		  vw -= (scroll->slider_size + 1);
	 }

	 /* Do we need a horizontal scrollbar */
	 if ((vw < cw) && (!scroll->no_hscroll)) {
		  needh = MxTrue;
		  vh -= (scroll->slider_size + 1);
	 }

	 /* Do we need a vertical scrollbar because of the horizontal scrollbar */
	 if ((vh < ch) && (needv == MxFalse) && (!scroll->no_vscroll)) {
		  needv = MxTrue;
		  vw -= (scroll->slider_size + 1);
	 }

	 /* Do we need a horizontal scrollbar because of the vertical scrollbar */
	 if ((vw < cw) && (needh == MxFalse) && (!scroll->no_hscroll)) {
		  needh = MxTrue;
		  vh -= (scroll->slider_size + 1);
	 }

	 /* If we don't need a scrollbar then we can force the offset to zero and
	    also check to see if the client has already been scrolled too far up
	    or to the so that the scrollbar won't look right */
	 if (scroll->client) {

		  if (!needh) {
				clientflags = (MxGeomFlags) (clientflags | MxGeomX);

		  } else {
				const int right = cw - vw + MxX(scroll->client);

				if (right < 0) {

					 clientx = MxX(scroll->client) - right;
					 clientflags = (MxGeomFlags) (clientflags | MxGeomX);
				}
		  }

		  if (!needv) {
				clientflags = (MxGeomFlags) (clientflags | MxGeomY);

		  } else {
				const int bottom = ch - vh + MxY(scroll->client);

				if (bottom < 0) {

					 clienty = MxY(scroll->client) - bottom;
					 clientflags = (MxGeomFlags) (clientflags | MxGeomY);
				}
		  }
	 }

	 /* Position the visible area, and the basic scroll */
	 MxGeomRequest(&scroll->visible.base.object, border, border, vw, vh, (MxGeomFlags) (MxGeomX | MxGeomY | MxGeomW | MxGeomH));

	 /* Tell the client exactly what size was used */
	 if (scroll->client) {
		  unsigned int needredraw = MxFalse;

		  /* Redraw the object if we have to move it */
		  if (((clientx != MxX(scroll->client)) || (clienty != MxY(scroll->client))))
				needredraw = MxTrue;

		  MxGeomRequest(scroll->client, clientx, clienty, vw, vh, clientflags);

		  if (needredraw)
				MxEnqueueRefresh(scroll->client, MxFalse);
	 }

	 MxArgsInit(&sliderargs);
	 sliderargs.target = &scroll->base.object;

	 sliderargs.border = scroll->slider_border;
	 sliderargs.range = ch;
	 sliderargs.thumb = vh;

	 /* Create and place a vertical scrollbar */
	 if ((needv) && (!scroll->vslider))
		  scroll->vslider = MxSliderVNew(&scroll->base.object, 0, 0, scroll->slider_size, 0, &sliderargs);

	 if ((!needv) && (scroll->vslider)) {
		  MxDestroy(&scroll->vslider->base.object);
		  scroll->vslider = 0;
	 }

	 if (scroll->vslider) {
		  MxGeomPosition(&scroll->vslider->base.object, vw + 1 + dborder, 0);
		  MxGeomSize(&scroll->vslider->base.object, MxDefault, vh + dborder);

		  if (scroll->vslider->base.object.init)
				MxEnqueueRefresh(&scroll->vslider->base.object, MxFalse);

		  scroll->vslider->index = -MxY(scroll->client);
		  scroll->vslider->range = ch;
		  scroll->vslider->thumb = vh;
	 }

	 sliderargs.border = scroll->slider_border;
	 sliderargs.range = cw;
	 sliderargs.thumb = vw;

	 /* Create and place a horizontal scrollbar */
	 if ((needh) && (!scroll->hslider))
		  scroll->hslider = MxSliderHNew(&scroll->base.object, 0, 0, 0, scroll->slider_size, &sliderargs);

	 if ((!needh) && (scroll->hslider)) {
		  MxDestroy(&scroll->hslider->base.object);
		  scroll->hslider = 0;
	 }

	 if (scroll->hslider) {
		  MxGeomPosition(&scroll->hslider->base.object, 0, vh + 1 + dborder);
		  MxGeomSize(&scroll->hslider->base.object, vw + dborder, MxDefault);

		  if (scroll->hslider->base.object.init)
				MxEnqueueRefresh(&scroll->hslider->base.object, MxFalse);

		  scroll->hslider->index = -MxX(scroll->client);
		  scroll->hslider->range = cw;
		  scroll->hslider->thumb = vw;
	 }

	 /* Update the whole object if we gained or lost a scrollbar.  This may
	    not be perfectly efficient, but it makes sure that screen is updated
	    properly */
	 if ((had_vslider != scroll->vslider) || (had_hslider != scroll->hslider)) {

		  if (scroll->base.object.init)
				MxEnqueueRefresh(&scroll->base.object, MxFalse);
	 }
}

void *MxScrollHandler(MxObject * object, const MxEvent * const event)
{
	 MxScroll *scroll = (MxScroll *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw_scroll(scroll, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

	 case MxEventPreInit:
	 case MxEventGeomChanged:
	 case MxEventGeomChildChanged:
		  _scroll_geometry(scroll);
		  break;

	 case MxEventSlider:
		  if (scroll->client) {

				/* Or a horizontal scroll */
				if (event->slider.source == scroll->hslider)
					 MxMove(scroll->client, -event->slider.offset, MxDefault);

				/* Is it a vertical scroll */
				else if (event->slider.source == scroll->vslider)
					 MxMove(scroll->client, MxDefault, -event->slider.offset);
		  }
		  break;

		  /* Client asks for a scroll */
	 case MxEventScrollRect:{

				int x = MxDefault;
				int y = MxDefault;

				const int lft = scroll->visible.base.object.position.x1 - event->rect.rect.x1;
				const int top = scroll->visible.base.object.position.y1 - event->rect.rect.y1;
				const int rgt = scroll->visible.base.object.position.x2 - event->rect.rect.x2;
				const int bot = scroll->visible.base.object.position.y2 - event->rect.rect.y2;

				/* Do we need to scroll left */
				if (rgt < 0)
					 x = MxX(scroll->client) + rgt;

				/* Do we need to scroll up */
				if (bot < 0)
					 y = MxY(scroll->client) + bot;

				/* Do we need to scroll the right */
				if (lft > 0)
					 x = MxX(scroll->client) + lft;

				/* Do we need to scroll down */
				if (top > 0)
					 y = MxY(scroll->client) + top;

				/* Actually do the scrolling */
				if ((x != MxDefault) || (y != MxDefault)) {
					 MxMove(scroll->client, x, y);

					 /* Update the object and the scrollbars */
					 MxEnqueueRefresh(scroll->client, MxFalse);
					 if (scroll->vslider) {
						  scroll->vslider->index = -MxY(scroll->client);
						  MxEnqueueRefresh(&scroll->vslider->base.object, MxFalse);
					 }
					 if (scroll->hslider) {
						  scroll->hslider->index = -MxX(scroll->client);
						  MxEnqueueRefresh(&scroll->hslider->base.object, MxFalse);
					 }
				}
				break;
		  }

	 case MxEventFocusGot:
	 case MxEventFocusLost:
		  MxEnqueueRefresh(object, MxFalse);
		  return object;

	 default:
		  break;
	 }
	 return 0;
}

void MxScrollConstruct(MxScroll * scroll, MxObject * parent, int x, int y, int w, int h, MxScrollArgs * userargs)
{
	 MxScrollArgs args;
	 MxPanelArgs panelargs;

	 assert(scroll);
	 MxUserArgsInit(args, userargs);

	 /* Construct the object itself */
	 memset(scroll, 0, sizeof(MxScroll));
	 MxObjectConstruct(&scroll->base.object, parent, x, y, w, h, &args.object);
	 scroll->base.object.handler = MxScrollHandler;

	 /* Construct the visible area */
	 MxArgsInit(&panelargs);
	 panelargs.color = MxColorObjectBack;
//  panelargs.color = MxColorFocus;
	 panelargs.hascolor = MxTrue;
	 MxPanelConstruct(&scroll->visible, &scroll->base.object, 2, 2, w - 4, h - 4, &panelargs);
	 scroll->visible.base.object.handler = MxScrollVisibleHandler;

#ifdef MX_WINDOW_NAMES
	 scroll->visible.base.object.name = "MxScrollVisible";
#endif

	 /* Add the scrollable client under our visible area */
	 scroll->client = args.client;
	 if (scroll->client)
		  MxInsert(scroll->client, &scroll->visible.base.object, MxFalse);

	 /* Start with no scrollbars */
	 scroll->vslider = 0;
	 scroll->hslider = 0;
	 scroll->no_vscroll = args.no_vscroll;
	 scroll->no_hscroll = args.no_hscroll;
	 scroll->border = args.border + 1;

	 /* We don't draw over our children, so we can draw fast */
	 scroll->base.object.Fastdraw = MxTrue;

	 scroll->slider_border = args.slider_border;
	 if (args.slider_size)
		  scroll->slider_size = args.slider_size;
	 else
		  scroll->slider_size = MxSliderDefaultSize;

#ifdef MX_WINDOW_NAMES
	 scroll->base.object.name = "MxScroll";
#endif
}
