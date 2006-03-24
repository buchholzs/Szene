// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#pragma warning (disable : 4786)

#include "Desktop.h"

#include <sstream>
#include <stdexcept>
#include <string>
#include <time.h>
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext
#undef GrFont
#include <depui/depui.h>
#include <depui/graphics/clip.h>
#include <plush.h>

#include "Hud.h"
#include "HudRefreshCmd.h"

using namespace std;

namespace scene {

  const int Desktop::CTextColor = 9;	// Idx of text color
  const int Desktop::CFixColors = 20;	// Readonly colors
  const float Desktop::velocity  = 200.0f / 1000.0f;	// m/s
  const float Desktop::mouse_sens  = 2.5 * 2048.0/32768.0;		// mouse sensitivity
  const int Desktop::reset_area = 20;	// constraint mouse movement around center
  const int Desktop::avg_frame_window = 10; // average time over n frames

//////////////////////////////////////////////////////////////////////////////
// Depui-Handler
//
void *DesktopHandler(MxObject * object, const MxEvent * const event)
{
  scene::Desktop::ScDesktop *desktop = (scene::Desktop::ScDesktop *) object;
  MxImage *ctx = desktop->sc_desktop->getCtx();
  Controller *controller = &desktop->sc_desktop->controller_;
  MoveMode *walkMode = &desktop->sc_desktop->walkMode_;
  MoveMode *flyMode = &desktop->sc_desktop->flyMode_;
  int screen_w = ((GrContext2 *)ctx)->gc_xmax + 1;
  int screen_h = ((GrContext2 *)ctx)->gc_ymax + 1;
  int mouse_x, mouse_y;
  float difftime = desktop->sc_desktop->avgDifftime_;
  
  switch (event->type) {
  case MxEventPointerEnter:
	GrMouseWarp(screen_w / 2, screen_h / 2);
    desktop->sc_desktop->old_mouse_x_ = screen_w / 2;
    desktop->sc_desktop->old_mouse_y_ = screen_h / 2;
    MxPointerWantMove(object, MxTrue);

		  /* Fall through */
  case MxEventPointerMove: 
	  {
	  mouse_x = event->point.x;
	  mouse_y = event->point.y;
	  desktop->sc_desktop->mouse_get(event, mouse_x, mouse_y);
	  controller->panView(mouse_x*Desktop::mouse_sens);
	  controller->pitchView(mouse_y*Desktop::mouse_sens);

	  if (!((event->point.x >= Desktop::reset_area && event->point.x <= screen_w - Desktop::reset_area) &&
		(event->point.y >= Desktop::reset_area && event->point.y <= screen_h - Desktop::reset_area)))
      desktop->sc_desktop->mouse_reset();
	  }
	  break;						   

  /* Escape key */
  case MxEventKeyUnbound:
	  switch (event->key.code) {
		  case 0x1b:
			/* Make an event to force an exit */
			MxEventSendSimple(&desktop->base.object, MxEventExit);
			return object;
		  case 0x44: // f10
			controller->setMoveMode( walkMode );
			return object;
		  case 0x43: // f9
			controller->setMoveMode( flyMode );
			return object;
		  case 'w':
			controller->moveForward(difftime);
			return object;
		  case 'a':
			controller->moveLeft(difftime);
			return object;
		  case 's':
			controller->moveBackward(difftime);
			return object;
		  case 'd':
			controller->moveRight(difftime);
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
				((GrContext2 *)ctx)->gc_xmax,
				((GrContext2 *)ctx)->gc_ymax,
				x1, y1, x2, y2)) {

		  MxBlitToScreenFast(ctx, NULL, 
					 x1, y1, x1, y1,
					 x2 - x1 + 1, y2 - y1 + 1);
		}
      }
    }
    break;

    /* Otherwise behave just as a regular desktop */
  default:
    return MxDesktopHandler(object, event);
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
// Methods
//

// ------------------------------------------------------------
// Konstruktor
//
Desktop::Desktop(int screenWidth,int screenHeight) :
	walkMode_(&scene_, velocity, velocity),
	flyMode_(&scene_, velocity, velocity),
	controller_(&walkMode_, &scene_),
	scene_(screenWidth, screenHeight),
	cam_(NULL),
	hud_(NULL),
	old_mouse_x_(0),
	old_mouse_y_(0),
	prevtime_(0),
	elapsedTime_(0),
	avgDifftime_(0),
	frames_(0),
	difftime_(0.0),
	direct_(true)
{
  lastmessage_[0] = '\0';
  MxAlertArgs args = { "Alert", lastmessage_,
			 {"Ok", 0, MxFalse},
			 {NULL, 0, MxFalse},
			 {NULL, 0, MxFalse} };
  msgOk = args;

  static MxButton button;
  /* Create some drivers specific to the system */
  static MxDriverSystem system = MxDriverSystemDefault;
  static MxDriverOutput output = MxDriverOutputDefault;
  static MxDriverInput input = MxDriverInputDefault;

  static MxDesktopArgs desktopargs;
  MxArgsInit(&desktopargs);

  desktopargs.desktop_w = screenWidth;
  desktopargs.desktop_h = screenHeight;
  desktopargs.desktop_c = 8;
  desktopargs.system = &system;
  desktopargs.output = &output;
  desktopargs.input = &input;
  desktopargs.window.caption = "";

  /* Initialize the library */
  MxDesktopConstruct(&desktop_.base.mx_desktop, 0, 0, 0, 0, &desktopargs);
  if (!desktop_.base.mx_desktop.ok)
	  throw std::runtime_error("desktop construction failed.");

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

  /* Tell the desktop to use our handler */
  desktop_.base.object.handler = DesktopHandler;

  // store this pointer for static handler
  desktop_.sc_desktop = this;

  // create image for scene
  char *memory[4] = {(char *)scene_.getFrameBuffer(),0,0,0};
  ctx_ = (MxImage*)GrCreateContext(screenWidth,screenHeight,memory,NULL);

  // clear palette
  memset(palette_, 0, sizeof palette_);
  return;	
}
	
// ------------------------------------------------------------
// Destruktor
//
Desktop::~Desktop ()
{
	MxDestroy(&desktop_.base.object);
	GrDestroyContext((struct _GR_context*)ctx_);
}

// ------------------------------------------------------------
// Szene neu laden
//
void Desktop::loadScene(const std::string &filename) {
  try {
    scene_.loadXML(filename);
    cam_ = scene_.getCurrCamera();
	reloadPalette();
	Scene::ActionMap *am = scene_.getAllActions();
	scene::Command *hudRefreshCmd = new scene::HudRefreshCmd(hud_, (_GR_context*)getCtx());
	string id = "HudRefreshCmd";	
	am->insert(make_pair(id, hudRefreshCmd));

    strcpy(lastmessage_, (std::string(filename) + " loaded.").c_str());
	if (hud_) hud_->setStatus(lastmessage_);
  } catch (Scene::IOError &) {
	std::ostringstream msg;
    msg << filename << ": file not found"; 
    strcpy(lastmessage_, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop_.base.object);
    return;
  } catch (Scene::ParseError &pe) {
    std::ostringstream msg;
    msg << filename << ':' << pe.getLine() << ": error: " << pe.what(); 
    strcpy(lastmessage_, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop_.base.object);
    return;
  }
}

// ------------------------------------------------------------
// Palette neu laden
//
void Desktop::reloadPalette() 
{
  int i;
  // Fixed colors
  scene_.makePalette(palette_, CFixColors, 255);
  for (i = CFixColors; i < 256; i++) {
    GrSetColor(i, palette_[ i*3 ], palette_[ i*3 + 1], palette_[ i*3 + 2 ]);
  }
}

// ------------------------------------------------------------
// Scene rendern und ausgeben
//
void Desktop::display() {
  clock_t currtime = clock();
  assert(prevtime_ <= currtime);
  difftime_ = (float)(currtime - prevtime_)*1000.0 / (float) CLOCKS_PER_SEC;
  assert((long)difftime_ >= 0);
  elapsedTime_ += difftime_;

  prevtime_ = currtime;


	if (hud_) {
		if (elapsedTime_ > 0 && frames_ >= avg_frame_window) {
			hud_->setFPS((float)frames_*1000.0 / (float)elapsedTime_);
			avgDifftime_ = (float)elapsedTime_ / (float)frames_;
			elapsedTime_ = frames_ = 0;
		}
		if (cam_) {
			hud_->setPosition(cam_->X, cam_->Y, cam_->Z, cam_->Pitch, cam_->Pan, cam_->Roll);
		} else {
			hud_->setPosition(0,0,0,0,0,0);
		}
	}
	if (cam_) {
		scene_.render();
		frames_++;
		scene_.execute(avgDifftime_);
	}

	if (direct_) { 
		  MxBlitToScreenFast(ctx_, NULL, 
					 0, 0, 
					 desktop_.base.object.position.x1, 
					 desktop_.base.object.position.y1,
					 desktop_.base.object.position.x2 - desktop_.base.object.position.x1, 
					 desktop_.base.object.position.y2 - desktop_.base.object.position.y1);
		
	} else {
		MxRefresh(&getDesktop()->base.object);
	}
}

void Desktop::mouse_reset() 
{
  MxImage *ctx = desktop_.sc_desktop->getCtx();
  int screen_w = ((GrContext2 *)ctx)->gc_xmax - 1;
  int screen_h = ((GrContext2 *)ctx)->gc_ymax - 1;

  GrMouseEvent evt;
  GrMouseWarp(screen_w / 2, screen_h / 2);
  do {
    GrMouseGetEventT(GR_M_EVENT | GR_M_NOPAINT, &evt,0L);
  } while (evt.flags != 0);
  old_mouse_x_ = evt.x;
  old_mouse_y_ = evt.y;
}

void Desktop::mouse_get(const MxEvent *event, int &mouse_x, int &mouse_y) 
{
  static signed short int mx = 0 , my = 0;

  mouse_x = ((old_mouse_x_ - event->point.x) + mx) * 6 / 10;
  mouse_y = ((old_mouse_y_ - event->point.y) + my) * 6 / 10;
  mx = mouse_x;
  my = mouse_y;
  old_mouse_x_ = event->point.x;
  old_mouse_y_ = event->point.y;
}

} // scene
