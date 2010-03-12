#ifndef SCENE_DESKTOP_H
#define SCENE_DESKTOP_H

#include <string>
#include "depui/object/object.h"
#include "depui/desktop/desktop.h"
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext
#undef GrFont
#include <plush.h>

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
		scene::Controller *controller;
		scene::FlyMode *flyMode;
		scene::Hud *hud;				// HUD
		scene::WalkMode *walkMode;
		scene::Scene *scn;
		std::string *filename;  

		pl_uChar ThePalette[768];
		MxImage *ctx;
		
		signed short int old_mouse_x;
		signed short int old_mouse_y;

		int frames; // count frames for calculating fps
		clock_t prevtime; //
		float elapsedTime; // for calculating fps, in msec
		float difftime; // diff (current frame - last frame) in msec
		bool directDisplay; // display indirect in event loop or direct in display
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
void loadScene(SceneDesktop *desktop, const std::string &filename);
void updateScene(SceneDesktop *desktop);
void reloadPalette(SceneDesktop *desktop);

#ifdef __cplusplus
}
#endif
#endif
