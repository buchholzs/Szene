#include "depui/depui.h"

static MxButton button;
static MxWindow ourwindow;
static MxDesktop desktop;

static void desktop_exit(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 if (selected)
		  MxEventSendSimple(&desktop.base.object, MxEventExit);
}

/* An alert to make sure we want to exit */
static MxAlertArgs alertargs = { "Exit request",
	 "Are you sure you want to exit?\n\nPress a button\n\nAs many lines\nas you want",
	 {"Cancel", 0, 0},
	 {"Exit", desktop_exit, 0},
	 {0, 0, 0}
};

static void alert_start(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;

	 if (selected)
		  MxAlertStart(&alertargs, &ourwindow.base.object);
}

int main(int argc, char *argv[])
{
	 MxButtonArgs buttonargs;
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
	 MxWindowConstruct(&ourwindow, &desktop.base.object, 50, 10, 130, 130, &windowargs);

	 /* Make a nice exit button in the window */
	 MxArgsInit(&buttonargs);
	 buttonargs.stext.caption = "Exit";

	 MxPushButtonConstruct(&button, ourwindow.client, 5, 5, MxDefault, MxDefault, &buttonargs);
	 button.callback = alert_start;

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
