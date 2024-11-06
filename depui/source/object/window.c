#include "depui/config.h"
#include "depui/macros.h"
#include "depui/pointer/pointer.h"
#include "depui/event/queue.h"
#include "depui/event/focus.h"
#include "depui/desktop/driver.h"
#include "depui/desktop/desktop.h"
#include "depui/object/defsize.h"
#include "depui/object/window.h"
#include "depui/object/mover.h"
#include "depui/object/panel.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/decorate.h"
#include "depui/geometry/geometry.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxWindowClientPanelHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

		  /* Pass some simple events to it's parent */
	 case MxEventOk:
	 case MxEventCancel:
	 case MxEventExit:
		  return MxEventSend(MxParent(object), event);

	 default:
		  return MxPanelHandler(object, event);
	 }
	 return 0;
}

static void draw_window(MxWindow * window, int x1, int y1, int x2, int y2)
{
	 int top;

	 const int title_height = MxFontHeight(MxFontDefault) + 2;
	 const int title_width = MxFontLength(MxFontDefault, window->caption) + 1;
	 const int barheight = (window->menu) ? MxH(&window->menu->base.object) + 1 : 0;

	 MxColor fore_color = MxColorFore;
	 MxColor back_color = MxColorBack;

	 if (MxActive() == &window->base.object) {
		  fore_color = MxColorSelectedFore;
		  back_color = MxColorSelectedBack;
	 }

	 /* Draw the entire frame */
	 MxFrameEmpty(x1, y1, x2, y2, 1, window->modal ? MxColorLight : MxColorDark, MxColorDark);

	 /* Find out where the client top should be */
	 top = y1 + title_height + 1 + barheight;
	 if (barheight)
		  ++top;

	 MxScreenHLine(0, x1 + 1, top, x2 - 1, MxColorDark);

	 /* Draw the part by the title */
	 MxFontScreenRender(0, window->caption, MxFontDefault, x1 + 2, y1 + 2, fore_color, back_color);
	 MxScreenHLine(0, x1 + 1, y1 + 1, x1 + title_width, back_color);
	 MxScreenVLine(0, x1 + 1, y1 + 1, y1 + title_height - 1, back_color);
	 MxScreenHLine(0, x1 + 1, y1 + title_height, x1 + title_width, back_color);
	 MxScreenRectFill(0, x1 + title_width + 1, y1 + 1, x2 - 1, y1 + title_height, back_color);

	 {									  /* Draw the border */
		  const int bot = (!window->unresizeable) ? y2 - 7 : y2 - 1;
		  int top = y1 + title_height + 2;

		  if (barheight)
				top += barheight + 1;

		  MxFrameEmpty(x1 + 1, top, x2 - 1, bot, window->border, MxColorBack, MxColorBack);
	 }

	 if (barheight)
		  MxScreenHLine(0, x1 + 1, y1 + title_height + 1, x2 - 1, MxColorBack);

	 /* Draw the close decoration */
	 if (!window->uncloseable)
		  MxDecorate(MxDecorationClose, x2 - 2 - MxDecorationClose->width, y1 + 2);

	 /* Draw decorations for resizing */
	 if (!window->unresizeable) {
		  MxScreenRectFill(0, x1 + 1, y2 - 6, x2 - 1, y2 - 1, MxColorBack);
		  MxDecorate(MxDecorationResize, x2 - 6, y2 - 6);
	 }

	 /* If the client is hidden, draw the background */
	 if (!window->client)
		  MxScreenRectFill(0, x1 + 2, y1 + title_height + 2, x2 - 2, y2 - 2, MxColorBack);
}

static void _window_geometry(MxWindow * window)
{
	 const int w = MxW(&window->base.object);
	 const int h = MxH(&window->base.object);
	 const int border = abs(window->border);
	 const int barheight = (window->menu) ? MxH(&window->menu->base.object) + 1 : 0;
	 int title_height = MxFontHeight(MxFontDefault) + barheight + 1;
	 int bottom = 0;

	 /* Make sure the menu is in the right place */
	 if (window->menu) {
		  const int menupos = MxFontHeight(MxFontDefault) + 2;

		  MxMove(&window->menu->base.object, 1, menupos + 2);
		  MxResize(&window->menu->base.object, MxW(&window->base.object) - 2, MxDefault);
	 }

	 /* Put a little extra room for a seperator line between title and
	    whatever (probably a menu) is in the bar */
	 if (barheight)
		  ++title_height;

	 if (!window->unresizeable)
		  bottom += MxDecorationResize->height;

	 MxGeomRequest(window->client, 1 + border, title_height + 3 + border, w - 2 - 2 * border,
						h - title_height - 4 - bottom - 2 * border, (MxGeomFlags) (MxGeomX | MxGeomY | MxGeomW | MxGeomH));
}

static void _window_resize(MxWindow * window, const MxEventGeom * event)
{
	 const int barheight = (window->menu) ? MxH(&window->menu->base.object) + 1 : 0;
	 const int t = MxFontHeight(MxFontDefault) + 10 + barheight;

	 /* Find out the size wants to be affected */
	 if (event->data->flags & MxGeomW)
		  event->data->w = MX_MAX(event->data->w, t * 3);

	 if (event->data->flags & MxGeomH)
		  event->data->h = MX_MAX(event->data->h, t);
}

static void active_refresh(MxWindow * window)
{
	 MxRegion toupdate;
	 MxRect titlebar;

	 /* Get the objects visible region */
	 MxVisible(&window->base.object);
	 MxRegionCopyConstruct(&toupdate, &window->base.object.region);

	 /* Find where out titlebar is */
	 titlebar = window->base.object.position;
	 titlebar.y1 += MxFontHeight(MxFontDefault) + 3;

	 /* Only update the region of the titlebar */
	 MxRegionClipRect(&toupdate, &titlebar);
	 MxEnqueueRefreshRegion(&toupdate);

	 MxRegionDestruct(&toupdate);
}

static void activate(MxWindow * window)
{
	 if (MxActive() != &window->base.object)
		  MxActiveSet(&window->base.object, 0);
}

static void handle_press(MxWindow * window, int x, int y)
{
	 MxObject *object = &window->base.object;

	 const int titlebar = object->position.y1 + MxFontHeight(MxFontDefault) + 2;

	 activate(window);

	 /* Are we clicked in the bottom right */
	 if ((x > object->position.x2 - 11)
		  && (y > object->position.y2 - 6)) {

		  /* Are we doing a resize */
		  if (!window->unresizeable) {
				window->resizeing = MxTrue;

				MxPointerGrab(object);
				MxPointerWantMove(object, MxTrue);
		  }

		  /* Are we clicked in the top right */
	 } else if ((x > object->position.x2 - 11)
					&& (y < object->position.y1 + MxDecorationClose->height + 2)) {

		  if (!window->uncloseable)
				MxEventSendSimple(object, MxEventExit);

		  /* Are we doing a move */
	 } else if (y < titlebar) {

		  if (!window->unmovable) {
				window->moving = MxTrue;

				MxPointerGrab(object);
				MxPointerWantMove(object, MxTrue);
		  }
	 }
}

static void modal_init(MxWindow * window)
{
	 if (!window->modal)
		  return;

	 /* Block the window that we should block */
	 window->blocked->blocked = MxTrue;

	 /* Make us the active window, and remember the previous active window */
	 MxActiveSet(&window->base.object, window);
}

static void modal_done(MxWindow * window)
{
	 if (!window->modal)
		  return;

	 /* Unblock the blocked window */
	 assert(window->blocked->blocked);
	 window->blocked->blocked = MxFalse;
	 window->blocked = 0;

	 MxActiveSet(0, 0);
}

void MxWindowModal(MxWindow * window, unsigned int makemodal, MxObject * blocked)
{
	 if (makemodal == window->modal)
		  return;

	 /* Make a modal window */
	 if ((makemodal) && (blocked)) {
		  window->modal = MxTrue;
		  window->blocked = blocked;

		  /* Init the window if necessary */
		  if (!window->base.object.init)
				modal_init(window);
	 }

	 /* Take away modality from a window */
	 if (!makemodal) {

		  if (window->base.object.init)
				modal_done(window);

		  window->modal = MxFalse;
		  window->blocked = 0;
	 }
}

void *MxWindowHandler(MxObject * object, const MxEvent * const event)
{
	 MxWindow *window = (MxWindow *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventDestroy:

		  /* Replace any modality */
		  if (window->modal)
				modal_done(window);

		  /* Free the caption of the window */
		  if ((window->ownscaption) && (window->caption))
				MxFree((char *) window->caption);
		  break;

	 case MxEventExpose:
		  draw_window(window, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

	 case MxEventButtonRightPressChild:
	 case MxEventButtonCenterPressChild:
		  activate(window);
		  break;

	 case MxEventButtonLeftPress:
	 case MxEventButtonLeftPressChild:
		  activate(window);
		  handle_press(window, event->point.x, event->point.y);
		  break;

	 case MxEventButtonLeftRelease:
		  if (MxPointer() == object)
				MxPointerRelease();
		  break;

	 case MxEventPointerMove:

		  if (window->moving)
				MxMoverStart(object, MxFalse, event->point.x, event->point.y);
		  else if (window->resizeing)
				MxMoverStart(object, MxTrue, event->point.x, event->point.y);
		  return object;

	 case MxEventMoverMoved:
	 case MxEventMoverResized:
		  window->moving = MxFalse;
		  window->resizeing = MxFalse;
		  break;

	 case MxEventExit:
		  MxDestroy(object);
		  break;

	 case MxEventPreInit:
		  _window_geometry(window);
		  break;

	 case MxEventPostInit:
		  if (window->modal)
				modal_init(window);

		  if (window->centered) {
				MxJustifyCenterHorizontal(object);
				MxJustifyCenterVertical(object);
		  }
		  break;

	 case MxEventGeomChanged:
		  _window_geometry(window);
		  MxEventSendSimpleToChildren(&window->base.object, MxEventGeomParentChanged, 0);
		  break;

	 case MxEventGeomRequest:
		  _window_resize(window, &event->geom);
		  return 0;

	 case MxEventKeyChild:
		  activate(window);
		  break;

	 case MxEventZOrderInform:

		  /* If we are modal we must be on top */
		  if (window->modal) {
				if (MxIndex(object) != 0)
					 MxZOrderDraw(object, 0);
		  }
		  break;

	 case MxEventActiveGot:
		  MxEnqueueRefresh(object, MxFalse);
		  break;

	 case MxEventActiveLost:
		  active_refresh(window);
		  return object;

	 default:
		  break;
	 }
	 return 0;
}

void MxWindowConstruct(MxWindow * window, MxObject * parent, int x, int y, int w, int h, MxWindowArgs * userargs)
{
	 MxWindowArgs args;

	 assert(window);
	 MxUserArgsInit(args, userargs);

	 memset(window, 0, sizeof(MxWindow));
	 MxObjectConstruct(&window->base.object, parent, x, y, w, h, &args.object);
	 window->base.object.handler = MxWindowHandler;

	 /* Try to add the user client */
	 if ((args.client) && (!args.noclient)) {
		  if (MxInsert(args.client, &window->base.object, MxFalse))
				window->client = args.client;
	 }

	 /* No user client or did not work */
	 if ((!window->client) && (!args.noclient)) {

		  MxPanel *panel = MxPanelNew(&window->base.object, 0, 0, 0, 0, 0);

		  panel->base.object.handler = MxWindowClientPanelHandler;
		  window->client = &panel->base.object;
		  panel->base.object.KeyProp = MxTrue;
		  panel->PassGeometry = MxTrue;

#ifdef MX_WINDOW_NAMES
		  panel->base.object.name = "MxWindowClient";
#endif
	 }

	 window->base.object.Fastdraw = MxTrue;

	 if (args.caption) {
		  window->caption = args.caption;
		  window->ownscaption = args.ownscaption;
	 } else {
		  window->caption = "";
		  window->ownscaption = MxFalse;
	 }

	 window->unmovable = args.unmovable;
	 window->unresizeable = args.unresizeable;
	 window->uncloseable = args.uncloseable;
	 window->centered = args.centered;
	 window->base.object.KeyProp = MxTrue;

	 /* Add the user's menu to our window */
	 window->menu = args.menu;
	 if (window->menu)
		  MxInsert(&window->menu->base.object, &window->base.object, MxFalse);

	 window->border = args.border;

	 _window_geometry(window);

	 if ((args.modal) && (args.blocked)) {
		  window->modal = args.modal;
		  window->blocked = args.blocked;
	 }
#ifdef MX_WINDOW_NAMES
	 window->base.object.name = "MxWindow";
#endif
}

MxWindow *MxWindowNew(MxObject * parent, int x, int y, int w, int h, MxWindowArgs * args)
{
	 return (MxWindow *) MxNewObject(sizeof(MxWindow), (MxVoidFunc) MxWindowConstruct, parent, x, y, w, h, &args->object);
}
