#include "depui/depui.h"

/* A reserved identifier for dragdrop used in this prog */
static MxDragdropType my_dragdrop_type = MxDragdropUser;

/* Cleanup the data from a successful or unsuccessfull drag/dropg */
static void cleanup_dragdrop(void *data)
{
	 (void) data;
}

/* A special list element handler that handles drag/drop */
static void *my_listarea_handler(MxObject * object, const MxEvent * const event)
{
	 MxListarea *list = (MxListarea *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

		  /* An element is being dragged, so start the drag drop */
	 case MxEventListareaDrag:
		  MxDragdropStart(object, list->clicked, my_dragdrop_type, cleanup_dragdrop, list->clicked->caption, MxFalse);
		  break;

		  /* Does someone want to drop something on us */
	 case MxEventDropTarget:

		  /* Make sure it is the right kind of drag/drop type i.e. the kind
		     that we reserved for these kind of events */
		  if (event->dragdrop.dragdrop->type != my_dragdrop_type)
				return 0;

		  /* We want the drop */
		  return object;

	 case MxEventDrop:

		  /* Make sure its the drop that we expected */
		  if (event->dragdrop.dragdrop->type != my_dragdrop_type) {
				return 0;

		  } else {
				/* Get a copy of the listdef we are talking about */
				MxListDef *def = (MxListDef *) event->dragdrop.dragdrop->data;
				const MxListDef temp = *def;

				MxListarea *source = (MxListarea *) event->dragdrop.dragdrop->source;

				MxListareaRemove(source, def);
				MxListareaAppend(list, &temp);
		  }
		  break;

	 default:
		  return MxListareaHandler(object, event);
	 }
	 return 0;
}

static MxListDef thelist1[] = {
	 {"1", 0, 0, 0, 0, 0, 0, 0},
	 {"2", 0, 0, 0, 0, 0, 0, 0},
	 {"3", 0, 0, 0, 0, 0, 0, 0},
	 {"4", 0, 0, 0, 0, 0, 0, 0},
	 {"5", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxListDef thelist2[] = {
	 {"6", 0, 0, 0, 0, 0, 0, 0},
	 {"7", 0, 0, 0, 0, 0, 0, 0},
	 {"8", 0, 0, 0, 0, 0, 0, 0},
	 {"9", 0, 0, 0, 0, 0, 0, 0},
	 {"10", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
	 MxList *list;
	 MxListArgs listargs;
	 MxStatictextArgs textargs;

	 /* Create some drivers specific to the system */
	 MxDesktop desktop;
	 MxDesktopArgs desktopargs;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 (void) argc;
	 (void) argv;

	 MxArgsInit(&desktopargs);

	 desktopargs.desktop_w = 320;
	 desktopargs.desktop_h = 200;
	 desktopargs.desktop_c = 8;
	 desktopargs.system = &system;
	 desktopargs.output = &output;
	 desktopargs.input = &input;
	 desktopargs.window.caption = "";

	 /* Initailize the library */
	 MxDesktopConstruct(&desktop, 0, 0, 0, 0, &desktopargs);
	 if (!desktop.ok)
		  return 1;

	 /* Make a nice exit button */
	 MxExitButtonNew(&desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make a nice message to tell the user what to do */
	 MxArgsInit(&textargs);
	 textargs.caption = "Drag/Drop between lists";
	 textargs.len = strlen(textargs.caption);
	 MxStatictextNew(&desktop.base.object, 30, 30, MxDefault, MxDefault, &textargs);

	 /* Make a list object */
	 MxArgsInit(&listargs);
	 listargs.listarea.def = thelist1;
	 list = MxListNew(&desktop.base.object, 30, 50, 50, 100, &listargs);
	 list->listarea.base.object.handler = my_listarea_handler;

	 /* Make a second list object */
	 listargs.listarea.def = thelist2;
	 list = MxListNew(&desktop.base.object, 100, 50, 50, 100, &listargs);
	 list->listarea.base.object.handler = my_listarea_handler;

	 /* Reserve a drag/drop type for the pbjects we will be passing */
	 MxDragdropReserve(&my_dragdrop_type);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
