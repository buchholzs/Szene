// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#pragma warning (disable : 4786)

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <depui/depui.h>
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext 
#undef GrFont 

#include "App.h"
#include "Desktop.h"
#include "Scene.h"

using namespace std;

namespace scene {

//////////////////////////////////////////////////////////////////////////////
// Konstanten und statische Variablen
//
  const int BPP = 8;
#ifdef WIN32
  const int screen_w = 320;
  const int screen_h = 240;
  const int refresh_ivl = 54; // Refresh-Interval Display in msec
#else
  const int screen_w = 640;
  const int screen_h = 480;
  const int refresh_ivl = 0; // Refresh-Interval Display in msec
#endif
  const char *WINTITLE="GRX Scene";

//////////////////////////////////////////////////////////////////////////////
// Forward declarations
//
  static void settextmode();

  // ------------------------------------------------------------
  // Konstruktor
  //
  App::App (std::string filename) :
    desktop_(screen_w, screen_h),
    hud_(Desktop::LIGHTGRAY),
    filename_(filename)
  {
    desktop_.setHud(&hud_);
  }

  // ------------------------------------------------------------
  // Destruktor
  //
  App::~App ()
  {}

  // ------------------------------------------------------------
  // Ausgabe der Szene und der GUI
  //
  void App::run ()
  {
    char lastmessage[80] = "";
    int width=screen_w, height=screen_h, bpp=BPP;
    bool sceneToLoad = filename_ != "";

    /* Run the desktop until it wants to exit */
    clock_t oldclk = clock();
    clock_t newclk = 0;
    clock_t difftime = 0;

    MxDesktop * dsk = desktop_.getDesktop();
    while (MxDesktopRun(dsk)) {
      newclk = clock();  
      difftime = (newclk - oldclk)*1000/CLOCKS_PER_SEC;

      if (difftime >= refresh_ivl) {
        oldclk = newclk;
        desktop_.display();
      }

      if (sceneToLoad) {
        sceneToLoad=false;
        desktop_.loadScene(filename_);
      }
    }
    /* Close and go home */
    GrSetMode( GR_default_text );
  }

  // ------------------------------------------------------------
  // Textmodus bei exit()
  //
  static void settextmode() {
    GrSetMode( GR_default_text );
  }
} // scene 

extern "C" int
main(int argc, char **argv)
{
  try 
    {
      if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <scene.scx>" << std::endl;
        return 1;
      }
      
      // atexit: textmode
      atexit(scene::settextmode);

      // Rendering
      std::cout << "Starting" << std::endl;
      scene::App app(argv[1]);
      app.run();
    }
  catch (exception &e) 
    {
      GrSetMode( GR_default_text );
      std::cerr << "Exception: " << e.what( ) << endl;
    };
  return 0;
}
