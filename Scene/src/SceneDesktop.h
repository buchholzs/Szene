#ifndef SCENE_DESKTOP_H
#define SCENE_DESKTOP_H

#include "depui/object/object.h"
#include "depui/desktop/desktop.h"

#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext
#undef GrFont

#include "Controller.h"
#include "Hud.h"
#include "HudRefreshCmd.h"
#include "MoveMode.h"
#include "FlyMode.h"
#include "Scene.h"
#include "WalkMode.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////
// Typen
//
typedef struct SceneDesktop {
		  union {
				MxObject object;
				MxDesktop desktop;
		  } base;
		  scene::Scene *scn;
		  scene::Controller *controller;
		  scene::WalkMode *walkMode;
		  scene::FlyMode *flyMode;

		  pl_uChar ThePalette[768];
		  MxImage *ctx;
		  bool directDisplay;
		  float prevtime;
		  float difftime;
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
