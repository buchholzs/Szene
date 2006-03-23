#include "depui/depui.h"

int main(int argc, char *argv[])
{
	 MxButton button;

	 MxSliderArgs sliderargs;

	 /* Create some drivers specific to the system */
	 MxDesktop desktop;
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

	 /* Make some sliders */
	 MxArgsInit(&sliderargs);
	 sliderargs.range = 100;
	 sliderargs.thumb = 100;

	 MxSliderVNew(&desktop.base.object, 10, 30, MxDefault, 100, &sliderargs);

	 sliderargs.range = 100;
	 sliderargs.thumb = 50;
	 sliderargs.border = 5;

	 MxSliderHNew(&desktop.base.object, 30, 30, 100, 25, &sliderargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
