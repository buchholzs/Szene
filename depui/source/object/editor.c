#include "depui/config.h"
#include "depui/types.h"
#include "depui/args/args.h"
#include "depui/object/defsize.h"
#include "depui/object/editor.h"
#include "depui/event/focus.h"
#include "depui/event/queue.h"
#include <stdio.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static MxFileselector *open_selector(MxEditor * editor, const char *caption)
{
	 /* Prepare a file selector to open a file */
	 MxFileselectorArgs fileargs;

	 MxArgsInit(&fileargs);
	 fileargs.file = editor->filename;
	 strcpy(editor->filename, "");
	 fileargs.window.caption = caption;

	 /* Open the file selector to save a file */
	 return MxFileselectorStart(&fileargs, &editor->base.object, &editor->base.object);
}

static void editor_save(MxEditor * editor)
{
	 /* Try to open the destination file */
	 FILE *file = fopen(editor->filename, MX_FILE_WRITE);

	 MX_TRACE("");

	 if (file) {

		  /* Copy the editable text to a buffer */
		  const int len = MxEditareaLength(&editor->scrledit.editarea);
		  char *buffer = (char *) MxMalloc(len + 1);

		  /* Copy the buffer to the file */
		  if (buffer) {
				MxEditareaCopy(&editor->scrledit.editarea, buffer);
				fwrite(buffer, len, 1, file);

				/* Cleanup the file */
				MxFree(buffer);
		  }
		  /* Close the file */
		  fclose(file);
	 }
	 /* We are done trying to save the file */
	 editor->filesave = 0;
}

static void editor_open(MxEditor * editor)
{
	 /* Try to open the destination file */
	 FILE *file = fopen(editor->filename, MX_FILE_READ);

	 MX_TRACE("");

	 if (file) {

		  long len;
		  char *buffer;

		  /* Find out how big the file is */
		  fseek(file, 0, SEEK_END);
		  len = ftell(file);
		  rewind(file);

		  /* Read in the file and set the caption */
		  buffer = (char *) MxMalloc(len + 1);
		  if (buffer) {

				/* Make sure it's terminated */
				long end = fread(buffer, 1, len, file);

				buffer[end] = 0;
				MxEditareaSet(&editor->scrledit.editarea, buffer, MxTrue, MxTrue);
				MxEnqueueRefresh(&editor->scrledit.base.object, MxTrue);
		  }
		  /* Close the file */
		  fclose(file);
	 }
	 /* We are done trying to open the file */
	 editor->fileopen = 0;
}

static void callback_new(MxObject * menu, void *data, unsigned int selected)
{
	 (void) data;

	 if (selected) {
		  MxObject *object = MxParent(menu);
		  MxEditor *edit = MxEditorNew(0, MxX(object) + 20, MxY(object) + 20, MxW(object), MxH(object), 0);

		  if (edit) {
				MxInsert(&edit->base.object, MxParent(object), MxTrue);
				MxActiveSet(&edit->base.object, 0);
				MxEnqueueRefresh(&edit->base.object, MxTrue);
		  }
	 }
}

static void callback_open(MxObject * menu, void *data, unsigned int selected)
{
	 (void) data;

	 if (selected) {
		  MxObject *object = MxParent(menu);
		  MxEditor *editor = (MxEditor *) object;

		  editor->fileopen = open_selector(editor, "Open");
	 }
}

static void callback_save(MxObject * menu, void *data, unsigned int selected)
{
	 (void) data;

	 if (selected) {
		  MxObject *object = MxParent(menu);
		  MxEditor *editor = (MxEditor *) object;

		  editor->filesave = open_selector(editor, "Save");
	 }
}

void *MxEditorHandler(MxObject * object, const MxEvent * const event)
{
	 MxEditor *editor = (MxEditor *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventOk:

		  /* Have we selected a file to save */
		  if (editor->filesave)
				editor_save(editor);

		  /* Have we selected a file to open */
		  else if (editor->fileopen)
				editor_open(editor);

		  break;

		  /* Act like a normal window */
	 default:
		  return MxWindowHandler(object, event);
	 }
	 return 0;
}

MxMenuDef MxEditorFilemenu[] = {
	 {"New", callback_new, 0, 0, 0, 0, 0, 0}
	 ,
	 {"Open", callback_open, 0, 0, 0, 0, 0, 0}
	 ,
	 {"Save", callback_save, 0, 0, 0, 0, 0, 0}
	 ,
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

MxMenuDef MxEditorTopmenu[] = {
	 {"File ", 0, MxEditorFilemenu, 0, 0, 0, 0, 0}
	 ,
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

void MxEditorConstruct(MxEditor * editor, MxObject * parent, int x, int y, int w, int h, MxEditorArgs * userargs)
{
	 MxEditorArgs args;

	 assert(editor);
	 MxUserArgsInit(args, userargs);

	 /* Start with an empty object */
	 memset(editor, 0, sizeof(MxEditor));

	 /* Make the scrollable editarea area as window client */
	 MxScrollEditareaConstruct(&editor->scrledit, 0, 0, 0, 10, 10, &args.scrledit);

	 args.win.client = &editor->scrledit.base.object;

	 /* If the user does not say, use the basic menu */
	 if (!args.menu.listarea.def) {
		  args.menu.listarea.def = MxEditorTopmenu;
		  args.menu.listarea.ownsdef = MxFalse;
	 }

	 /* Construct the menu */
	 MxMenuConstruct(&editor->menu, 0, 0, 0, MxDefault, MxDefault, &args.menu);
	 args.win.menu = &editor->menu;

	 /* Construct the internal object */
	 if (!args.win.caption)
		  args.win.caption = "MxEditor";

	 MxWindowConstruct(&editor->base.win, parent, x, y, w, h, &args.win);
	 editor->base.object.handler = MxEditorHandler;

#ifdef MX_WINDOW_NAMES
	 editor->base.object.name = "MxEditor";
#endif
}

MxEditor *MxEditorNew(MxObject * parent, int x, int y, int w, int h, MxEditorArgs * args)
{
	 return (MxEditor *) MxNewObject(sizeof(MxEditor), (MxVoidFunc) MxEditorConstruct, parent, x, y, w, h, &args->object);
}
