///////////////////////////////////////////////////////////////////////////////
//
// MODULE: kepler_main.cc
// DESCRIPTION: Main-Modul
// HISTORY:
//		$Log: kepler_main.cc,v $
//		Revision 1.3  1998/04/11 22:51:43  buchholz
//		Bewegung der Kamera, Zielverfolgung
//
///////////////////////////////////////////////////////////////////////////////

// Systemincludes
#include <strstream.h>
#include <iomanip.h>
#ifndef DJGPP
#include <getopt.h>
#else
#include <float.h>
#include <unistd.h>
#endif

// Projektincludes
#include <grx20.h>
#include <assert.h>

// Local Includes
#include "solar.h"

void SetTextMode(void)
{
  GrSetMode(GR_default_text);
}

int main(int argc, char **argv)
{
int resolution = 1;			// niedrige Aufl”sung
int updatePalette = 0;    // Palette aktualisieren
int useTextures = 1;				// Texturen verwenden

int c;
  while ((c = getopt(argc, argv, "huts:")) != -1) {
    switch (c) {
    case 's':
      resolution = *optarg - '0';
      break;
    case 'u':
      updatePalette = !updatePalette;
      break;
    case 't':
      useTextures = !useTextures;
      break;
    case 'h':
    case '?':
      cout << "Aufruf: " << argv[0] << " [-hu [-s[12]]" << endl
	   << "wobei" << endl
	   << "\t-s[12]\tAufl”sung niedrig/hoch" << endl
	   << "\t-t\tKeine Texturen benutzen" << endl
	   << "\t-u\tAktualisieren der Palette" << endl
	   << "\t-h\tDiese Hilfe" << endl;
	exit(0);
      break;
    }
  }
  atexit(SetTextMode);

#if defined(DJGPP) || defined(__WATCOMC__)
   // Put the fpu in a low precision, no exception state
  _control87(MCW_EM|PC_24,MCW_EM|MCW_PC); 
#endif
  if (resolution==1) {
    GrSetMode(GR_320_200_graphics);
  } else {
    GrSetMode(GR_width_height_graphics, 640, 480);
  }
  GrMouseEventMode(1);
  GrMouseInit();
  GrMouseSetColors(Solar::cTextColor, Solar::cBlackColor);
  GrMouseDisplayCursor();

  Solar solar(updatePalette, useTextures);

  scheduler();			// Multitasking ein
  GrSetMode( GR_default_text );
  return 0;
}
