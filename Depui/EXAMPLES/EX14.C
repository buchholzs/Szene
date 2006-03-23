#include "depui/depui.h"

static MxDesktop desktop;

int main(int argc, char *argv[])
{
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

	 /* Make a nice exit button */
	 MxExitButtonNew(&desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Prepare some window arguments */
	 MxArgsInit(&windowargs);
	 windowargs.caption = "DEPUI";

	 /* Add our window to the desktop */
	 MxWindowNew(&desktop.base.object, 50, 10, 110, 110, &windowargs);

	 /* Reserve a part of the screen for direct access */
	 MxDirectAccessNew(&desktop.base.object, 70, 70, 50, 50, 0);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {

		  /* Draw a pixel on the screen.  We don't need clipping because we
		     will keep everything inside the MxDirectAccess object */
		  MxScreenPixelFast(0, 70 + rand() % 51, 70 + rand() % 51, rand());
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
