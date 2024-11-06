#include <stdlib.h>
#include <stdio.h>
#include "depui/depui.h"

const char *longstring = "DEPUI is a portable graphic user interface library written in the \
language. The docs are quite minimal, but should still work and compile \
for a very wide variety of platforms.\n\
\n\
The code is very modular and (should be) fairly easy to understand. It will \
compile for 32 or 16 bit targets and has been written in a very portable \
way.\n\
\n\
I am releasing this code in order to get feedback as to how everything\
works on different platforms and to encourage discussions and contributions.\n\
\n\
You can find it at: http://huizen.dds.nl/~deleveld/depui.htm\n\
\n\
Right now it has drivers for the following platforms:\n\
 - DOS with DJGPP using Allegro\n\
 - DOS with DJGPP using GRX 2.3\n\
 - DOS with Borland 3.11 using BGI\n\
 - DOS with DJGPP using simple VESA 2.0\n\
 - Linux using Allegro\n\
 - Linux using GRX 2.3 (on top of Svgalib)\n\
 - Linux using Svgalib directly\n\
 - Linux using Nano-X - Contributed by Nick Papadonis\n\
 - DOS with DJGPP using simple VESA 1.0\n\
 - OpenGUI drivers (mouse/keyboard only work under DOS/DJGPP)\n\
 - DOS with TinyPTC (still rather slow, but functional)\n\
 - Linux using X-Windows\n";

int main(int argc, char *argv[])
{
	 MxScrollEditareaArgs editargs;

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
	 MxExitButtonNew(&desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make an editable textarea with some text */
	 MxArgsInit(&editargs);
	 editargs.editarea.textarea.caption = longstring;
	 editargs.editarea.textarea.endtest = MxLineEndWordwrap;
//   editargs.editarea.textarea.endtest = MxLineEndCharwrap;
	 MxScrollEditareaNew(&desktop.base.object, 15, 30, 250, 150, &editargs);

	 /* Run the gui events */
	 while (MxDesktopRun(&desktop)) {
	 };

	 MxDestroy(&desktop.base.object);
	 return 0;
}
