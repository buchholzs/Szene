#include "depui/config.h"
#include "depui/macros.h"
#include "depui/args/args.h"
#include "depui/object/defsize.h"
#include "depui/desktop/driver.h"
#include "depui/draw/draw.h"
#include "depui/event/queue.h"
#include "depui/graphics/frame.h"
#include "depui/object/cursor.h"
#include "depui/geometry/geometry.h"
#include <time.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

//#define ALWAYS_ON

static void draw_cursor(MxCursor * cursor, int x1, int y1, int x2, int y2)
{
	 if (cursor->on) {
		  MxScreenHLine(0, x1, y1, x2, MxColorFore);
		  MxScreenVLine(0, x1, y1 + 1, y2 - 1, MxColorFocus);
		  MxScreenVLine(0, x1 + 1, y1 + 1, y2 - 1, MxColorFore);
		  MxScreenVLine(0, x2, y1 + 1, y2 - 1, MxColorFocus);
		  MxScreenHLine(0, x1, y2, x2, MxColorFore);
	 }
}

static void start_blink(MxCursor * cursor)
{
	 MxEvent blink;

	 if (cursor->waiting)
		  return;

	 blink.type = MxEventCursorBlink;
	 cursor->waiting = MxTrue;

	 MxEnqueue(&cursor->base.object, &blink, MxCursorBlinkTime);
}

void *MxCursorHandler(MxObject * object, const MxEvent * const event)
{
	 MxCursor *cursor = (MxCursor *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw_cursor(cursor, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

	 case MxEventCursorBlink:
		  cursor->waiting = MxFalse;

		  /* Ignore blink event if we shouldn't be blinking */
		  if (!cursor->blinking)
				break;

		  /* On the first blink, keep the cursor on extra long */
		  if (cursor->firstblink) {
				cursor->firstblink = MxFalse;
				start_blink(cursor);
				break;
		  }

		  /* Invert the cursor */
#ifndef ALWAYS_ON
		  cursor->on = cursor->on ? MxFalse : MxTrue;
		  MxEnqueueRefresh(object, MxFalse);
#endif
		  start_blink(cursor);
		  break;

	 case MxEventGeomRequest:
		  MxScrollRequest(object, event->geom.data);
		  break;

	 default:
		  break;
	 }
	 return 0;
}

void MxCursorConstruct(MxCursor * cursor, MxObject * parent, int x, int y, int w, int h, MxCursorArgs * userargs)
{
	 int defh;

	 MxCursorArgs args;

	 assert(cursor);

	 MxUserArgsInit(args, userargs);

	 defh = MxFontHeight(MxFontDefault) + 1;
	 MxDefaultSize(&w, &h, MxCursorWidth, defh);

	 memset(cursor, 0, sizeof(MxCursor));
	 MxObjectConstruct(&cursor->base.object, parent, x, y, w, h, &args.args);
	 cursor->base.object.handler = MxCursorHandler;

	 cursor->base.object.Transparent = MxTrue;

#ifdef MX_WINDOW_NAMES
	 cursor->base.object.name = "MxCursor";
#endif
}

MxCursor *MxCursorNew(MxObject * parent, int x, int y, int w, int h, MxCursorArgs * args)
{
	 return (MxCursor *) MxNewObject(sizeof(MxCursor), (MxVoidFunc) MxCursorConstruct, parent, x, y, w, h, &args->args);
}

void MxCursorBlink(MxCursor * cursor, int blink)
{
	 /* Don't do anything if it's off and we ask for an off */
	 if ((!blink) && (!cursor->blinking))
		  return;

	 /* Start the cursor blinking */
	 if (blink) {
		  cursor->blinking = MxTrue;
		  cursor->firstblink = MxTrue;
		  cursor->on = MxTrue;

		  start_blink(cursor);
		  MxEnqueueRefresh(&cursor->base.object, MxFalse);

		  /* Stop the cursor blinking */
	 } else {
		  cursor->blinking = MxFalse;
		  cursor->on = MxFalse;

		  MxEnqueueRefresh(&cursor->base.object, MxFalse);
	 }
}

void MxMoveCursor(MxCursor * cursor, int x, int y)
{
	 MxEnqueueRefresh(&cursor->base.object, MxFalse);
	 MxGeomRequest(&cursor->base.object, x, y, 0, 0, (MxGeomFlags) (MxGeomX | MxGeomY));
	 MxEnqueueRefresh(&cursor->base.object, MxFalse);
}
