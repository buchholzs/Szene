#include "depui/depui.h"

/* When the putton is pressed, exit the root window */
static void button_callback(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;

	 if (!selected)
		  return;
        
    MxpAlertArgs alert;

    alert.caption = "Alert";
    alert.message = "This is an alert";
    alert.button1.caption = "One";
    alert.button2.caption = "Two";
    alert.button3.caption = "Three";

	 MxAlertStart(alert, 0);
}

static MxListDef shortlist[] = {
	 {"Short0", 0, 0, 0, 0, 0, 0, 0},
	 {"Short1", 0, 0, 0, 0, 0, 0, 0},
	 {"Short2", 0, 0, 0, 0, 0, 0, 0},
	 {"Short3", 0, 0, 0, 0, 0, 0, 0},
	 {"Short4", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
};

int main(int argc, char *argv[])
{
	 /* Create some drivers specific to the system */
	 MxpDesktopArgs desktopargs;
    
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

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
	 MxpDesktop desktop(0, 0, 0, 0, &desktopargs);
	 if (!desktop.ok)
		  return 1;

    MxpExitButton b1(desktop, 0, 0);
    
	 MxpButtonArgs buttonargs;
    
	 buttonargs.stext.caption = "Push to alert";
	 buttonargs.callback = button_callback;
	 MxpPushButton b2(desktop, 10, 25, MxDefault, MxDefault, &buttonargs);

	 buttonargs.Reset();
	 buttonargs.stext.caption = "Toggle";
	 MxpToggleButton b3(desktop, 10, 55, MxDefault, MxDefault, &buttonargs);

    MxpCancelButton b4(desktop, 10, 85);
    MxpOkButton b5(desktop, 10, 115);

    MxpList list(desktop, 150, 25, 50, 50);
    list.DefSet(shortlist, MxFalse);

    (void) b1;
    (void) b2;
    (void) b3;
    (void) b4;
    (void) b5;

    MxpWindow w1(desktop, 100, 25, 100, 100, 0);
    MxpEditor e1(desktop, 110, 50, 100, 100, 0);

    (void) w1;
    (void) e1;
    
	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 return 0;
}
