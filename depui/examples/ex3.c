#include "depui/depui.h"

static MxDesktop desktop;

static void desktop_exit(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 if (selected)
		  MxEventSendSimple(&desktop.base.object, MxEventExit);
}

int main(int argc, char *argv[])
{
	 MxButtonArgs btnargs;

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
	 windowargs.uncloseable = MxTrue;

	 /* Add our window to the desktop */
	 ourwindow = MxWindowNew(&desktop.base.object, 10, 10, 100, 100, &windowargs);

	 /* Add a button to the window client area */
	 MxArgsInit(&btnargs);
	 btnargs.callback = desktop_exit;
	 MxExitButtonNew(ourwindow->client, 10, 10, MxDefault, MxDefault, &btnargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
