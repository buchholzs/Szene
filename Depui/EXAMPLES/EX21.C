#include <stdlib.h>
#include <stdio.h>
#include "depui/depui.h"

static MxDesktop desktop;

static void backswitch(struct MxObject *object, void *data, unsigned int selected)
{
	 static MxColor olddesktop;
	 static unsigned int switched = MxFalse;

	 (void) object;
	 (void) data;
	 (void) selected;

	 /* Change the background colors */
	 if (!switched) {
		  olddesktop = MxColorDesktop;
		  MxColorDesktop = MxColorBack;

		  /* Or else change them back */
	 } else
		  MxColorDesktop = olddesktop;

	 switched = !switched;
	 MxEnqueueRefresh(&desktop.base.object, MxFalse);
}

static void *DesktopHandler(MxObject * object, const MxEvent * const event)
{
	 /* Quit while we have no objects to control */
	 if (MxNumChild(object) == 0)
		  Mx.exiting = object;

	 /* Otherwise behave just as a regular desktop */
	 return MxDesktopHandler(object, event);
}

/* main function */
int main(int argc, char *argv[])
{
	 MxEditorArgs editorargs;
	 MxMenuDef *topmenu;
	 MxMenuDef *usermenu;
	 MxMenuDef user = { "User ", 0, 0, 0, 0, 0, 0, 0 };
	 MxMenuDef change = { "Change", backswitch, 0, 0, 0, 0, 0, 0 };

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

	 desktop.base.object.handler = DesktopHandler;

	 /* Extend the editor's menu */
	 usermenu = MxMenuDefAppend(0, &change);
	 user.data = usermenu;
	 topmenu = MxMenuDefAppend(MxEditorTopmenu, &user);

	 /* Make an editor object with out new menu */
	 MxArgsInit(&editorargs);
	 editorargs.menu.listarea.def = topmenu;

	 MxEditorNew(&desktop.base.object, 10, 10, 100, 100, &editorargs);

	 while (MxDesktopRun(&desktop)) {
	 };

	 MxFree(topmenu);
	 MxFree(usermenu);

	 MxDestroy(&desktop.base.object);
	 return 0;
}
