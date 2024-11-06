#include "depui/depui.h"

static MxDesktop desktop;

void *OurWindowHandler(MxObject * object, const MxEvent * const event)
{
	 switch (event->type) {

		  /* Close the desktop when we exit */
	 case MxEventExit:
		  MxEventSend(&desktop.base.object, event);
		  break;

		  /* Otherwise act like a normal window */
	 default:
		  return MxWindowHandler(object, event);
	 }
	 return 0;
}

int main(int argc, char *argv[])
{
	 MxWindow *ourwindow;
	 MxWindowArgs windowargs;

	 /* Create some drivers specific to the system */
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

	 /* Prepare some window arguments */
	 MxArgsInit(&windowargs);
	 windowargs.caption = "DEPUI";

	 /* Add our window to the desktop */
	 ourwindow = MxWindowNew(&desktop.base.object, 10, 10, 100, 100, &windowargs);
	 ourwindow->base.object.handler = OurWindowHandler;

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
