#ifndef SCENE_DESKTOP_H
#define SCENE_DESKTOP_H

#include <string>
#include <memory>
#include "depui/object/object.h"
#include "depui/desktop/desktop.h"
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext
#undef GrFont
#include <PLUSH.H>

#ifdef __cplusplus
extern "C" {
#endif

namespace scene {
	class Controller;
	class Hud;
	class FlyMode;
	class WalkMode;
	class Scene;
}

//////////////////////////////////////////////////////////////////////////////
// Typen
//
typedef struct SceneDesktop {
		union {
			MxObject object;
			MxDesktop desktop;
		} base;
		std::shared_ptr<scene::Controller> controller;
		std::shared_ptr<scene::FlyMode> flyMode;
		std::shared_ptr<scene::WalkMode> walkMode;
		std::shared_ptr<scene::Scene> scn;
		std::shared_ptr<scene::Hud> hud;

		MxImage *ctx;
		
		signed short int old_mouse_x;
		signed short int old_mouse_y;
		signed short int mx;
		signed short int my;

		int frames; // count frames for calculating fps
		clock_t prevtime; //
		int elapsedTime; // for calculating fps, in msec
		int difftime; // diff (current frame - last frame) in msec
		bool directDisplay; // display indirect in event loop or direct in display
		bool ignorePointerMove; // ignore last MxEventPointerMove event
		char lastmessage[256]; // status message
		bool mouseWarp; // mouse warp on/off
		bool hasPaused; // animations paused due to GUI interaction
	 } SceneDesktop;

	 typedef struct SceneDesktopArgs {
		  MxObjectArgs object;	  /* Must be first */

		  MxDesktopArgs mxdesktop;
	 } SceneDesktopArgs;

//////////////////////////////////////////////////////////////////////////////
// Konstanten und Statische Variablen
//
enum ega_colors { 
  BLACK        =0, 
  BLUE         =1,
  GREEN        =2,
  CYAN         =3,
  RED          =4,
  MAGENTA      =5,
  BROWN        =6,
  LIGHTGRAY    =7,
  DARKGRAY     =8,
  LIGHTBLUE    =9,
  LIGHTGREEN   =10,
  LIGHTCYAN    =11,
  LIGHTRED     =12,
  LIGHTMAGENTA =13,
  YELLOW       =14,
  WHITE        =15};


void *SceneDesktopHandler(MxObject * object, const MxEvent * const event);
void SceneDesktopConstruct(SceneDesktop * desktop, int x, int y, int w, int h, SceneDesktopArgs * args);
void updateScene(SceneDesktop * desktop);
void mouse_reset(SceneDesktop * desktop);
void setDirectDisplay(SceneDesktop* desktop, bool directDisplay);

#ifdef __cplusplus
}
#endif
#endif
