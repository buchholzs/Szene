#include "depui/depui.h"

/* Place to put the selected filename */
static char filename[MX_MAX_PATH] = "";

/* Button calback to call up a file selector */
static void callback(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 if (selected) {

		  /* Setup the file selector arguments */
		  MxFileselectorArgs args;

		  MxArgsInit(&args);

		  /* What kind of files are we looking for */
		  strcpy(filename, "");

		  args.file = filename;
		  args.window.caption = "Select a file";
		  MxFileselectorStart(&args, 0, 0);
	 }
}

int main(int argc, char *argv[])
{
	 MxButton myexit;
	 MxButton button;
	 MxButtonArgs buttonargs;

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
	 MxArgsInit(&buttonargs);
	 MxExitButtonConstruct(&myexit, &desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make a buton that will open up a file selector */
	 MxArgsInit(&buttonargs);
	 buttonargs.stext.caption = "Open file selector";
	 buttonargs.callback = callback;
	 MxPushButtonConstruct(&button, &desktop.base.object, 10, 30, MxDefault, MxDefault, &buttonargs);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* CLose and go home */
	 MxDestroy(&desktop.base.object);

	 /* Tell the user what was selected */
	 printf("File selected: %s\n", filename);
	 return 0;
}
