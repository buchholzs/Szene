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
#include <chrono>
#include <thread>
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext
#undef GrFont
#include <depui/depui.h>
#include <depui/graphics/clip.h>
#include <PLUSH.H>

#include "Controller.h"
#include "SceneDesktop.h"
#include "Scene.h"
#include "MoveMode.h"
#include "FlyMode.h"
#include "WalkMode.h"
#include "XScreen.h"

using namespace std;
using namespace scene;

//////////////////////////////////////////////////////////////////////////////
// Konstanten und Statische Variablen
//

#ifdef WIN32
const int screen_w = 800;
const int screen_h = 600;
#else
const int screen_w = 640;
const int screen_h = 480;
#endif

const int refresh_ivl = 1;	// Refresh-Interval in msec
const int input_ivl = 67;	// Input-Abfrage-Interval in msec

int main(int argc, char *argv[])
{
	 /* Place to put the selected filename */
	 std::string filename;

	 MxButton myexit;
	 MxButtonArgs buttonargs;

	 /* Create some drivers specific to the system */
	 SceneDesktop desktop;
	 SceneDesktopArgs desktopargs;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 MxArgsInit(&desktopargs);
	 int maxScreenWidth = screen_w;
	 int maxScreenHeight = screen_h;
	 ScreenResolution(&maxScreenWidth, &maxScreenHeight);
	 desktopargs.mxdesktop.desktop_w = maxScreenWidth;
	 desktopargs.mxdesktop.desktop_h = maxScreenHeight;
	 desktopargs.mxdesktop.desktop_c = 8;
	 desktopargs.mxdesktop.system = &system;
	 desktopargs.mxdesktop.output = &output;
	 desktopargs.mxdesktop.input = &input;
	 desktopargs.mxdesktop.window.caption = "";

	 /* Initialize the library */
	 SceneDesktopConstruct(&desktop, 0, 0, 0, 0, &desktopargs);
	 if (!desktop.base.desktop.ok)
		  return 1;
#ifndef WIN32
	 FullScreen(true);
#endif
	
	 /* Make a nice exit button */
	 MxArgsInit(&buttonargs);
	 MxExitButtonConstruct(&myexit, &desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	  /* Run the desktop until it wants to exit */      
	 auto oldclk = chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()).count();

	  /*
      if (argc != 2 && argc != 1) {
        std::cerr << "Usage: " << argv[0] << " [<scene.scx>]" << std::endl;
        exit(1);
      }
	  */
	  if (argc == 2) {
		  filename = argv[1];
	  }
	  bool sceneToLoad = filename[0] != '\0';
	  bool initialLoad = true;
	  bool desktopRun = true;
	  int lastInputPoll = 0;
	  int lastScreenRefresh = 0;

	  updateScene(&desktop); // show the blue desktop
	  while (desktopRun) {
		// Convert the current time to time since epoch
		auto start_t = chrono::duration_cast<chrono::milliseconds>(
        	chrono::system_clock::now().time_since_epoch()).count();
		const int tick_ivl = start_t - oldclk;
		oldclk = start_t;

		lastInputPoll += tick_ivl;
		lastScreenRefresh += tick_ivl;

		if ((lastScreenRefresh > refresh_ivl) && desktop.directDisplay) {
			lastScreenRefresh = 0;
			updateScene(&desktop);
		}
		if ((lastInputPoll > input_ivl) || !desktop.directDisplay) {
			lastInputPoll = 0;
			desktopRun = MxDesktopRun(&desktop.base.desktop);
		}

		if (sceneToLoad) {
			sceneToLoad=false;
			initialLoad=false;
			desktop.controller->loadScene(filename);
		} else if (initialLoad) {
			initialLoad = false;
			MxEvent event;
			event.type = MxEventKeyUnbound;
			event.key.code = 0x3D; // F3 - Load
			MxEnqueue(&desktop.base.object, &event, 0);
		}

		auto end_t = chrono::duration_cast<chrono::milliseconds>(
        	chrono::system_clock::now().time_since_epoch()).count();
		const int busy_ivl = end_t - start_t;

		const int milliseconds = max(refresh_ivl - busy_ivl, 0);

		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	  }

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);

	 exit(0);
}

