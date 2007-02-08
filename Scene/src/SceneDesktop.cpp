#include "SceneDesktop.h"

#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <depui/depui.h>
#include <depui/config.h>
#include <depui/args/args.h>
#include <depui/object/object.h>
#include <depui/graphics/clip.h>

using namespace std;
using namespace scene;

//////////////////////////////////////////////////////////////////////////////
// Konstanten und Statische Variablen
//
const int CFixColors = 20;	// Readonly colors
const float velocity  = 200.0f / 1000.0f;	// m/s

static char lastmessage[256] = "";

static MxAlertArgs msgOk = { "Alert", lastmessage,
			 {"Ok", 0, MxFalse},
			 {NULL, 0, MxFalse},
			 {NULL, 0, MxFalse} };

//////////////////////////////////////////////////////////////////////////////
// Depui-Handler
//
void *SceneDesktopHandler(MxObject * object, const MxEvent * const event)
{
  SceneDesktop *desktop = (SceneDesktop *) object;
 
  switch (event->type) {
    /* Escape key */
  case MxEventKeyUnbound:
	  switch (event->key.code) {
		  case 0x1b:
			/* Make an event to force an exit */
			MxEventSendSimple(&desktop->base.object, MxEventExit);
			return object;
		  case 0x3D: // f3
			desktop->directDisplay = false;
			desktop->controller->loadScene(desktop);
			return object;
		  case 0x3F: // f5
			MxEnqueueRefresh(&desktop->base.object, MxTrue);
			return object;
		  case 0x44: // f10
			  desktop->controller->setMoveMode( desktop->walkMode );
			return object;
		  case 0x43: // f9
			desktop->controller->setMoveMode( desktop->flyMode );
			return object;
		  case 'w':
			desktop->controller->moveForward(desktop->difftime);
			return object;
		  case 'a':
			desktop->controller->moveLeft(desktop->difftime);
			return object;
		  case 's':
			desktop->controller->moveBackward(desktop->difftime);
			return object;
		  case 'd':
			desktop->controller->moveRight(desktop->difftime);
			return object;
	  }
	  break;

  case MxEventExpose:
    {
      /* Blit the Szene */
      for (int i = 0; i < MxRegionNumber(mx_region); i++) {
		const MxRect *const s = MxRegionRect(mx_region, i);

		int x1 = s->x1, y1 = s->y1, x2 = s->x2, y2 = s->y2;
		if (!MxClipRect(0, 0, 
				((GrContext2 *)desktop->ctx)->gc_xmax,
				((GrContext2 *)desktop->ctx)->gc_ymax,
				x1, y1, x2, y2)) {

		  MxBlitToScreenFast(desktop->ctx, NULL, 
					 x1, y1, x1, y1,
					 x2 - x1 + 1, y2 - y1 + 1);
		}
      }
    }
    return 0;

    /* Otherwise behave just as a regular desktop */
  default:
    return MxDesktopHandler(object, event);
  }
  return MxDesktopHandler(object, event);
}

void SceneDesktopConstruct(SceneDesktop * desktop, int x, int y, int w, int h, SceneDesktopArgs * userargs)
{
	SceneDesktopArgs args;

	MxUserArgsInit(args, userargs);

	MxDesktopConstruct(&desktop->base.desktop, x, y, w, h, &args.mxdesktop );

	GrResetColors(); // Palette mode
	GrColor *egacolors = GrAllocEgaColors();

	MxColorFore = egacolors[BLACK];
	MxColorBack = egacolors[LIGHTGRAY];
	MxColorObjectFore = egacolors[LIGHTBLUE];
	MxColorObjectBack = egacolors[BLUE];

	MxColorSelectedFore = egacolors[BLACK];
	MxColorSelectedBack = egacolors[LIGHTBLUE];

	MxColorLight = egacolors[WHITE];
	MxColorMed = egacolors[LIGHTGRAY];
	MxColorDark = egacolors[DARKGRAY];
	MxColorDesktop = egacolors[BLUE];
	MxColorFocus = egacolors[LIGHTBLUE];
	MxColorDisabled = egacolors[DARKGRAY];

	desktop->base.object.handler = SceneDesktopHandler;
	desktop->scn = new scene::Scene(args.mxdesktop.desktop_w,args.mxdesktop.desktop_h);
	lastmessage[0] = '\0';

	// create image for scene
	char *memory[4] = {(char *)desktop->scn->getFrameBuffer(),0,0,0};
	desktop->ctx = (MxImage*)GrCreateContext(args.mxdesktop.desktop_w,args.mxdesktop.desktop_h,memory,NULL);

	// clear palette
	memset(desktop->ThePalette, 0, sizeof desktop->ThePalette);

	// create walk-, flymode
	desktop->walkMode = new WalkMode(desktop->scn, velocity, velocity);
	desktop->flyMode = new FlyMode(desktop->scn, velocity, velocity);

	// create controller
	desktop->controller = new Controller(desktop->walkMode, desktop->scn);

}

// Szene neu laden
void loadScene(SceneDesktop * desktop, const std::string &filename) {
  try {
    desktop->scn->loadXML(filename);
	reloadPalette(desktop);
    strcpy(lastmessage, (std::string(filename) + " loaded.").c_str());
  } catch (Scene::IOError &) {
    ostringstream msg;
    msg << filename << ": file not found"; 
    strcpy(lastmessage, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop->base.object);
    return;
  } catch (Scene::ParseError &pe) {
    ostringstream msg;
    msg << filename << ':' << pe.getLine() << ": error: " << pe.what(); 
    strcpy(lastmessage, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop->base.object);
    return;
  }
}

// MatEdit aktualisieren nach GUI Änderungen
//
void updateScene(SceneDesktop * desktop) {
  clock_t currtime = clock();
  assert(desktop->prevtime <= currtime);
  desktop->difftime = (float)(currtime - desktop->prevtime)*1000.0 / (float) CLOCKS_PER_SEC;
  assert((long)difftime >= 0);
  //selapsedTime_ += difftime_;

  desktop->prevtime = currtime;
  pl_Cam*	cam = desktop->scn->getCurrCamera ();
  if (cam) {
	desktop->scn->render();
	list<string> l;
  } else {
	GrSetContext((GrContext2*)desktop->ctx);
	GrClearContext( MxColorDesktop );
	GrTextXY(5,((GrContext2*)desktop->ctx)->gc_ymax-15,lastmessage,GrBlack(),MxColorDesktop);
	GrSetContext(NULL);
  }
  MxRefresh(&desktop->base.object);
}

void reloadPalette(SceneDesktop * desktop) 
{
  int i;
  // Fixed colors
  desktop->scn->makePalette(desktop->ThePalette, CFixColors, 255);
  for (i = CFixColors; i < 256; i++) {
    GrSetColor(i, desktop->ThePalette[ i*3 ], desktop->ThePalette[ i*3 + 1], desktop->ThePalette[ i*3 + 2 ]);
  }
}
