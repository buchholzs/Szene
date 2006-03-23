// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _Desktop_H_
#define _Desktop_H_

#include <string>
#include <plush.h>
#include <depui/depui.h>

#include "Controller.h"
#include "Scene.h"
#include "WalkMode.h"
#include "FlyMode.h"

namespace scene {

class Hud;

class Desktop {

public:
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

  const static int CTextColor;	// Idx of text color
  const static int CFixColors;	// Readonly colors
  const static float velocity;	// m/s
  const static float mouse_sens;// mouse sensitivity
  const static int reset_area;	// constraint mouse movement around center
  const static int avg_frame_window;	// average time over n frames
  
 typedef struct SceneDesktop {
	  union {
			MxObject object;
			MxDesktop mx_desktop;
	  } base;
	  scene::Desktop *sc_desktop;
 } ScDesktop;

public:
	// Konstruktor
	Desktop(int screenWidth,int screenHeight);
	// Destruktor
	virtual ~Desktop ();
	// return MxDesktop
	MxDesktop *getDesktop() { return &desktop_.base.mx_desktop; }
	// return GrContext
	MxImage *getCtx() { return ctx_; }	
	// set HUD
	void setHud(Hud *hud) { hud_=hud; }
	// Szene neu laden
	void loadScene(const std::string &filename);
	// Palette neu laden
	void reloadPalette();
	// Scene rendern und ausgeben
	void display();
	// Direktausgabe
	void setDirectDisplay(bool direct) { direct_ = direct; }

private:
	// mouse to origin
	void mouse_reset();
	// get mouse coords
	void Desktop::mouse_get(const MxEvent *evt, int &mouse_x, int &mouse_y);
	// static desktop handler
	friend void *DesktopHandler(MxObject * object, const MxEvent * const event);
private:
	SceneDesktop desktop_;		// Desktop
	WalkMode walkMode_;		// FlyMode
	FlyMode flyMode_;			// MoveMode
	Controller controller_;		// Controller
	MxAlertArgs msgOk;		// Alert
	char lastmessage_[256]; // Message for Alert
	Scene scene_;	// Scene
	MxImage *ctx_;	// Backbuffer
	pl_uChar palette_[768]; // Palette
	pl_Cam *cam_;			// Kamera
	Hud *hud_;				// HUD
	signed short int old_mouse_x_;
	signed short int old_mouse_y_;
	clock_t prevtime_; // previous clock()
	int frames_; // count frames for calculating fps
	float elapsedTime_; // for calculating fps, in msec
	float avgDifftime_; // average difftime (based on fps)
	float difftime_; // diff (current frame - last frame) in msec
	bool direct_; // display indirect in event loop or direct in display
};

} // scene

#endif
