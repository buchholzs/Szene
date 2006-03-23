#include "depui/depui.h"

static MxDesktop desktop;

/* When the putton is pressed, exit the root window */
static void button_callback(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;

	 if (selected)
		  MxEventSendSimple(&desktop.base.object, MxEventExit);
}

int main(int argc, char *argv[])
{
	 MxButtonArgs buttonargs;

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

	 /* Prepare some button arguments for an exit button */
	 MxArgsInit(&buttonargs);
	 buttonargs.stext.caption = "Hello world";
	 buttonargs.callback = button_callback;

	 /* Add a button to the dialog */
	 MxPushButtonNew(&desktop.base.object, 100, 100, MxDefault, MxDefault, &buttonargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
