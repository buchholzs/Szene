#include "depui/depui.h"

static MxDesktop desktop;

static MxListDef thelist[] = {
	 {"List\telem0", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem1", 0, 0, 0, 0, 0, 0, 0},
	 {"", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem2", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem3", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem4", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem5", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem6", 0, 0, 0, MxTrue, 0, 0, 0},
	 {"Listelem7", 0, 0, MxTrue, MxTrue, 0, 0, 0},
	 {"Listelem8", 0, 0, MxTrue, 0, 0, 0, 0},
	 {"Listelem9", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
};

/* Simple tabstop function */
static int tabstop(const MxObject * object, const int tab)
{
	 (void) object;
	 (void) tab;

	 return 50;
}

static MxListDef thecoloumlist[] = {
	 {"List\telem0\tzero", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem1\tone", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem2\ttwo", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem3\tthree", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem4\tfour", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem5\tfive", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem6\tsix", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem7\tseven", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem8\teight", 0, 0, 0, 0, 0, 0, 0},
	 {"List\telem9\tnine", 0, 0, 0, 0, 0, 0, 0},
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

	 MxArgsInit(&desktopargs);

	 (void) argc;
	 (void) argv;

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

	 /* Make some scrollable list object */
	 MxArgsInit(&listargs);
	 listargs.listarea.def = thelist;

	 MxListNew(&desktop.base.object, 10, 30, 100, 100, &listargs);

	 /* Make some scrollable multi coloum list object */
	 listargs.listarea.def = thecoloumlist;
	 listargs.listarea.tabstop = tabstop;

	 MxListNew(&desktop.base.object, 120, 30, 160, 100, &listargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
