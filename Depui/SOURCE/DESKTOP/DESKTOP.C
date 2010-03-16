#include "depui/config.h"
#include "depui/args/args.h"
#include "depui/desktop/desktop.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"
#include "depui/event/focus.h"
#include "depui/graphics/frame.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void draw(MxDesktop * desktop, int x1, int y1, int x2, int y2)
{
	 const MxColor fill = (&desktop->base.object != mx_desk) ? MxColorBack : MxColorDesktop;

	 MxScreenRectFill(0, x1, y1, x2, y2, fill);
}

void *MxDesktopHandler(MxObject * object, const MxEvent * const event)
{
	 MxDesktop *desktop = (MxDesktop *) object;

	 MX_TRACE(event_name[event->type]);

	 switch (event->type) {

	 case MxEventExpose:
		  draw(desktop, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

	 case MxEventDestroy:
		  if (object == Mx.exiting)
				Mx.exiting = 0;
		  break;

	 case MxEventExit:
		  Mx.exiting = object;

		  /* If we are a sub-window, ask the window containing us to be killed */
		  if (object != mx_desk)
				MxEventSend(MxParent(object), event);

		  break;

	 case MxEventButtonLeftPress:
		  if (object == mx_desk) {
				MxPopupClean();
				MxFocusSet(0);
				MxActiveSet(object, 0);
		  }
		  break;

	 default:
		  break;
	 }
	 return 0;
}

#if defined(MX_DEBUG_STREAM) || defined (MEMTRACK)
#include <stdlib.h>
FILE *mx_stream = 0;

static void cleanup(void)
{
	 if (mx_stream)
		  fclose(mx_stream);
	 mx_stream = 0;
}

#endif

/* Make sure the desktop gets cleanup if the user forgets */
static void cleanup_desktop(void)
{
	 if (mx_desk)
		  MxDestroy(mx_desk);
	 mx_desk = 0;
}

void MxDesktopConstruct(MxDesktop * desktop, int x, int y, int w, int h, MxDesktopArgs * userargs)
{
	 MxDesktopArgs args;

	 MxUserArgsInit(args, userargs);

	 assert(desktop);
	 memset(desktop, 0, sizeof(MxDesktop));

	 /* If we are logging events, make sure that we have a stream to send them 
	    to */
#ifdef MX_DEBUG_STREAM
	 if (!mx_stream) {
		  mx_stream = fopen("event.dat", "w");
		  atexit(cleanup);
	 }
#endif

	 /* Initialize the desktop for the first time */
	 if (!mx_desk) {
		  unsigned int ret = MxTrue;

#ifdef MX_DEBUG_MEM
		  _mx_stack_base = (void *) &desktop;
		  _mx_highest_stack = (void *) &desktop;
#endif
		  /* Start with initialized objects */
		  memset(&Mx, 0, sizeof(Mx));

		  Mx.desktop = desktop;

		  /* Initialize the driver */
		  mx_system = args.system;
		  mx_output = args.output;
		  mx_input = args.input;

		  /* Find the correct size of the desktop */
		  if ((args.desktop_w == MxDefault) || (args.desktop_w == 0))
				args.desktop_w = 640;
		  if ((args.desktop_h == MxDefault) || (args.desktop_h == 0))
				args.desktop_w = 480;
		  if ((args.desktop_c == MxDefault) || (args.desktop_c == 0))
				args.desktop_c = 8;

		  /* Initialize the output driver */
		  ret = mx_output->Init(mx_output, args.desktop_w, args.desktop_h, args.desktop_c, args.window.caption);
		  if (ret) {

				/* Initialize the desktop size, so the input platform can use the
				   size for mouse range initialization */
				desktop->base.object.position.x1 = 0;
				desktop->base.object.position.y1 = 0;
				desktop->base.object.position.x2 = MxScreenWidth(0) - 1;
				desktop->base.object.position.y2 = MxScreenHeight(0) - 1;

				/* Initialize the input driver */
				ret = mx_input->Init();
		  }

		  /* If initializations didn't go well, return before setting the
		     mx_desk */
		  if (!ret)
				return;

		  /* Make the root object */
		  MxObjectConstruct(&desktop->base.object, 0, 0, 0, MxScreenWidth(0), MxScreenHeight(0), &args.object);
		  desktop->base.object.handler = MxDesktopHandler;
		  desktop->base.object.KeyProp = MxTrue;
#ifdef MX_WINDOW_NAMES
		  desktop->base.object.name = "MxRootDesktop";
#endif
		  /* Some basic global setup stuff */
		  MxRegionConstruct(&mx_region);
		  MxEventQueueConstruct();
		  Mx.idle_count = 0;

		  /* Make sure we refresh the new object */
		  MxEnqueueRefreshRect(&desktop->base.object.position);

		  /* Indicate that the init went well */
		  mx_desk = &desktop->base.object;
		  Mx.desktop = desktop;

		  /* Confirm that it went well */
		  if ((mx_desk) && (desktop->base.object.constructed))
				desktop->ok = MxTrue;

		  /* Make sure we cleanup when done */
		  atexit(cleanup_desktop);

		  /* We already have a root, so make a subwindow of the root */
	 } else {
		  MxWindow *win;

		  /* Create the desktop */
		  MxObjectConstruct(&desktop->base.object, 0, 0, 0, w, h, &args.object);
		  desktop->base.object.handler = MxDesktopHandler;
		  desktop->base.object.KeyProp = MxTrue;
#ifdef MX_WINDOW_NAMES
		  desktop->base.object.name = "MxSubDesktop";
#endif
		  /* Put the desktop into a window */
		  args.window.client = &desktop->base.object;
		  win = MxWindowNew(mx_desk, x, y, w, h, &args.window);

		  /* Make sure we refresh the new object */
		  MxEnqueueRefresh(&win->base.object, MxTrue);

		  /* Confirm that it went well */
		  if ((win) && (desktop->base.object.constructed))
				desktop->ok = MxTrue;
	 }
}

static void _object_init(MxObject * const object, const MxEvent * const event)
{
	 /* Do the children first */
	 MxObject *child = MxFirstChild(object);

	 while (child) {
		  _object_init(child, event);
		  child = MxNext(child);
	 }

#ifdef MX_DEBUG_EVENT
	 fprintf(mx_stream, "%s->%s [%p]\n", event_name[event->type], object->name, object);
#endif

	 /* Actually call the classes handler */
	 object->handler(object, event);
	 object->init = MxTrue;
}

void mx_object_init(struct MxObject *const object)
{
	 MxEvent event;

	 assert(object);

	 event.type = MxEventPreInit;
	 _object_init(object, &event);

	 event.type = MxEventPostInit;
	 _object_init(object, &event);
}
