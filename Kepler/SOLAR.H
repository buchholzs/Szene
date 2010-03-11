#ifndef _SOLAR_H
#define _SOLAR_H
///////////////////////////////////////////////////////////////////////////////
//
// MODULE: solar.h
// DESCRIPTION: Klasse Solar
// HISTORY: $Log: solar.h,v $
// HISTORY: Revision 1.4  1998/04/11 22:51:43  buchholz
// HISTORY: Bewegung der Kamera, Zielverfolgung
// HISTORY:
//
///////////////////////////////////////////////////////////////////////////////

// Systemincludes
#include <list>
#include <aedef.h>
#include <task.h>
#include <plush.h>
#include <grx20.h>

// Projektincludes
#include "target.h"

class Solar: public Task {
public:
  static const int cBlackColor = 0;
  static const int cTextColor  = cBlackColor + 1;
  static const int cFirstFreeColor  = cTextColor + 1;
  Solar(
		  	int updatePalette,	// j: Palette neu berechnen und in Datei schreiben
		  								// n: Palette aus Datei lesen
			int useTextures  		// j: Texturen benutzen
		  );
  Solar::~Solar();

  void    TaskMain();
private:

	////////////////////////////////////////////////////////////////////////////
	//
	//	Normiert einen Winkel in den Bereich 0..2 PI
	//
  	void normAngleRad(
						pl_Float	&angle	// [io] nicht normierter Winkel
						);
	////////////////////////////////////////////////////////////////////////////
	//
	//	Normiert einen Winkel in den Bereich 0..360
	//
  	void normAngleDeg(
						pl_Float	&angle	// [io] nicht normierter Winkel
						);
  pl_Light *TheLight;   // Our light
  pl_Light *TheSunLight;   // 2. Licht
  pl_Obj *TheSun;      // Our cube object
  pl_Obj *TheEarth;      // Our cube object
  pl_Obj *TheMoon;      // Our cube object
  pl_Mat *Material[4]; // Used for creating palette
  pl_Cam *TheCamera; // Our camera
  unsigned char *TheFrameBuffer; // Our framebuffer to render to
  unsigned char ThePalette[768];
  GrContext screen;
  list<pl_Obj *>	TheObjects;	// Objekte zum Rendern
  list<Target>	TheTargets;		// Ziele
  list<Target>::iterator	currTarget_;	// ausgewähltes Ziel
};

//---Inline------------------------------------------------------------------
inline void Solar::normAngleRad(pl_Float &angle)
{
  if (angle > (2.0*PL_PI))
	angle -= 2.0*PL_PI;
  else if (angle < -(2.0*PL_PI))
	angle	+= 2.0*PL_PI;
}

inline void Solar::normAngleDeg(pl_Float &angle)
{
  if (angle > 360)
	angle -= 360;
  else if (angle < -360)
	angle	+= 360;
}

#endif
