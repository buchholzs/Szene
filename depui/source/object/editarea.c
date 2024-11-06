#include "depui/config.h"
#include "depui/macros.h"
#include "depui/args/args.h"
#include "depui/desktop/driver.h"
#include "depui/draw/draw.h"
#include "depui/event/queue.h"
#include "depui/event/focus.h"
#include "depui/geometry/geometry.h"
#include "depui/object/edit.h"
#include "depui/object/defsize.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void post_update_cursor(MxEditarea * editarea, const unsigned int set)
{
	 int pixx = MxX(&editarea->cursor.base.object);
	 int pixy = MxY(&editarea->cursor.base.object);
	 const MxTextareaParse *parse = MxTextareaParseIndex(&editarea->base.textarea, editarea->offset);

	 MxTextareaPixel(&editarea->base.textarea, parse, editarea->offset, &pixx, &pixy);

	 MxMoveCursor(&editarea->cursor, pixx, pixy);

	 if (set)
		  editarea->xpixel = pixx;
}

static void handle_delete(MxEditarea * editarea)
{
	 /* Make sure there is a character to delete */
	 if (editarea->base.textarea.caption[editarea->offset]) {

		  /* Actually delete the character */
		  MxTextareaDelete(&editarea->base.textarea, 1, editarea->offset);
		  post_update_cursor(editarea, MxTrue);
	 }
}

static void handle_backspace(MxEditarea * editarea)
{
	 MX_TRACE("");

	 if (editarea->offset) {

		  /* Actually delete the character */
		  --editarea->offset;
		  MxTextareaDelete(&editarea->base.textarea, 1, editarea->offset);
		  post_update_cursor(editarea, MxTrue);
	 }
}

static void handle_normal(MxEditarea * editarea, unsigned int code)
{
	 char string[3] = " ";

	 /* Actually insert the character */
	 string[0] = code;
	 MxTextareaInsert(&editarea->base.textarea, string, editarea->offset);
	 ++editarea->offset;
	 post_update_cursor(editarea, MxTrue);
}

static void handle_left(MxEditarea * editarea)
{
	 const MxTextareaParse *parse = MxTextareaParseIndex(&editarea->base.textarea, editarea->offset);

	 MX_TRACE("");

	 /* Is it a correct line and are we not at the begin of the string */
	 if (editarea->offset > parse->offset) {

		  --editarea->offset;
		  post_update_cursor(editarea, MxTrue);
	 }
}

static void handle_right(MxEditarea * editarea)
{
	 const MxTextareaParse *parse = MxTextareaParseIndex(&editarea->base.textarea, editarea->offset);

	 MX_TRACE("");

	 /* Is it a correct line and are we not at the end of the string */
	 if ((editarea->base.textarea.caption[editarea->offset])
		  && (editarea->offset < parse->offset + parse->len + parse->skip - 1)) {

		  ++editarea->offset;
		  post_update_cursor(editarea, MxTrue);
	 }
}

static void handle_up(MxEditarea * editarea)
{
	 const MxTextareaParse *parse = MxTextareaParseIndex(&editarea->base.textarea, editarea->offset);

	 MX_TRACE("");

	 /* Make sure we are not the first line */
	 if (parse->linenum) {

		  int pixel = editarea->xpixel;

		  /* Goto the previous line */
		  --parse;

		  /* Set the new string offset */
		  editarea->offset = MxTextareaOffset(&editarea->base.textarea, parse, &pixel);
		  post_update_cursor(editarea, MxFalse);
	 }
}

static void handle_down(MxEditarea * editarea)
{
	 const MxTextareaParse *parse = MxTextareaParseIndex(&editarea->base.textarea, editarea->offset);

	 MX_TRACE("");

	 /* Make sure we are not the last line */
	 if (parse->linenum + 1 < editarea->base.textarea.parsenum) {

		  int pixel = editarea->xpixel;

		  /* Goto the next line */
		  ++parse;

		  /* Set the new string offset */
		  editarea->offset = MxTextareaOffset(&editarea->base.textarea, parse, &pixel);
		  post_update_cursor(editarea, MxFalse);
	 }
}

static void handle_home(MxEditarea * editarea)
{
	 const MxTextareaParse *parse = MxTextareaParseIndex(&editarea->base.textarea, editarea->offset);

	 MX_TRACE("");

	 if (editarea->offset != parse->offset) {

		  /* Goto the begin if the line */
		  editarea->offset = parse->offset;
		  post_update_cursor(editarea, MxTrue);
	 }
}

static void handle_end(MxEditarea * editarea)
{
	 const MxTextareaParse *parse = MxTextareaParseIndex(&editarea->base.textarea, editarea->offset);

	 MX_TRACE("");

	 if (editarea->offset != parse->offset + parse->len) {

		  /* Go to the end of the line */
		  editarea->offset = parse->offset + parse->len;
		  post_update_cursor(editarea, MxTrue);
	 }
}

static unsigned int handle_key(MxEditarea * editarea, MxKey key, unsigned int code)
{
	 unsigned int used = MxTrue;

	 /* Handle special keys */
	 switch (key) {

	 case MxKeyDelete:
		  handle_delete(editarea);
		  break;

	 case MxKeyLeft:
		  handle_left(editarea);
		  break;

	 case MxKeyRight:
		  handle_right(editarea);
		  break;

	 case MxKeyUp:
		  handle_up(editarea);
		  break;

	 case MxKeyDown:
		  handle_down(editarea);
		  break;

	 case MxKeyHome:
		  handle_home(editarea);
		  break;

	 case MxKeyEnd:
		  handle_end(editarea);
		  break;

		  /* We did not find a use for the key */
	 default:
		  used = MxFalse;
		  break;
	 }

	 /* Handle normal keys */
	 if (!used) {

		  if (code == 0x08)
				handle_backspace(editarea);
		  else
				handle_normal(editarea, code);

		  used = MxTrue;
	 }

	 if (used) {
		  MxCursorBlink(&editarea->cursor, MxTrue);
		  MxEnqueueRefresh(&editarea->base.object, MxFalse);
	 }

	 return used;
}

void *MxEditareaHandler(MxObject * object, const MxEvent * const event)
{
	 MxEditarea *editarea = (MxEditarea *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 /* Make sure the cursor is on top of all the textlines */
	 MxZOrder(&editarea->cursor.base.object, 0);

	 switch (event->type) {

		  /* Take the focus when a child of ours is clicked */
	 case MxEventButtonLeftPress:{

				/* Try and get the focus */
				MxFocusSet(object);

				/* If we have the focus move the cursor to where the click was */
				if (MxFocus() == object) {

					 const MxTextareaParse *parse = MxTextareaLine(&editarea->base.textarea, event->point.y - object->position.y1);
					 int pixel = event->point.x - object->position.x1;

					 editarea->offset = MxTextareaOffset(&editarea->base.textarea, parse, &pixel);
					 post_update_cursor(editarea, MxTrue);
				}
				break;
		  }

		  /* Blink the cursor when when we have the focus */
	 case MxEventFocusGot:
		  MxCursorBlink(&editarea->cursor, MxTrue);
		  return object;

	 case MxEventFocusLost:
		  MxCursorBlink(&editarea->cursor, MxFalse);
		  return object;

	 case MxEventGeomRequest:{

				/* Get the textarea to handle the size first */
				void *ret = MxTextareaHandler(object, event);

				/* Don't let us be set to smaller than our cursor */
				if (event->geom.data->flags & MxGeomW)
					 event->geom.data->w = MX_MAX(event->geom.data->w, MxW(&editarea->cursor.base.object));

				if (event->geom.data->flags & MxGeomH)
					 event->geom.data->h = MX_MAX(event->geom.data->h, MxH(&editarea->cursor.base.object));

				return ret;
		  }
	 case MxEventKey:
		  /* Try to use the key, if we use it, say so */
		  if (handle_key(editarea, event->key.key, event->key.code))
				return object;

		  /* We found no use for the key */
		  break;

	 case MxEventTextareaPostparse:
		  post_update_cursor(editarea, MxTrue);
		  break;

	 default:
		  return MxTextareaHandler(object, event);
	 }
	 return 0;
}

void MxEditareaConstruct(MxEditarea * editarea, MxObject * parent, int x, int y, int w, int h, MxEditareaArgs * userargs)
{
	 MxEditareaArgs args;

	 const int cursorh = MxFontHeight(MxFontDefault) + 1;

	 assert(editarea);
	 MxUserArgsInit(args, userargs);

	 /* Create the base object */
	 memset(editarea, 0, sizeof(MxEditarea));
	 MxTextareaConstruct(&editarea->base.textarea, parent, x, y, w, h, &args.textarea);
	 editarea->base.object.handler = MxEditareaHandler;

	 /* Create the cursor */
	 MxCursorConstruct(&editarea->cursor, &editarea->base.object, 0, 0, MxCursorWidth, cursorh, &args.cursor);

#ifdef MX_WINDOW_NAMES
	 editarea->base.object.name = "MxEditarea";
#endif
}

MxEditarea *MxEditareaNew(MxObject * parent, int x, int y, int w, int h, MxEditareaArgs * args)
{
	 return (MxEditarea *) MxNewObject(sizeof(MxEditarea), (MxVoidFunc) MxEditareaConstruct, parent, x, y, w, h, &args->object);
}

const char *MxEditareaCaption(MxEditarea * editarea)
{
	 return editarea->base.textarea.caption;
}

void MxEditareaSet(MxEditarea * editarea, const char *text, unsigned int owns, unsigned int refresh)
{
	 MxTextareaSet(&editarea->base.textarea, text, owns, refresh);
	 editarea->offset = 0;
	 post_update_cursor(editarea, MxTrue);
}
