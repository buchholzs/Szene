#include "depui/depui.h"

static MxDesktop desktop;

static MxListDef thelist[] = {
	 {"Listelem0", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem1", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem2", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem3", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem4", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem5", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem6", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem7", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem8", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem9", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
};

int main(int argc, char *argv[])
{
	 MxListArgs listargs;

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

	 /* Make some list object with multiple coloums */
	 MxArgsInit(&listargs);
	 listargs.listarea.def = thelist;

	 MxListNew(&desktop.base.object, 30, 30, 100, 100, &listargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
