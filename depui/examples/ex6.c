#include "depui/depui.h"

static MxDesktop desktop;

static void callback_new(MxObject * object, void *data, unsigned int selected)
{
	 MxAlertArgs alertargs = { "Callback called", "Menu->File->new",
		  {"Ok", 0, MxTrue},
		  {0, 0, 0},
		  {0, 0, 0}
	 };

	 (void) object;
	 (void) data;
	 (void) selected;

	 MxAlertStart(&alertargs, 0);
}

static void callback_open(MxObject * object, void *data, unsigned int selected)
{
	 MxAlertArgs alertargs = { "Callback called", "Menu->File->open",
		  {"Ok", 0, MxTrue},
		  {0, 0, 0},
		  {0, 0, 0}
	 };

	 (void) object;
	 (void) data;
	 (void) selected;

	 MxAlertStart(&alertargs, 0);
}

static void callback_exit(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 if (selected)
		  MxEventSendSimple(&desktop.base.object, MxEventExit);
}

static void callback_help(MxObject * object, void *data, unsigned int selected)
{
	 MxAlertArgs alertargs = { "Callback called", "Menu->Help->Help",
		  {"Ok", 0, MxTrue},
		  {0, 0, 0},
		  {0, 0, 0}
	 };

	 (void) object;
	 (void) data;
	 (void) selected;

	 MxAlertStart(&alertargs, 0);
}

static MxMenuDef helpmenu[] = {
	 {"Help ", callback_help, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxMenuDef filemenu[] = {
	 {"New", callback_new, 0, 0, 0, 0, 0, 0},
	 {"Open", callback_open, 0, 0, 0, 0, 0, 0},
	 {"Exit", callback_exit, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxMenuDef topmenu[] = {
	 {"File ", 0, filemenu, 0, 0, 0, 0, 0},
	 {"Help ", 0, helpmenu, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
	 MxWindow *ourwindow;
	 MxWindowArgs windowargs;

	 MxMenu *menu;
	 MxMenuArgs menuargs;

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
	 if (!&desktop.base.object)
		  return 1;

	 /* Create a menu */
	 MxArgsInit(&menuargs);
	 menuargs.listarea.def = topmenu;
	 menu = MxMenuNew(0, 0, 0, 0, 0, &menuargs);

	 /* Create a window and add it to the desktop */
	 MxArgsInit(&windowargs);
	 windowargs.caption = "DEPUI";
	 windowargs.uncloseable = MxTrue;
	 windowargs.menu = menu;
	 ourwindow = MxWindowNew(&desktop.base.object, 10, 10, 150, 150, &windowargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
