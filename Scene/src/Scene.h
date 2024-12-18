// Copyright (c) 2002 Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _Scene_H_
#define _Scene_H_

#pragma warning (disable : 4786)
#include <stdexcept>
#include <string>
#include <map>
#include <PLUSH.H>
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#include <grxkeys.h>
#undef GrContext 
#undef GrFont 
#include "sc_tokens.h"

/* itoa:  convert n to characters in s */
void itoa(int n, char s[]);

/*
** Konstanten
*/
const pl_Float ASPECT_RATIO = 1.0;
const pl_Float FOV = 90.0;

// Forward decl
struct sc_TokenPair;

namespace scene {
class Command;
class Mover;
class Rotator;
class Sequence;
class Hud;

class Scene {
 public:
  const static int nCols = 256;
  const static int nEgaCols = 16;

  typedef std::map<std::string, pl_Cam*> CamMap;
  typedef std::map<std::string, pl_Light*> LightMap;
  typedef std::map<std::string, pl_Obj*> ObjMap;
  typedef std::map<std::string, pl_Mat*> MatMap;
  typedef std::map<std::string, pl_Texture*> TextureMap;
  typedef std::map<std::string, Command*> ActionMap;

  class ParseError : public std::logic_error {
  public:
    ParseError(const std::string& message, int line) 
      : logic_error(message), line_(line) {} 
    
    int getLine() { return line_; }
  private:
    int line_;
  };

  class IOError : public std::runtime_error {
  public:
    IOError(const std::string& message) : runtime_error(message) {} 
  };


  Scene () 
  {
    init(0, 0, ASPECT_RATIO);
  }
  Scene(pl_uInt screenWidth, pl_uInt screenHeight,
        pl_Float aspectRatio = ASPECT_RATIO)
  {
    init(screenWidth, screenHeight, aspectRatio);
  }
  virtual ~Scene ();
  
  	// Setzt die Hintergrundfarbe
	void setBackground(const pl_uChar col) {
		background_=col;
	}

    // Setzt die Bewegungsgeschwindigkeit
    void setMoveSpeed(const float speed) {
        moveSpeed_ = speed;
    }

    // Liefert die Bewegungsgeschwindigkeit
    float getMoveSpeed() {
        return moveSpeed_;
    }

    // Setzt die Drehgeschwindigkeit
    void setTurnSpeed(const float speed) {
        turnSpeed_ = speed;
    }

    // Liefert die Drehgeschwindigkeit
    float getTurnSpeed() {
        return turnSpeed_;
    }

    // Setzt die z.Zt. selektierte Kamera
  void	setCurrCamera (pl_Cam *cam);

  // Liefert die aktive Kamera
  pl_Cam*	getCurrCamera ();

  // Setzt den z.Zt. selektierten Mover
  void setCurrMover(Mover* mover);

  // Liefert den aktiven Mover
  Mover*    getCurrMover();

  // Setzt den z.Zt. selektierten Rotator
  void setCurrRotator(Rotator* rotator);

  // Liefert den aktiven Rotator
  Rotator* getCurrRotator();

  // Setzt die z.Zt. selektierten Sequence
  void setCurrSequence(Sequence* Sequence);

  // Liefert die aktiven Sequence
  Sequence* getCurrSequence();

  // Liefert den Framebuffer
  pl_uChar*	getFrameBuffer () { return frameBuffer_; }

  // L�dt eine Szenebeschreibung im XML-Format
  void	loadXML (const std::string &fileName);

  // L�scht die geladene Szene
  void clear ();

  // Liefert eine Kamera aus der Szenebeschreibung
  pl_Cam*	findCamera (const std::string &name);

  // Liefert alle Kameras aus der Szenebeschreibung
  Scene::CamMap *getAllCameras () { return &cameras_; }

  // Liefert ein Licht aus der Szenebeschreibung
  pl_Light*	findLight (const std::string &name);

  // Liefert alle Lichter aus der Szenebeschreibung
  Scene::LightMap *getAllLights () { return &lights_; };

  // Liefert ein Material aus der Szenebeschreibung
  pl_Mat*	findMaterial (const std::string &name);

  // Liefert alle Materialen aus der Szenebeschreibung
  Scene::MatMap *getAllMaterials () { return &materials_; }

  // Liefert ein Objekt aus der Szenebeschreibung
  pl_Obj*	findObject (const std::string &name);

  // Liefert alle Objekte aus der Szenebeschreibung
  Scene::ObjMap *getAllObjects() { return &objects_; }

  // Liefert eine Textur aus der Szenebeschreibung
  pl_Texture*	findTexture (const std::string &name);

  //Liefert alle Texturen aus der Szenebeschreibung
  Scene::TextureMap *getAllTextures() { return &textures_; }

  // Liefert eine Aktion aus der Szenebeschreibung
  Command*	findAction (const std::string &name);

  //Liefert alle Aktionen aus der Szenebeschreibung
  Scene::ActionMap *getAllActions() { return &actions_; }

  // Rendert eine Szene mit der ausgew�hlten Kamera 
  void	render ();

  // F�hrt die Aktionen der Szene aus
  void	execute (float timeDiff);

  // Gibt eine Beschreibung der Szene im Debug Log aus
  void	dump ();

  // Erzeugt eine Camera anhand der Attributliste
  void createCamera(const char **attr);

  // Erzeugt ein Light anhand der Attributliste
  void createLight(const char **attr);

  // Erzeugt eine Textur anhand der Attributliste
  void createTexture(const char **attr);

  // Erzeugt ein Material anhand der Attributliste
  void createMaterial(const char **attr);

  // Erzeugt ein Object anhand der Attributliste
  void createObject(enum sc_Tokens tok, const char **attr);

  // Erzeugt ein Object aus einer Datei anhand der Attributliste
  void createObjectFromFile(enum sc_Tokens tok, const char **attr);

  // Erzeugt eine Transformation anhand der Attributliste
  void createTransformation(enum sc_Tokens tok, const char **attr);

  // Erzeugt eine Mover-Animation anhand der Attributliste
  void createMover(enum sc_Tokens tok, const char** attr);
  
  // Erzeugt eine Rotator-Animation anhand der Attributliste
  void createRotator(enum sc_Tokens tok, const char** attr);

  // Erzeugt eine Sequence-Animation anhand der Attributliste
  void createSequence(enum sc_Tokens tok, const char** attr);

  // Erzeugt eine Pause-Animation anhand der Attributliste
  void createPause(enum sc_Tokens tok, const char** attr);

  // Erzeugt eine SetMat-Animation anhand der Attributliste
  void createSetMat(enum sc_Tokens tok, const char** attr);

  // Mover point setzen anhand der Attributliste
  void setPoint(const char** attr);

  // Rotator angle setzen anhand der Attributliste
  void setAngle(const char** attr);

  // Setzt die Hintergrundfarbe
  void setBackground(const char **attr);

  // Setzt die Bewegungsgeschwindigkeit
  void setMoveSpeed(const char** attr);

      // Skalierung anhand der Attributliste
  void doScale(enum sc_Tokens tok, const char **attr);

  // Camera target setzen anhand der Attributliste
  void setTarget(const char **attr);

  /*
  ** Berechnet eine Palette aus den vorhandenen Materialien 
  ** und mappt diese anschlie�end auf die Palette
  ** 
  ** Parameter:
  **	pal : Palette, ein 768 byte-Array von unsigned chars,
  **		  3 bilden zusammen ein RGB-Tripel
  **  pstart : Startoffset, normal 0
  **  pend : Endoffset, normal 255
  */
  void makePalette(pl_sInt pstart, pl_sInt pend);

  void reloadPalette();

  // pausiert die Animationen bei false
  void	setPause(bool pause) { pause_ = pause;  }

  // liefert den Pause-Status
  bool	getPaletteMode() { return paletteMode_; }

  // pausiert die Animationen bei false
  void	setPaletteMode(bool paletteMode) { paletteMode_ = paletteMode;  }

  // liefert den Pause-Status
  bool	getPause() { return pause_; }

  int LoadContextFromFramebuffer( _GR_context * ctx );

  void setEgaColors(GrColor *egaColors);

 protected:
  Scene (const Scene& rhs);
  Scene& operator = (const Scene &arg);

 private:
  // Initialisiert wichtige Attribute
  void init(pl_uInt screenWidth, pl_uInt screenHeight, pl_Float aspectRatio);

  std::string fileName_;
  CamMap cameras_;
  LightMap lights_;
  ObjMap objects_;
  MatMap materials_;
  TextureMap textures_;
  ActionMap actions_;
  pl_Cam *currCam_;
  Mover* currMover_;
  Rotator* currRotator_;
  Sequence* currSequence_;

  pl_uInt screenWidth_;	// Screen width
  pl_uInt screenHeight_;	// Screen height
  pl_ZBuffer *zBuffer_; // Z Buffer
  pl_uChar *frameBuffer_; // Frame buffer (screenWidth_ * screenHeight_)
  pl_uChar ThePalette_[nCols*3];
	GrColor TheGrxPalette_[nCols];

  pl_Float aspectRatio_;	// Aspect ratio (normalerweise 1.0)
  pl_uChar background_;	// Hintergrundfarbe
  float moveSpeed_; // Bewegungsgeschwindigkeit
  float turnSpeed_; // Drehgeschwindigkeit

  bool pause_; // Pause
  bool colorsAllocated_; // Palettenfarben allokiert
  bool paletteMode_; // Palette or TrueColor?
	GrColor firstFreeColor_;
	GrColor lastFreeColor_;
};

} // scene
#endif
