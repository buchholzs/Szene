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

const int refresh_ivl = 5; // Refresh-Inteval in msec


int main(int argc, char *argv[])
{
	 MxButton myexit;
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

	  /* Run the desktop until it wants to exit */
#ifdef WIN32
	  clock_t oldclk = clock();
	  clock_t newclk;
#else
	  uclock_t oldclk = uclock();
	  uclock_t newclk;
#endif

      if (argc != 2 && argc != 1) {
        std::cerr << "Usage: " << argv[0] << " [<scene.scx>]" << std::endl;
        return 1;
      }

	  if (argc == 2) {
		  strcpy(filename, argv[1]);
	  }
	  bool sceneToLoad = filename[0] != '\0';
	  bool initialLoad = true;

	  updateScene(&desktop); // show the blue desktop
      while (MxDesktopRun(&desktop.base.desktop)) {
#ifdef WIN32
		newclk = clock();  
		if (((newclk - oldclk)*1000/CLOCKS_PER_SEC) > refresh_ivl) {
#else 
		newclk = uclock();  
		if (((newclk - oldclk)*1000/UCLOCKS_PER_SEC) > refresh_ivl) {
#endif
		  oldclk = newclk;
		  if (desktop.directDisplay) {
			updateScene(&desktop);
		  }
		}

		if (sceneToLoad) {
			sceneToLoad=false;
			initialLoad=false;
			loadScene(&desktop, filename);
		} else if (initialLoad) {
			initialLoad = false;
			MxEvent event;
			event.type = MxEventKeyUnbound;
			event.key.code = 0x3D; // F3 - Load
			MxEnqueue(&desktop.base.object, &event, 0);
		}
	  }

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);

	 /* Tell the user what was selected */
	 printf("File selected: %s\n", filename);
	 return 0;
}
