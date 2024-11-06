#include "depui/depui.h"

static MxDesktop desktop;

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

	 desktopargs.desktop_w = 640;
	 desktopargs.desktop_h = 480;
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

	 /* Add a button to the dialog */
	 MxExitButtonNew(&desktop.base.object, 100, 100, MxDefault, MxDefault, &buttonargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
