#include "depui/depui.h"

static MxDesktop desktop;

/* Special button handler to make desktop do opaque moves */
void *MxButtonMakeOpaqueHandler(MxObject * object, const MxEvent * const event)
{
	 /* Make the move style opaque when the button is selected */
	 if (event->type == MxEventSelect)
		  Mx.OpaqueMove = MxTrue;

	 /* Otherwise act just like a normal push botton */
	 return MxPushButtonHandler(object, event);
}

/* Special button handler to make desktop do outline moves */
void *MxButtonMakeOutlineHandler(MxObject * object, const MxEvent * const event)
{
	 /* Make the move style outline when the button is selected */
	 if (event->type == MxEventSelect)
		  Mx.OpaqueMove = MxFalse;

	 /* Otherwise act just like a normal push botton */
	 return MxPushButtonHandler(object, event);
}

static void desktop_exit(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 if (selected)
		  MxEventSendSimple(&desktop.base.object, MxEventExit);
}

int main(int argc, char *argv[])
{
	 MxWindow *ourwindow;
	 MxWindowArgs windowargs;

	 MxButton *button;
	 MxButtonArgs buttonargs;

	 /* Initailize the library */
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

	 /* Prepare some window arguments */
	 MxArgsInit(&windowargs);
	 windowargs.caption = "DEPUI";
	 windowargs.uncloseable = MxTrue;

	 /* Add our window to the desktop */
	 ourwindow = MxWindowNew(&desktop.base.object, 10, 10, 150, 150, &windowargs);

	 /* Add an exit button to the window client area */
	 MxArgsInit(&buttonargs);
	 buttonargs.callback = desktop_exit;
	 MxExitButtonNew(ourwindow->client, 10, 10, MxDefault, MxDefault, &buttonargs);

	 /* Add an opaque move button to the window client area */
	 MxArgsInit(&buttonargs);
	 buttonargs.stext.caption = "Opaque move";
	 button = MxPushButtonNew(ourwindow->client, 10, 35, MxDefault, MxDefault, &buttonargs);

	 /* Make this button call the opaque handler */
	 button->base.object.handler = MxButtonMakeOpaqueHandler;

	 /* Add an opaque move button to the window client area */
	 buttonargs.stext.caption = "Outline move";
	 button = MxPushButtonNew(ourwindow->client, 10, 60, MxDefault, MxDefault, &buttonargs);

	 /* Make this button call the outline handler */
	 button->base.object.handler = MxButtonMakeOutlineHandler;

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
