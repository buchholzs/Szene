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

const int screen_w = 800;
const int screen_h = 600;

const std::chrono::milliseconds refresh_ivl(1);	// Refresh-Interval in msec
const std::chrono::milliseconds input_ivl(67);	// Input-Abfrage-Interval in msec

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
	 FullScreen(true);
	
	 /* Make a nice exit button */
	 MxArgsInit(&buttonargs);
	 MxExitButtonConstruct(&myexit, &desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	  /* Run the desktop until it wants to exit */      
	 auto oldclk = chrono::system_clock::now();

	  if (argc == 2) {
		  filename = argv[1];
	  }
	  bool sceneToLoad = filename[0] != '\0';
	  bool initialLoad = true;
	  bool desktopRun = true;
	  std::chrono::milliseconds lastInputPoll(0);
	  std::chrono::milliseconds lastScreenRefresh(0);
	  const std::chrono::milliseconds min_ivl(0);

	  updateScene(&desktop); // show the blue desktop
	  while (desktopRun) {
		// Convert the current time to time since epoch
		auto start_t = chrono::system_clock::now();
		auto tick_ivl = std::chrono::duration_cast<std::chrono::milliseconds>(start_t - oldclk).count();
		oldclk = start_t;

		lastInputPoll += std::chrono::milliseconds(tick_ivl);
		lastScreenRefresh += std::chrono::milliseconds(tick_ivl);

		if ((lastScreenRefresh > refresh_ivl) && desktop.directDisplay) {
			lastScreenRefresh = std::chrono::milliseconds(0);
			updateScene(&desktop);
		}
		if ((lastInputPoll > input_ivl) || !desktop.directDisplay) {
			lastInputPoll = std::chrono::milliseconds(0);
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

		auto end_t = chrono::system_clock::now();
		std::chrono::milliseconds busy_ivl = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t);
		std::chrono::milliseconds used_ivl = refresh_ivl - busy_ivl;

		std::chrono::milliseconds milliseconds = max(used_ivl, min_ivl);

		std::this_thread::sleep_for(milliseconds);
	  }

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);

	 exit(0);
}
