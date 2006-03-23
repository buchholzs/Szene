#include "depui/config.h"
#include "depui/macros.h"
#include "depui/args/args.h"
#include "depui/draw/draw.h"
#include "depui/event/queue.h"
#include "depui/event/focus.h"
#include "depui/object/edit.h"
#include "depui/object/defsize.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#define LEFTOFFSET 3

static void post_update_cursor(MxEditline * line, unsigned int newoff)
{
	 /* Find the new position of the cursor on the new line */
	 const int p = MxStatictextPixel(&line->base.stext, newoff);
	 int offset = p + line->base.stext.tx + LEFTOFFSET;

	 unsigned int update = MxFalse;
	 const int width = MxW(&line->base.object);
	 const int rgt = offset - width - LEFTOFFSET + 5 * MxCursorWidth + 1;
	 const int lft = offset - LEFTOFFSET;

	 /* Move the text to the left (cursor too far right) */
	 if (rgt > 0) {
		  offset -= rgt;
		  line->base.stext.tx -= rgt;
		  update = MxTrue;
	 }
	 /* Move the text to the right (cursor too far left) */
	 if (lft < 0) {
		  offset -= lft;
		  line->base.stext.tx -= lft;
		  update = MxTrue;
	 }

	 if (update)
		  MxEnqueueRefresh(&line->base.object, MxFalse);

	 /* Move the cursor to it's proper position */
	 line->offset = newoff;
	 MxMoveCursor(&line->cursor, offset, line->base.stext.ty + 1);
}

static void handle_delete(MxEditline * line)
{
	 MX_TRACE("");

	 /* Make sure there is a character to delete */
	 if (line->base.stext.caption[line->offset]) {

		  /* Actually delete the character */
		  MxTextlineDelete(&line->base.textline, 1, line->offset);

		  /* Move the cursor if necessary */
		  post_update_cursor(line, line->offset);
		  MxEnqueueRefresh(&line->base.object, MxFalse);
	 }
}

static void handle_backspace(MxEditline * line)
{
	 MX_TRACE("");

	 if (line->offset) {

		  /* Actually delete the character */
		  MxTextlineDelete(&line->base.textline, 1, line->offset - 1);

		  /* Move the cursor if necessary */
		  post_update_cursor(line, line->offset - 1);
		  MxEnqueueRefresh(&line->base.object, MxFalse);
	 }
}

static void handle_normal(MxEditline * line, unsigned int code)
{
	 char string[3] = " ";

	 /* Actually insert the character */
	 string[0] = code;
	 MxTextlineInsert(&line->base.textline, string, line->offset);

	 /* Move the cursor if necessary */
	 post_update_cursor(line, line->offset + 1);
	 MxEnqueueRefresh(&line->base.object, MxFalse);
}

static void handle_left(MxEditline * line)
{
	 MX_TRACE("");

	 /* Is it a correct line and are we not at the begin of the string */
	 if (line->offset)
		  post_update_cursor(line, line->offset - 1);
}

static void handle_right(MxEditline * line)
{
	 MX_TRACE("");

	 /* Is it a correct line and are we not at the end of the string */
	 if (line->base.stext.caption[line->offset])
		  post_update_cursor(line, line->offset + 1);
}

static void handle_home(MxEditline * line)
{
	 MX_TRACE("");

	 if (line->offset) {

		  /* Move the cursor to the start of the line */
		  post_update_cursor(line, 0);
	 }
}

static void handle_end(MxEditline * line)
{
	 const unsigned int len = strlen(line->base.stext.caption);

	 MX_TRACE("");

	 if (line->offset != len)
		  post_update_cursor(line, len);
}

static unsigned int handle_key(MxEditline * line, MxKey key, unsigned int code)
{
	 unsigned int used = MxTrue;

	 /* Handle special keys */
	 switch (key) {

	 case MxKeyDelete:
		  handle_delete(line);
		  break;

	 case MxKeyLeft:
		  handle_left(line);
		  break;

	 case MxKeyRight:
		  handle_right(line);
		  break;

	 case MxKeyHome:
		  handle_home(line);
		  break;

	 case MxKeyEnd:
		  handle_end(line);
		  break;

		  /* We did not find a use for the key */
	 default:
		  used = MxFalse;
		  break;
	 }

	 /* Handle normal keys */
	 if (!used) {

		  used = MxTrue;

		  /* Handle backspace seperately */
		  if (code == 0x08)
				handle_backspace(line);

		  /* Don't allow returns */
		  else if ((code == 0x0D) || (code == 0x0A))
				used = MxFalse;

		  /* Handle normal keys */
		  else
				handle_normal(line, code);
	 }

	 if (used)
		  MxCursorBlink(&line->cursor, MxTrue);

	 return used;
}

static void mx_draw_editline(MxEditline * line, int x1, int y1, int x2, int y2)
{
	 mx_draw_statictext(&line->base.stext, LEFTOFFSET, 2, x1, y1, x2, y2, MxColorObjectFore, MxColorObjectBack);
}

void *MxEditlineHandler(MxObject * object, const MxEvent * const event)
{
	 MxEditline *line = (MxEditline *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  mx_draw_editline(line, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

		  /* Take the focus when a child of ours is clicked */
	 case MxEventButtonLeftPress:{

				/* Try and get the focus */
				MxFocusSet(object);

				/* If we have the focus move the cursor to where the click was */
				if (MxFocus() == object) {

					 unsigned int pixel = event->point.x - line->base.object.position.x1 - line->base.stext.tx;

					 post_update_cursor(line, MxStatictextOffset(&line->base.stext, &pixel));
				}
				break;
		  }

		  /* Blink the cursor when when we have the focus */
	 case MxEventFocusGot:
		  MxCursorBlink(&line->cursor, MxTrue);
		  return object;

	 case MxEventFocusLost:
		  MxCursorBlink(&line->cursor, MxFalse);
		  return object;

		  /* Don't let us be set to smaller than our cursor */
	 case MxEventGeomRequest:{

				/* Get the textline to handle the size first */
				void *ret = MxTextlineHandler(object, event);

				/* Don't let the width get too small */
				if (event->geom.data->flags & MxGeomW)
					 event->geom.data->w = MX_MAX(event->geom.data->w, MxCursorWidth);

				/* Don't let the height get too small */
				if (event->geom.data->flags & MxGeomH) {
					 const int cursorh = MxFontHeight(MxFontDefault) + 1;

					 event->geom.data->h = MX_MAX(event->geom.data->h, cursorh);
				}
				return ret;
		  }
	 case MxEventGeomChanged:{
				void *ret = MxTextlineHandler(object, event);

				MxRegionInvalidate(&line->cursor.base.object);
				MxZOrder(&line->cursor.base.object, 0);
				return ret;
		  }

	 case MxEventKey:

		  /* Try to use the key, if we use it, say so */
		  if (handle_key(line, event->key.key, event->key.code))
				return object;

		  /* We found no use for the key */
		  break;

	 default:
		  return MxTextlineHandler(object, event);
	 }
	 return 0;
}

void MxEditlineConstruct(MxEditline * line, MxObject * parent, int x, int y, int w, int h, MxEditlineArgs * userargs)
{
	 int defw, defh;

	 MxEditlineArgs args;

	 assert(line);
	 MxUserArgsInit(args, userargs);

	 /* Find the default size of the editable text area */
	 if (args.textline.stext.caption) {
		  const char *temp = mx_text_copy(args.textline.stext.caption, args.textline.stext.len);

		  defw = MxFontLength(MxFontDefault, args.textline.stext.caption) + 1;

		  MxFree((char *) temp);
	 } else
		  defw = 10;
	 defh = MxFontHeight(MxFontDefault) + 5;
	 MxDefaultSize(&w, &h, defw, defh);

	 /* Create the base object */
	 memset(line, 0, sizeof(MxEditline));

	 MxTextlineConstruct(&line->base.textline, parent, x, y, w, h, &args.textline);
	 line->base.object.handler = MxEditlineHandler;

	 /* By default we want a small border */
	 line->base.stext.border = args.textline.stext.border - 1;

	 /* We want a certian justification */
	 line->base.stext.just = MxJustifyVCenter;

	 /* Create the cursor */
	 MxCursorConstruct(&line->cursor, &line->base.object, 1, 1, MxDefault, MxDefault, &args.cursor);

#ifdef MX_WINDOW_NAMES
	 line->base.object.name = "MxEditline";
#endif
}

MxEditline *MxEditlineNew(MxObject * parent, int x, int y, int w, int h, MxEditlineArgs * args)
{
	 return (MxEditline *) MxNewObject(sizeof(MxEditline), (MxVoidFunc) MxEditlineConstruct, parent, x, y, w, h, &args->object);
}

void MxEditlineSet(MxEditline * line, const char *caption)
{
	 const int len = strlen(caption);
	 char *copy = (char *) MxMalloc(len + 1);

	 assert(line);
	 assert(copy);

	 if (copy) {
		  strcpy(copy, caption);
		  MxStatictextSet(&line->base.stext, copy, MxTrue);
		  post_update_cursor(line, line->offset);
	 }
}

const char *MxEditlineCaption(MxEditline * line)
{
	 assert(line);

	 return line->base.stext.caption;
}

void MxEditlineCursorTo(MxEditline * line, unsigned int cindex)
{
	 const unsigned int len = strlen(line->base.stext.caption);

	 if (cindex > len)
		  cindex = len;

	 assert(line);

	 post_update_cursor(line, cindex);
}
