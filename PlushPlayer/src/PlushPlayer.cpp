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
#include <Windows.h>
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
#include "MoveMode.h"
#include "FlyMode.h"
#include "WalkMode.h"

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

const int refresh_ivl = 5;	// Refresh-Interval in msec
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
#else
	  uclock_t oldclk = uclock();
#endif
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
		clock_t start_t = clock();  
		const int tick_ivl = (start_t - oldclk) * 1000 / CLOCKS_PER_SEC;
		oldclk = start_t;

		lastInputPoll += tick_ivl;
		lastScreenRefresh += tick_ivl;

		if ((lastScreenRefresh > refresh_ivl) && desktop.directDisplay) {
			lastScreenRefresh = 0;
			updateScene(&desktop);
		}
		if (lastInputPoll > input_ivl) {
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

		clock_t end_t = clock();
		const int busy_ivl = (end_t - start_t) * 1000 / CLOCKS_PER_SEC;
		Sleep(max(refresh_ivl - busy_ivl, 0));
	  }

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);

	 exit(0);
}

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return main(__argc, __argv);
}
#endif
