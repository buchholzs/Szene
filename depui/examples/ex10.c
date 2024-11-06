#include "depui/depui.h"

static MxDesktop desktop;

int main(int argc, char *argv[])
{
	 MxButton button;

	 MxScrollTextareaArgs scrolltextareaargs;

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
	 MxExitButtonConstruct(&button, &desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make some scrollabel textarea object */
	 MxArgsInit(&scrolltextareaargs);
	 scrolltextareaargs.textarea.caption = "This is some text\nHere is a second line.\nHere is a third line\n\nThe avove line is empty";

	 MxScrollTextareaNew(&desktop.base.object, 30, 30, 150, 80, &scrolltextareaargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
