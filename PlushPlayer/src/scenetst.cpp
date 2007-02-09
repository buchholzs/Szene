// Copyright (c) 2002 Steffen Buchholz

#pragma warning (disable : 4786)
#include "grx20.h"
#include "grxkeys.h"

#include <assert.h>
#include <time.h>
#include <typeinfo>
#include <iostream>
#include <stdexcept>

#include "Scene.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constants
//
#ifdef _MSC_VER
const int screen_w = 320;
const int screen_h = 200;
#else
const int screen_w = 640;
const int screen_h = 480;
#endif
const int BPP = 8;
const char *WINTITLE = "GRX Scene";

const float velocity = 20.0; // m/s
const int reset_area = 20;
const int CText = 1;

//////////////////////////////////////////////////////////////////////////////
// Static variables
//
float mouse_sens = 2.5 * 2048.0/32768.0;
static pl_uChar ThePalette[768];
static signed short int old_mouse_x, old_mouse_y;

void mouse_reset() 
{
  GrMouseEvent evt;
  GrMouseWarp(screen_w / 2, screen_h / 2);
  do {
    GrMouseGetEventT(GR_M_EVENT | GR_M_NOPAINT, &evt,0L);
  } while (evt.flags != 0);
  old_mouse_x = evt.x;
  old_mouse_y = evt.y;
}
void mouse_get(GrMouseEvent evt, int &mouse_x, int &mouse_y) 
{
  static signed short int mx = 0 , my = 0;

  mouse_x = ((old_mouse_x - evt.x) + mx) * 6 / 10;
  mouse_y = ((old_mouse_y - evt.y) + my) * 6 / 10;
  mx = mouse_x;
  my = mouse_y;
  old_mouse_x = evt.x;
  old_mouse_y = evt.y;
}
void renderScene(string file) {
  pl_sChar lastmessage[80] = "";
  GrMouseEvent evt;
  int mouse_x, mouse_y;
  int width=screen_w, height=screen_h, bpp=BPP;

  GrSetMode( GR_width_height_bpp_graphics,width,height,bpp );
  GrSetWindowTitle( (char *)WINTITLE );
  GrMouseInit();

  cout << "Rendering" << endl;
  scene::Scene scene(screen_w, screen_h);

  char *memory[4] = {(char *)scene.getFrameBuffer(),0,0,0};
  GrContext *ctx =
    GrCreateContext(screen_w,screen_h,memory,NULL);


  pl_Cam *cam = NULL;
  bool doInit = true;

  float prevtime = clock() / (float) CLOCKS_PER_SEC; 
  float currtime = prevtime , difftime, avgfps, elapsedtime = 0.0; 
  int frames = 0;
  mouse_reset();
  while( 1 ) {
	frames ++;
    currtime = (clock() / (float) CLOCKS_PER_SEC);
    difftime = currtime - prevtime;
    prevtime = currtime;
	elapsedtime += difftime;
	if (frames == 20) {
		avgfps = frames / elapsedtime;
		elapsedtime = frames = 0;
	}
	
    
    if (doInit) {
      doInit = false;
      scene.loadXML(file);
      cam = scene.getCurrCamera();
      cout << "Make palette" << endl;
      scene.makePalette(ThePalette, 2, 255);
      for (int i = 2; i < 256; i++) {
	GrSetColor(i, ThePalette[ i*3 ], 
		   ThePalette[ i*3 + 1], 
		   ThePalette[ i*3 + 2 ]);
      }
      GrSetColor(CText, 0, 192, 0);
    }
    assert(cam != NULL);

    GrMouseGetEventT(GR_M_EVENT/* | GR_M_NOPAINT*/,&evt, 0L);
    if (evt.flags & GR_M_KEYPRESS) {
      switch (evt.key) {
      case GrKey_Escape:
	return;
      case GrKey_l:	// Reload
	doInit = true;
	break;
      case GrKey_LParen: mouse_sens /= 1.1f; 
	sprintf((char *)lastmessage,"MouseSens: %.3f",mouse_sens);
	break;
        // ] increases mouse sensitivity
      case GrKey_RParen: mouse_sens *= 1.1f; 
	sprintf((char *)lastmessage,"MouseSens: %.3f",mouse_sens);
	break;
      }
    }
    mouse_x = mouse_y = 0;
    //	if (evt.flags & GR_M_MOTION) {
    mouse_get(evt, mouse_x, mouse_y);
    
    if (evt.buttons & GR_M_MIDDLE) { // if middle button hit, we roll
        cam->Roll += (mouse_x*mouse_sens);
    } else {
        cam->Pan += (mouse_x*mouse_sens);
    }
    cam->Pitch += (mouse_y*mouse_sens); // update pitch and pan of ship

		
    float v = 0.0;
    if (evt.buttons & GR_M_LEFT) { // if left button hit, we go forward quickly
      v = 2 * velocity;
    } else if (evt.buttons & GR_M_RIGHT) { // if right button hit, we go backward slowly
      v = - 2 * velocity;
    }
    if (v != 0.0) {
      cam->X -=
	difftime*v*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
	difftime*v*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Y += 
	difftime*v*sin(cam->Pitch*PL_PI/180.0);
    }
    if (!((evt.x >= reset_area && evt.x <= screen_w - reset_area) &&
	  (evt.y >= reset_area && evt.y <= screen_h - reset_area)))
      mouse_reset();
    //	}
	
    scene.render();
    plTextPrintf(cam,cam->ClipLeft+5,cam->ClipBottom-12,0.0,CText,
		 ( pl_sChar *)"Pitch=%.2f Pan=%.2f Roll=%.2f MX=%d MY=%d",
		 cam->Pitch,cam->Pan, cam->Roll, mouse_x, mouse_y);
    plTextPrintf(cam,cam->ClipLeft+5,cam->ClipBottom-24, 0.0,CText,
		 ( pl_sChar *)"X=%.2f Y=%.2f Z=%.2f FPS=%3.1f", 
		 cam->X, cam->Y, cam->Z, avgfps);
    plTextPrintf(cam,cam->ClipLeft+5,cam->ClipBottom-36, 0.0,CText,
		 lastmessage);
    GrBitBlt(NULL, 0, 0,ctx,
	     0, 0, screen_w - 1, screen_h - 1, GrWRITE);
  }
  GrSetMode( GR_default_text );
}

extern "C" int
GRXMain(int argc, char **argv)
{
  try 
    {
      if (argc != 2) {
	cerr << "Usage: " << argv[0] << " <scene.xml>" << endl;
	return 1;
      }
      // Parse only
      cout << "Parsing only" << endl;
      scene::Scene scene1;
      scene1.loadXML(argv[1]);
      scene1.dump( cout );
      cout << "Parsing ok" << endl;

      // Rendering
      cout << "Start rendering" << endl;
      renderScene(argv[1]);
      cout << "Rendering ok" << endl;
    }
  catch (exception &e) 
    {
      cerr << "Exception: " << e.what( ) << endl;
      cerr << "Typ: " << typeid(e).name( ) << endl;
    };
  return 0;
}
