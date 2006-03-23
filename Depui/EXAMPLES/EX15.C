#include "depui/depui.h"

static MxDesktop desktop;

int main(int argc, char *argv[])
{
	 MxButtonArgs buttonargs;

	 MxRadioGroup *group;
	 MxRadioGroupArgs groupargs;

	 MxWindow ourwindow;
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
	 MxWindowConstruct(&ourwindow, &desktop.base.object, 50, 10, 130, 180, &windowargs);

	 /* Add a radio group and some radio buttons */
	 MxArgsInit(&groupargs);
	 groupargs.caption = "group";
	 group = MxRadioGroupNew(ourwindow.client, 5, 5, 85, 75, &groupargs);

	 MxArgsInit(&buttonargs);
	 buttonargs.stext.caption = "Radio 1";
	 MxRadioButtonNew(&group->base.object, 5, 15, MxDefault, MxDefault, &buttonargs);

	 buttonargs.stext.caption = "Radio 2";
	 MxRadioButtonNew(&group->base.object, 5, 35, MxDefault, MxDefault, &buttonargs);

	 buttonargs.stext.caption = "Radio 3";
	 MxRadioButtonNew(&group->base.object, 5, 55, MxDefault, MxDefault, &buttonargs);

	 /* Add some check buttons */
	 buttonargs.stext.caption = "Check 1";
	 MxCheckboxNew(ourwindow.client, 5, 90, MxDefault, MxDefault, &buttonargs);

	 buttonargs.stext.caption = "Check 2";
	 MxCheckboxNew(ourwindow.client, 5, 105, MxDefault, MxDefault, &buttonargs);

	 buttonargs.stext.caption = "Check 3";
	 MxCheckboxNew(ourwindow.client, 5, 120, MxDefault, MxDefault, &buttonargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
