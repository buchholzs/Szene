#include "depui/depui.h"

static MxDesktop desktop;

static void *OurDesktopHandler(MxObject * object, const MxEvent * const event)
{
	 switch (event->type) {

	 case MxEventExpose:
		  /* Do the normal desktop drawing */
		  MxDesktopHandler(object, event);

		  /* And put a little message up */
		  MxFontScreenRender(0, "Hello World", MxFontDefault, 100, 100, MxColorFore, MxColorBack);
		  break;

		  /* Wait for an unused escape key */
	 case MxEventKeyUnbound:
		  if (event->key.code == 0x1b) {

				/* Make an event to force an exit */
				MxEventSendSimple(&desktop.base.object, MxEventExit);

				/* Say that we used the key */
				return object;
		  }
		  /* They key was not what we wanted */
		  break;

		  /* Otherwise behave just as a regular desktop */
	 default:
		  return MxDesktopHandler(object, event);
	 }
	 return 0;
}

int main(int argc, char *argv[])
{
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

	 /* Tell the desktop to use our handler */
	 desktop.base.object.handler = OurDesktopHandler;

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);
	 return 0;
}
