// Copyright (c) 2006, Steffen Buchholz

#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext
#undef GrFont
#include <depui/depui.h>
#include <depui/graphics/clip.h>
#include <plush.h>

#include "Controller.h"
#include "SceneDesktop.h"
#include "Scene.h"
#include "Hud.h"
#include "HudRefreshCmd.h"
#include "MoveMode.h"
#include "FlyMode.h"
#include "WalkMode.h"

using namespace std;
using namespace scene;

//////////////////////////////////////////////////////////////////////////////
// Konstanten und Statische Variablen
//

#ifdef WIN32
const int screen_w = 640;
const int screen_h = 480;
#else
const int screen_w = 640;
const int screen_h = 480;
#endif

  /* Place to put the selected filename */
static char filename[MX_MAX_PATH] = "";

const int refresh_ivl = 200; // Refresh-Inteval in msec


//////////////////////////////////////////////////////////////////////////////
// Forward declarations
//
static void *fileOpenOKSelectedHandler(struct MxObject * object, const MxEvent * const event);

// File | Open Filedialog OK selected
static void *fileOpenOKSelectedHandler(struct MxObject * object, const MxEvent * const event) {
  MxStatictext *okSel	= (MxStatictext *)object;

  switch (event->type) {
  case MxEventOk: 
	  {
		// change dir
#ifdef WIN32
		char *lbs = strrchr(filename, '/');
		if (lbs != NULL) {
			  *lbs='\0';
		}
		char *newDir= lbs == NULL ? NULL : strdup(filename);
		const char *fileName = lbs == NULL ? filename : ++lbs;
#else
		char *newDir = dirname(filename);
		const char *fileName = basename(filename);
#endif
		if (newDir != NULL) {
		  chdir(newDir);
		  free(newDir);
		}
		loadScene((SceneDesktop *)MxParent(&okSel->base.object), fileName);
		MxDestroy(object);	// destroy okSel
	  }
	break;
  default:
	return MxStatictextHandler(object, event);
  }
  return 0;
}


/* Button calback to call up a file selector */
static void fileOpenHandler(MxObject * object, void *data, unsigned int selected)
{
 if (selected) {
  /* text for filename */
  MxStatictextArgs textargs;
  MxArgsInit(&textargs);
  textargs.caption = "Hallo";
  MxStatictext *okSel = MxStatictextNew(MxParent(object), 0, 0, 0, 0, &textargs);
  okSel->base.object.handler = fileOpenOKSelectedHandler;
//  MxHide(&okSel->base.object, MxTrue);

  /* Setup the file selector arguments */
  MxFileselectorArgs args;

  MxArgsInit(&args);
  args.file = (char *)filename;
  strcpy(args.file, "");
  args.pattern = "*.SCX;*.scx";
  args.attrib = FA_RDONLY | FA_DIREC;
  args.window.caption = "Select scene file";

  /* Start the file selector */
  MxFileselector *fs = MxFileselectorStart(&args, MxParent(object), &okSel->base.object);
 }
}

extern "C" int GRXMain(int argc, char *argv[])
{
	 MxButton myexit;
	 MxButton button;
	 MxButtonArgs buttonargs;

	 /* Create some drivers specific to the system */
	 SceneDesktop desktop;
	 SceneDesktopArgs desktopargs;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 MxArgsInit(&desktopargs);

	 desktopargs.mxdesktop.desktop_w = screen_w;
	 desktopargs.mxdesktop.desktop_h = screen_h;
	 desktopargs.mxdesktop.desktop_c = 8;
	 desktopargs.mxdesktop.system = &system;
	 desktopargs.mxdesktop.output = &output;
	 desktopargs.mxdesktop.input = &input;
	 desktopargs.mxdesktop.window.caption = "";

	 /* Initialize the library */
	 SceneDesktopConstruct(&desktop, 0, 0, 0, 0, &desktopargs);
	 if (!desktop.base.desktop.ok)
		  return 1;
	
	 /* Make a nice exit button */
	 MxArgsInit(&buttonargs);
	 MxExitButtonConstruct(&myexit, &desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Make a button that will open up a file selector */
	 MxArgsInit(&buttonargs);
	 buttonargs.stext.caption = "Open file selector";
	 buttonargs.callback = fileOpenHandler;
	 MxPushButtonConstruct(&button, &desktop.base.object, 10, 30, MxDefault, MxDefault, &buttonargs);

	  /* Run the desktop until it wants to exit */
	  clock_t oldclk = clock();
	  clock_t newclk;

      if (argc != 2 && argc != 1) {
        std::cerr << "Usage: " << argv[0] << " [<scene.scx>]" << std::endl;
        return 1;
      }

	  if (argc == 2) {
		  strcpy(filename, argv[1]);
	  }
	  bool sceneToLoad = filename[0] != '\0';


	  while (MxDesktopRun(&desktop.base.desktop)) {
		newclk = clock();  
		if (((newclk - oldclk)*1000/CLOCKS_PER_SEC) > refresh_ivl) {
		  oldclk = newclk;
		  updateScene(&desktop);
		}

		if (sceneToLoad) {
			sceneToLoad=false;
			loadScene(&desktop, filename);
		}
	  }

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);

	 /* Tell the user what was selected */
	 printf("File selected: %s\n", filename);
	 return 0;
}
