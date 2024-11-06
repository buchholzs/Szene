#include "depui/depui.h"

int program1(void)
{
	 MxStatictextArgs stextargs;

	 MxDesktop desktop;
	 MxDesktopArgs desktopargs;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 MxArgsInit(&desktopargs);

	 desktopargs.desktop_w = 320;
	 desktopargs.desktop_h = 200;
	 desktopargs.desktop_c = 8;
	 desktopargs.system = &system;
	 desktopargs.output = &output;
	 desktopargs.input = &input;
	 desktopargs.window.caption = "program1";

	 /* Initailize the library */
	 MxDesktopConstruct(&desktop, 10, 10, 150, 150, &desktopargs);
	 if (!desktop.ok)
		  return 1;

	 /* Make a nice exit button */
	 MxExitButtonNew(&desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make some nice static text */
	 MxArgsInit(&stextargs);
	 stextargs.caption = "This is program 1";
	 MxStatictextNew(&desktop.base.object, 5, 25, MxDefault, MxDefault, &stextargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}

int program2(void)
{
	 MxStatictextArgs stextargs;

	 MxDesktop desktop;
	 MxDesktopArgs desktopargs;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 MxArgsInit(&desktopargs);

	 desktopargs.desktop_w = 320;
	 desktopargs.desktop_h = 200;
	 desktopargs.desktop_c = 8;
	 desktopargs.system = &system;
	 desktopargs.output = &output;
	 desktopargs.input = &input;
	 desktopargs.window.caption = "program2";

	 /* Initailize the library */
	 MxDesktopConstruct(&desktop, 30, 30, 150, 150, &desktopargs);
	 if (!desktop.ok)
		  return 1;

	 /* Make a nice exit button */
	 MxExitButtonNew(&desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make some nice static text */
	 MxArgsInit(&stextargs);
	 stextargs.caption = "This is program 2";
	 MxStatictextNew(&desktop.base.object, 5, 25, MxDefault, MxDefault, &stextargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}

static void callback_program1(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 (void) selected;

	 if (selected)
		  program1();
}

static void callback_program2(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 (void) selected;

	 if (selected)
		  program2();
}

int program3(void)
{
	 MxButtonArgs buttonargs;

	 MxDesktop desktop;
	 MxDesktopArgs desktopargs;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 MxArgsInit(&desktopargs);

	 desktopargs.desktop_w = 320;
	 desktopargs.desktop_h = 200;
	 desktopargs.desktop_c = 8;
	 desktopargs.system = &system;
	 desktopargs.output = &output;
	 desktopargs.input = &input;
	 desktopargs.window.caption = "program3";

	 /* Initailize the library */
	 MxDesktopConstruct(&desktop, 10, 10, 150, 150, &desktopargs);
	 if (!desktop.ok)
		  return 1;

	 /* Make a nice exit button */
	 MxExitButtonNew(&desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make some buttons to run the two programs */
	 MxArgsInit(&buttonargs);
	 buttonargs.stext.caption = "Run program 1";
	 buttonargs.callback = callback_program1;
	 MxPushButtonNew(&desktop.base.object, 5, 25, MxDefault, MxDefault, &buttonargs);

	 buttonargs.stext.caption = "Run program 2";
	 buttonargs.callback = callback_program2;
	 MxPushButtonNew(&desktop.base.object, 5, 55, MxDefault, MxDefault, &buttonargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}

int main(int argc, char *argv[])
{
	 int ret;

	 (void) argc;
	 (void) argv;

	 /* Run program 1 by itself */
	 ret = program1();
	 if (ret)
		  return ret;

	 /* Run program 2 by itself */
	 ret = program2();
	 if (ret)
		  return ret;

	 /* Run program 1 and program 2 at the same time */
	 ret = program3();
	 return ret;
}
