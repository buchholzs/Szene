#pragma warning (disable : 4786)

#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <depui/depui.h>
#include <depui/config.h>
#include <depui/args/args.h>
#include <depui/object/object.h>
#include <depui/graphics/clip.h>
#include "Controller.h"
#include "Hud.h"
#include "MoveMode.h"
#include "FlyMode.h"
#include "Scene.h"
#include "WalkMode.h"
#include "scenedbg.h"
#include "SceneDesktop.h"

using namespace std;
using namespace scene;

//////////////////////////////////////////////////////////////////////////////
// Constants and static variables
//
static void mouse_get(SceneDesktop * desktop, const MxEvent *event, int &mouse_x, int &mouse_y);
static void handleError(SceneDesktop * desktop, const string &msg);

const float mouse_sens  = 2.5 * 2048.0/32768.0;		// mouse sensitivity
const int reset_area = 20;	// constraint mouse movement around center

//////////////////////////////////////////////////////////////////////////////
// Depui-Handler
//
void *SceneDesktopHandler(MxObject * object, const MxEvent * const event)
{
  SceneDesktop *desktop = (SceneDesktop *) object;
  int screen_w = ((GrContext2 *)desktop->ctx)->gc_xmax + 1;
  int screen_h = ((GrContext2 *)desktop->ctx)->gc_ymax + 1;
  int mouse_x, mouse_y;
 
  switch (event->type) {
  case MxEventDestroy:
	  GrDestroyContext((struct _GR_context *)desktop->ctx);
	  break;

  case MxEventPointerEnter:
	   MxPointerWantMove(object, MxTrue);
	   // Fall through

  case MxEventPointerMove: 
	  if (desktop->directDisplay) {
		mouse_x = event->point.x;
		mouse_y = event->point.y;
		mouse_get(desktop, event, mouse_x, mouse_y);
		desktop->controller->panView(mouse_x*mouse_sens);
		desktop->controller->pitchView(mouse_y*mouse_sens);

		if (!((event->point.x >= reset_area && event->point.x <= screen_w - reset_area) &&
			(event->point.y >= reset_area && event->point.y <= screen_h - reset_area)))
			mouse_reset(desktop);
	  }
	  break;						   

    /* Escape key */
  case MxEventKeyUnbound:
	  switch (event->key.code) {
		  case 0x1b:
			setDirectDisplay(desktop, !desktop->directDisplay);
			if (!desktop->directDisplay) {
				// Show the exit button
				desktop->controller->refreshDesktop();
			}
			return object;
		  case 0x3B: // f1
			setDirectDisplay(desktop, false);
			desktop->controller->showHelp();
			return object;
		  case 0x3D: // f3
			setDirectDisplay(desktop, false);
			desktop->controller->openScene();
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
		  case ' ':
			  desktop->controller->setPause(!desktop->controller->getPause());
			  return object;
		  case 'r':
			if (desktop->controller->getFilename() != "") {
			  desktop->controller->loadScene(desktop->controller->getFilename());
			}
			return object;
		  case 'q':
			/* Make an event to force an exit */
			MxEventSendSimple(&desktop->base.object, MxEventExit);
			return object;
	  }
	  break;

  case MxEventExpose:
    {
      /* Blit the Szene */
      for (unsigned int i = 0; i < MxRegionNumber(mx_region); i++) {
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
#ifdef WIN32
	desktop->mouseWarp = true;
#else
	desktop->mouseWarp = false; // wayland doesn't support XWarpPointer
	DBGPRINTF(("Fenstermanager unterstützt kein GrMouseWarp!"));    
#endif

	desktop->scn = std::make_shared<scene::Scene>(args.mxdesktop.desktop_w,args.mxdesktop.desktop_h);

	GrResetColors(); // Palette mode
	int nFreeCols = GrNumFreeColors();
	desktop->scn->setPaletteMode( nFreeCols != 0);

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

	desktop->scn->setEgaColors(egacolors);

	desktop->base.object.handler = SceneDesktopHandler;
	desktop->lastmessage[0] = '\0';

	// create image for scene
	if (desktop->scn->getPaletteMode()) {
		char* memory[4] = { (char*)desktop->scn->getFrameBuffer(),0,0,0 };
		desktop->ctx = (MxImage*)GrCreateContext(args.mxdesktop.desktop_w, args.mxdesktop.desktop_h, memory, NULL);
	} else {
		desktop->ctx = (MxImage*)GrCreateContext(args.mxdesktop.desktop_w,args.mxdesktop.desktop_h,NULL,NULL);
	}

	// create hud
	desktop->hud = std::make_shared<Hud>(egacolors[LIGHTGRAY], (struct _GR_context*)desktop->ctx);

	// set mousecolor
#ifdef GRX_NATIVE_POINTER
	GrMouseSetColors(egacolors[WHITE], egacolors[BLACK]);
#endif

	// create walk-, flymode
	desktop->walkMode = std::make_shared<WalkMode>(desktop->scn, desktop->scn->getMoveSpeed(), desktop->scn->getTurnSpeed());
	desktop->flyMode = std::make_shared<FlyMode>(desktop->scn, desktop->scn->getMoveSpeed(), desktop->scn->getTurnSpeed());

	// create controller
	std::shared_ptr<MoveMode> moveMode = desktop->walkMode;
	std::shared_ptr<Scene> scene = desktop->scn;
	desktop->controller = std::make_shared<Controller>(moveMode, scene, desktop);

	desktop->ignorePointerMove = false;

	desktop->frames = 0;
	desktop->prevtime = 0;
	desktop->elapsedTime = 0;
	desktop->difftime = 0;
	desktop->prevtime = clock(); 
	desktop->old_mouse_x = args.mxdesktop.desktop_w / 2;
	desktop->old_mouse_y = args.mxdesktop.desktop_h / 2;
	desktop->mx = 0;
	desktop->my = 0;
	desktop->hasPaused = false;
	if (desktop->mouseWarp) {
		GrMouseWarp(desktop->old_mouse_x, desktop->old_mouse_y);
	}
	setDirectDisplay(desktop, true);
}

// Update desktop with new scene
void updateScene(SceneDesktop * desktop) {
  clock_t currtime = clock();
  assert(desktop->prevtime <= currtime);
  desktop->difftime = (float)(currtime - desktop->prevtime)*1000.0f / (float) CLOCKS_PER_SEC;
  assert((long)difftime >= 0);
  desktop->elapsedTime += desktop->difftime; // in msec

  desktop->prevtime = currtime;
  pl_Cam*	cam = desktop->scn->getCurrCamera ();

  if (desktop->elapsedTime >= 1000.0) {
	float fps = ((float)desktop->frames)*1000.0f / desktop->elapsedTime;
	desktop->hud->setFPS(fps);
	desktop->frames = 0;
	desktop->elapsedTime = 0.0f;
  }
  if (cam) {
	  desktop->hud->setPosition(cam->X, cam->Y, cam->Z, cam->Pitch, cam->Pan, cam->Roll);
  } else {
	  desktop->hud->setPosition(0,0,0,0,0,0);
  }
  
  if (cam) {
	desktop->scn->render();
	desktop->frames++;
	if (desktop->hasPaused) {
		desktop->hasPaused = false;
	} else {
		// only execute animations if not paused before
		desktop->scn->execute(desktop->difftime);
	}	
	if (!desktop->scn->getPaletteMode()) {
		desktop->scn->LoadContextFromFramebuffer((GrContext2*)desktop->ctx);
	}
	desktop->hud->display(); // show Hud last
  } else {
	GrSetContext((GrContext2*)desktop->ctx);
	GrClearContext( MxColorDesktop );
	GrTextXY(5,((GrContext2*)desktop->ctx)->gc_ymax-15,desktop->lastmessage,GrBlack(),MxColorDesktop);
	GrSetContext(NULL);
  }
  if (desktop->directDisplay) {
		  MxBlitToScreenFast(desktop->ctx, NULL, 
					 0, 0, 
					 desktop->base.object.position.x1, 
					 desktop->base.object.position.y1,
					 desktop->base.object.position.x2 - desktop->base.object.position.x1, 
					 desktop->base.object.position.y2 - desktop->base.object.position.y1);
  } else {
	MxRefresh(&desktop->base.object);
  }
}

void mouse_reset(SceneDesktop * desktop) 
{
  MxImage *ctx = desktop->ctx;
  int screen_w = ((GrContext2 *)ctx)->gc_xmax + 1;
  int screen_h = ((GrContext2 *)ctx)->gc_ymax + 1;

  GrMouseEvent evt;
  if (desktop->mouseWarp) {
  	GrMouseWarp(screen_w / 2, screen_h / 2);
  }
  GrMouseGetEvent(GR_M_MOTION | GR_M_NOPAINT, &evt);
  desktop->old_mouse_x = evt.x;
  desktop->old_mouse_y = evt.y;
  desktop->mx = 0;
  desktop->my = 0;
}

static void mouse_get(SceneDesktop * desktop, const MxEvent *event, int &mouse_x, int &mouse_y) 
{
  mouse_x = ((desktop->old_mouse_x - event->point.x) + desktop->mx) * 6 / 10;
  mouse_y = ((desktop->old_mouse_y - event->point.y) + desktop->my) * 6 / 10;
  desktop->mx = mouse_x;
  desktop->my = mouse_y;
  desktop->old_mouse_x = event->point.x;
  desktop->old_mouse_y = event->point.y;
}

void setDirectDisplay(SceneDesktop* desktop, bool directDisplay)
{
	if (desktop->directDisplay == directDisplay) {
		return;
	}
	else {
		if (directDisplay) {
			// hide mouse
#ifdef GRX_NATIVE_POINTER
			GrMouseEraseCursor();
#else
			mx_output->MouseShow(0);
#endif
			mouse_reset(desktop);
		}
		else {
			// show mouse
#ifdef GRX_NATIVE_POINTER
			GrMouseDisplayCursor();
#else
			mx_output->MouseShow(1);
#endif
			desktop->hasPaused = true; // animations paused
		}
		desktop->directDisplay = directDisplay;
	}
}