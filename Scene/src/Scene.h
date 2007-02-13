// Copyright (c) 2002 Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _Scene_H_
#define _Scene_H_

#pragma warning (disable : 4786)
#include <stdexcept>
#include <string>
#include <map>
#include <plush.h>
#include "sc_tokens.h"

/*
** Konstanten
*/
const pl_Float ASPECT_RATIO = 1.0;
const pl_Float FOV = 90.0;

// Forward decl
struct sc_TokenPair;

namespace scene {
class Command;

class Scene {
 public:
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

  // Liefert die z.Zt. selektierte Kamera
  void	setCurrCamera (pl_Cam *cam);

  // Liefert die aktive Kamera
  pl_Cam*	getCurrCamera ();

  // Liefert den Framebuffer
  pl_uChar*	getFrameBuffer () { return frameBuffer_; }

  // Lädt eine Szenebeschreibung im XML-Format
  void	loadXML (const std::string &fileName) 
     throw (ParseError, IOError);

  // Löscht die geladene Szene
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

  // Rendert eine Szene mit der ausgewählten Kamera 
  void	render ();

  // Führt die Aktionen der Szene aus
  void	execute (float timeDiff);

  // Gibt eine Beschreibung der Szene auf den Stream aus
  void	dump (const std::ostream &str);

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

	// Setzt die Hintergrundfarbe
	void setBackground(const char **attr);

	// Skalierung anhand der Attributliste
	void doScale(enum sc_Tokens tok, const char **attr);

	// Camera target setzen anhand der Attributliste
	void setTarget(const char **attr);

  /*
  ** Berechnet eine Palette aus den vorhandenen Materialien 
  ** und mappt diese anschließend auf die Palette
  ** 
  ** Parameter:
  **	pal : Palette, ein 768 byte-Array von unsigned chars,
  **		  3 bilden zusammen ein RGB-Tripel
  **  pstart : Startoffset, normal 0
  **  pend : Endoffset, normal 255
  */
  void makePalette(pl_uChar *pal, pl_sInt pstart, pl_sInt pend);


 protected:
  Scene (const Scene& rhs);
  Scene& operator = (const Scene &arg);

 private:
  // Initialisiert wichtige Attribute
  void init(pl_uInt screenWidth, pl_uInt screenHeight, pl_Float aspectRatio_);

  CamMap cameras_;
  LightMap lights_;
  ObjMap objects_;
  MatMap materials_;
  TextureMap textures_;
  ActionMap actions_;
  pl_Cam *currCam_;

  pl_uInt screenWidth_;	// Screen width
  pl_uInt screenHeight_;	// Screen height
  pl_ZBuffer *zBuffer_; // Z Buffer
  pl_uChar *frameBuffer_; // Frame buffer (screenWidth_ * screenHeight_)
  pl_Float aspectRatio_;	// Aspect ratio (normalerweise 1.0)
  pl_uChar background_;	// Hintergrundfarbe
};

} // scene
#endif
