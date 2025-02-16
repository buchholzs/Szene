// Copyright (c) 2002 Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#include <assert.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <future>
#include <thread>
#include <expat.h>
#include <grx20.h>
#include "Command.h"
#include "Mover.h"
#include "Rotator.h"
#include "Sequence.h"
#include "Pause.h"
#include "SetMat.h"
#include "scenedbg.h"
#include "Scene.h"

using namespace scene;

const float moveVelocity = 200.0f / 1000.0f;	// m/s
const float turnVelocity = 200.0f / 1000.0f;	// m/s

/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

using namespace std;

namespace scene {

/*
** Ressourcemonitor, führt Cleanup beim Verlassen der Methode "loadXML" durch
*/
class RessourceTracker {
  FILE *stream_;
  XML_Parser parser_;
public:
  RessourceTracker() : stream_(0), parser_(0) {}
  ~RessourceTracker() { 
    if (stream_) fclose(stream_);
    if (parser_) XML_ParserFree(parser_);
  }
  void setStream(FILE *stream) { stream_=stream; }
  void setParser(XML_Parser parser) { parser_=parser; }
};

/*
** Hilfsfunktion für for_each(). Wendet eine im Konstruktor übergebene
** Funktion auf den Value-Teil einer Map an.
*/
template <typename map_value_type, typename Fun >
class applyMap
{
 public:

  Fun f_;
  applyMap(Fun f){f_=f;}
  void operator() 
    (map_value_type a ) {
	  f_(a.second);
  }
};

/**
** Wandelt die Strings "yes" und "no" in ihre bool-Äquivalente
** 
** Parameter:
**		val : String mit "yes" oder "no"
** Returns:
**		true oder false
*/
static bool
toYesNo(const string &val) 
{
	sc_TokenPair *yes = sc_search(val.c_str());
	if (yes == NULL || !(yes->val == TOK_yes || yes->val == TOK_no)) {
	  throw domain_error(string("Unerwartetes Token: ") + val);
	}
	return yes->val == TOK_yes;
}

/**
** element opened
*/
static void
startElement(void *userData, const char *name, const char **atts)
{
  Scene *scene = static_cast<Scene *>(userData);

  sc_TokenPair *res = sc_search(name);
  if (res) {
	  switch (res->val) {
	  case TOK_background:
		  scene->setBackground(atts);
		  break;
	  case TOK_moveSpeed:
		  scene->setMoveSpeed(atts);
		  break;
	  case TOK_camera:
		  scene->createCamera(atts);
		  break;
	  case TOK_target:
		  scene->setTarget(atts);
		  break;
	  case TOK_light:
		  scene->createLight(atts);
		  break;
	  case TOK_texture:
		  scene->createTexture(atts);
		  break;
	  case TOK_material:
		  scene->createMaterial(atts);
		  break;
	  case TOK_plane: case TOK_box: case TOK_sphere:
	  case TOK_cone: case TOK_cylinder: case TOK_torus:
		  scene->createObject(res->val, atts);
		  break;
	  case TOK_o3ds: case TOK_jaw: case TOK_cob:
		  scene->createObjectFromFile(res->val, atts);
		  break;
	  case TOK_translate: case TOK_rotate:
		  scene->createTransformation(res->val, atts);
		  break;
	  case TOK_scale:
		  scene->doScale(res->val, atts);
		  break;
	  case TOK_point:
		  scene->setPoint(atts);
		  break;
	  case TOK_angle:
		  scene->setAngle(atts);
		  break;
	  case TOK_mover:
		  scene->createMover(res->val, atts);
		  break;
	  case TOK_rotator:
		  scene->createRotator(res->val, atts);
		  break;
	  case TOK_sequence:
		  scene->createSequence(res->val, atts);
		  break;
	  case TOK_pause:
		  scene->createPause(res->val, atts);
		  break;
	  case TOK_setMat:
		  scene->createSetMat(res->val, atts);
		  break;
	  case TOK_scene: case TOK_global: case TOK_cameras: case TOK_textures:
	  case TOK_materials: case TOK_lights: case TOK_objects: case TOK_transformations: case TOK_animations:
		  break;
	  default:
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }
  } else {
	  throw domain_error(string("Unerwartetes Token: ") + name);
  }
}

/**
** element closed
*/
static void
endElement(void *userData, const char *name)
{
  Scene *scene = static_cast<Scene *>(userData);
}
// PRESERVE:END

// ------------------------------------------------------------
Scene::~Scene ()
{
	// PRESERVE:BEGIN
	clear();
	delete [] frameBuffer_;
	delete [] zBuffer_;
	// PRESERVE:END
}

// ------------------------------------------------------------
// Setzt die z.Zt. selektierte Kamera

void Scene::setCurrCamera (pl_Cam *cam)
{
	// PRESERVE:BEGIN
	currCam_ = cam;
	// PRESERVE:END
}

// ------------------------------------------------------------
// Setzt den z.Zt. selektierten Mover

void Scene::setCurrMover(Mover* mover) {
	currMover_ = mover;
}

// ------------------------------------------------------------
// Setzt den z.Zt. selektierten Rotator

void Scene::setCurrRotator(Rotator* rotator) {
	currRotator_ = rotator;
}

// ------------------------------------------------------------
// Setzt den z.Zt. selektierten Sequence

void Scene::setCurrSequence(Sequence* sequence) {
	currSequence_ = sequence;
}

// ------------------------------------------------------------
// Liefert die aktive Kamera

pl_Cam* Scene::getCurrCamera ()
{
	// PRESERVE:BEGIN
	return currCam_;
	// PRESERVE:END
}

// ------------------------------------------------------------
// Liefert den aktiven Mover

Mover* Scene::getCurrMover()
{
	// PRESERVE:BEGIN
	return currMover_;
	// PRESERVE:END
}

// ------------------------------------------------------------
// Liefert den aktiven Rotator

Rotator* Scene::getCurrRotator()
{
	// PRESERVE:BEGIN
	return currRotator_;
	// PRESERVE:END
}

// ------------------------------------------------------------
// Liefert die aktiven Sequence

Sequence* Scene::getCurrSequence()
{
	// PRESERVE:BEGIN
	return currSequence_;
	// PRESERVE:END
}

// ------------------------------------------------------------
// Lädt eine Szenebeschreibung im XML-Format

#pragma warning(disable:4996)
void Scene::loadXML (const string &fileName)
{
	// PRESERVE:BEGIN
	fileName_ = fileName;
	FILE *stream = NULL;
	XML_Parser parser = NULL;
	RessourceTracker rt; // do cleanup on method end
	try {
	  if( (stream  = fopen( fileName.c_str(), "r" )) == NULL ) {
	    throw IOError(string("Datei ") + fileName + " konnte nicht geöffnet werden.");
	  }
	  rt.setStream(stream);	// cleanup later
	  clear();

	  char buf[BUFSIZ];
	  parser = XML_ParserCreate(NULL);
	  rt.setParser(parser);	// cleanup later
	  int done;
	  XML_SetUserData(parser, this);
	  XML_SetElementHandler(parser, startElement, endElement);

	  do {
	    size_t len = fread(buf, 1, sizeof(buf), stream);
	    done = len < sizeof(buf);
	    if (!XML_Parse(parser, buf, len, done)) {
	      throw ParseError(XML_ErrorString(XML_GetErrorCode(parser)), 
	       XML_GetCurrentLineNumber(parser));
	    }
	  } while (!done);
	} catch (logic_error &e) {
		throw ParseError(e.what(), XML_GetCurrentLineNumber(parser));
	}
  // PRESERVE:END
}


// ------------------------------------------------------------
// Liefert eine Kamera aus der Szenebeschreibung

pl_Cam* Scene::findCamera (const string &name)
{
	// PRESERVE:BEGIN
	CamMap::iterator it = cameras_.find(name);
	return it == cameras_.end() ? NULL : it->second;
	// PRESERVE:END
}


// ------------------------------------------------------------
// Liefert ein Licht aus der Szenebeschreibung

pl_Light* Scene::findLight (const string &name)
{
	// PRESERVE:BEGIN
	LightMap::iterator it = lights_.find(name);
	return it == lights_.end() ? NULL : it->second;
	// PRESERVE:END
}


// ------------------------------------------------------------
// Liefert ein Material aus der Szenebeschreibung

pl_Mat* Scene::findMaterial (const string &name)
{
	// PRESERVE:BEGIN
	MatMap::iterator it = materials_.find(name);
	return it == materials_.end() ? NULL : it->second;
	// PRESERVE:END
}


// ------------------------------------------------------------
// Liefert ein Objekt aus der Szenebeschreibung

pl_Obj* Scene::findObject (const string &name)
{
	// PRESERVE:BEGIN
	ObjMap::iterator it = objects_.find(name);
	return it == objects_.end() ? NULL : it->second;
	// PRESERVE:END
}

// ------------------------------------------------------------
// Liefert eine Textur aus der Szenebeschreibung

pl_Texture*	Scene::findTexture (const string &name)
{
	// PRESERVE:BEGIN
	return textures_[ name ];
	// PRESERVE:END
}

// ------------------------------------------------------------
// Rendert eine Szene mit der ausgewählten Kamera 

void Scene::render ()
{
	// PRESERVE:BEGIN
	if (zBuffer_) {
		memset(zBuffer_,0,screenWidth_*screenHeight_*sizeof(pl_ZBuffer));
	}
	if (frameBuffer_) {
	    memset(frameBuffer_,background_,screenWidth_*screenHeight_); // clear framebuffer for next frame
	}
	const pl_Cam *cam = getCurrCamera();
	assert(cam != NULL);

    plRenderBegin(const_cast<pl_Cam *>(cam));  // Start rendering with the camera
	for (LightMap::iterator lit = lights_.begin();
		lit != lights_.end(); ++lit) 
		{
			plRenderLight(lit->second);  // Render our lights
		}
	for (ObjMap::iterator oit = objects_.begin();
		oit != objects_.end(); ++oit)
		{
			plRenderObj(oit->second);	// Render our objects
		}
    plRenderEnd(); // Finish rendering
	// PRESERVE:END
}

// ------------------------------------------------------------
// Führt die Aktionen der Szene aus

void Scene::execute (int timeDiff)
{
	if (!pause_) {
		for (ActionMap::iterator action = actions_.begin();
			action != actions_.end(); ++action)
			{
				action->second->Execute(timeDiff);  // Execute actions
			}
	}
}

// ------------------------------------------------------------
// Gibt eine Beschreibung der Szene auf den Stream aus

void Scene::dump ()
{
	// PRESERVE:BEGIN
	string line;
	DBGPRINTF(("Dumping Scene %s", fileName_.c_str()));

	line = "Cameras: ";
	for_each(cameras_.begin(), cameras_.end(), [&line](pair<CamMap::key_type, CamMap::mapped_type> p) { line += p.first +", "; });
	line +="]";
	DBGPRINTF((line.c_str()));

	line = "Lights: [";
	for_each(lights_.begin(), lights_.end(), [&line](pair<LightMap::key_type, LightMap::mapped_type> p) { line += p.first +", "; });
	line +="]";
	DBGPRINTF((line.c_str()));

	line = "Objects: [";
	for_each(objects_.begin(), objects_.end(), [&line](pair<ObjMap::key_type, ObjMap::mapped_type> p) { line += p.first +", "; });
	line +="]";
	DBGPRINTF((line.c_str()));

	line = "Materials: [";
	for_each(materials_.begin(), materials_.end(), [&line](pair<MatMap::key_type, MatMap::mapped_type> p) { line += p.first +", "; });
	line +="]";
	DBGPRINTF((line.c_str()));

	line = "Textures: [";
	for_each(textures_.begin(), textures_.end(), [&line](pair<TextureMap::key_type, TextureMap::mapped_type> p) { line += p.first +", "; });
	line +="]";
	DBGPRINTF((line.c_str()));
// PRESERVE:END
}

bool Scene::CopyFramebuffer(int startY, int endY) {
  GrColor *pColors = new GrColor[ screenWidth_ ];

  for(int y=startY; y<endY; y++ ){
    for(unsigned int x=0; x < screenWidth_; x++ ){
	  pl_uChar c = frameBuffer_[y* screenWidth_ +x];
      pColors[x] = TheGrxPalette_[c];
    }
    GrPutScanline(0, screenWidth_ - 1, y, pColors, GrWRITE);
  }
  delete[] pColors;
  return true;
}	

int Scene::LoadContextFromFramebuffer( _GR_context * ctx )
{
  int y;
  int maxwidth, maxheight;
  int res = 0;

  maxwidth = ctx->gc_xmax + 1;
  maxheight = ctx->gc_ymax + 1;

  std::vector<std::future<bool>> futures;
  const unsigned int minThreads = 1;
  const int minPartition = 1;
  int maxThreads = max(std::thread::hardware_concurrency()*3/4, minThreads); // use 75% of available threads
  int partition = max(maxheight / maxThreads, minPartition);
  GrSetContext(ctx);
  for( y=0; y<maxheight; y+=partition ) {
	futures.push_back(std::async(std::launch::async, [this, y, partition, maxheight]() {
		return this->CopyFramebuffer(y, min(y + partition, maxheight + 1));
	}));
  }
  for (auto &f : futures) {
	if (!f.get()) {
	  res = -1;
	}
  }
  GrSetContext(NULL);

  return res;
}

void Scene::init(pl_uInt screenWidth, pl_uInt screenHeight, pl_Float aspectRatio)
{
	currCam_ = NULL;
	currMover_ = NULL;
	currRotator_ = NULL;
	currSequence_ = NULL;
	screenWidth_ = screenWidth;
	screenHeight_ = screenHeight;
	zBuffer_ = new pl_ZBuffer[screenWidth * screenHeight];
	frameBuffer_ = new pl_uChar[(screenWidth + 100 )* (screenHeight + 100)];
	aspectRatio_ = aspectRatio;
	background_ = 0;	
	moveSpeed_ = moveVelocity;
	turnSpeed_ = turnVelocity;
	pause_ = false;
	colorsAllocated_ = false;
    paletteMode_ = true;
	firstFreeColor_ = GrNOCOLOR;
	lastFreeColor_ = GrNOCOLOR;
	// clear palette
	memset(ThePalette_, 0, sizeof ThePalette_);
}

// delete action
static void ActionDelete(Command *cmd) {
	delete cmd;
}

void Scene::clear ()
{
	// Types for pointer to delete functions
	typedef void (*plCamFun)(pl_Cam*);
	typedef void (*plLightFun)(pl_Light*);
	typedef void (*plObjFun)(pl_Obj*);
	typedef void (*plMatFun)(pl_Mat*);
	typedef void (*plTexFun)(pl_Texture*);
	typedef void (*plActionFun)(Command*);

	currCam_ = NULL;
	currMover_ = NULL;
	currRotator_ = NULL;
	currSequence_ = NULL;
	background_ = 0; // black
	moveSpeed_ = moveVelocity;
	turnSpeed_ = turnVelocity;
	pause_ = false;
	memset(frameBuffer_,0,screenWidth_*screenHeight_);
	applyMap<CamMap::value_type, plCamFun> cm(plCamDelete);
	for_each(cameras_.begin(), cameras_.end(), cm );
	cameras_.clear();
	applyMap<LightMap::value_type, plLightFun> lm(plLightDelete);
	for_each(lights_.begin(), lights_.end(), lm );
	lights_.clear();
	applyMap<ObjMap::value_type, plObjFun> om(plObjDelete);
	for_each(objects_.begin(), objects_.end(), om );
	objects_.clear();
	applyMap<MatMap::value_type, plMatFun> mm(plMatDelete);
	for_each(materials_.begin(), materials_.end(), mm );
	materials_.clear();
	applyMap<TextureMap::value_type, plTexFun> tm(plTexDelete);
	for_each(textures_.begin(), textures_.end(), tm );
	textures_.clear();
	applyMap<ActionMap::value_type, plActionFun> am(ActionDelete);
	for_each(actions_.begin(), actions_.end(), am );
	actions_.clear();
}

void Scene::setBackground(const char **attr)
{
	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i  + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_color:
			  setBackground(std::stoi(val));
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for
}

void Scene::setMoveSpeed(const char** attr)
{
	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
			case TOK_speed:
				setMoveSpeed(std::stof(val));
				break;
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for
}

void Scene::createCamera(const char **attr) 
{	
	pl_Cam *cam = plCamCreate(screenWidth_,
                          screenHeight_,
                          aspectRatio_, // Aspect ratio
                          FOV, // Field of view
                          frameBuffer_, // Framebuffer
                          zBuffer_
                          ); // Create the camera
	string id;

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i  + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_id:
			  id = val;
			  break;
		  case TOK_fov:
			  cam->Fov = std::stof(val);
			  break;
		  case TOK_sort:
			  cam->Sort = std::stoi(val);
			  break;
		  case TOK_x:
			  cam->X = std::stof(val);
			  break;
		  case TOK_y:
			  cam->Y = std::stof(val);
			  break;
		  case TOK_z:
			  cam->Z = std::stof(val);
			  break;
		  case TOK_pitch:
			  cam->Pitch = std::stof(val);
			  break;
		  case TOK_pan:
			  cam->Pan = std::stof(val);
			  break;
		  case TOK_roll:
			  cam->Roll = std::stof(val);
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for
	cameras_.insert(make_pair(id, cam));
	if (cameras_.size() == 1) {
		// Erste Kamera: Defaultkamera
		setCurrCamera( cam );
	}
}

void Scene::setTarget(const char **attr) 
{	
	pl_Float x = 0;
	pl_Float y = 0;
	pl_Float z = 0; 
	pl_Cam *cam = getCurrCamera();
	if (cam == NULL) {
		throw invalid_argument(string("Keine Kamera als Ziel"));
	}

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i  + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_x:
			  x = std::stof(val);
			  break;
		  case TOK_y:
			  y = std::stof(val);
			  break;
		  case TOK_z:
			  z = std::stof(val);
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for
	plCamSetTarget(cam, x, y, z);
}

void Scene::createSetMat(sc_Tokens tok, const char** attr)
{
	bool repeat = true;	// #DEFAULT
	string id;
	string target;
	string material;
	int duration = 0;
	pl_Obj* obj = NULL;
	pl_Mat* mat = NULL;

	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
			case TOK_id:
				id = val;
				break;
			case TOK_target:
				target = val;
				obj = findObject(target);
				if (obj == NULL) {
					throw domain_error(string("Objekt nicht gefunden: ") + target);
				}
				break;
			case TOK_repeat:
				repeat = toYesNo(val);
				break;
			case TOK_duration:
				duration = std::stoi(val);
				break;
			case TOK_material:
			{
				material = val;
				mat = findMaterial(material);
				if (mat == NULL) {
					throw domain_error(string("Material nicht gefunden: ") + target);
				}
				break;
			}
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for

	bool isSequence = getCurrSequence() != NULL;
	SetMat* setMat = new SetMat(obj, mat, duration, isSequence ? false : repeat);
	if (isSequence) {
		getCurrSequence()->addTargetCommand(make_pair(id, setMat));
	}
	else {
		actions_.insert(make_pair(id, setMat));
	}
}

void Scene::setPoint(const char** attr)
{
	pl_Float x = 0;
	pl_Float y = 0;
	pl_Float z = 0;
	Mover* mover = getCurrMover();
	if (mover == NULL) {
		throw invalid_argument(string("Kein Mover gesetzt"));
	}

	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
			case TOK_xp:
				x = std::stof(val);
				break;
			case TOK_yp:
				y = std::stof(val);
				break;
			case TOK_zp:
				z = std::stof(val);
				break;
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for
	mover->addPoint(x, y, z);
}

void Scene::setAngle(const char** attr)
{
	pl_Float x = 0;
	pl_Float y = 0;
	pl_Float z = 0;
	Rotator* rotator = getCurrRotator();
	if (rotator == NULL) {
		throw invalid_argument(string("Kein Rotator gesetzt"));
	}

	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
			case TOK_xa:
				x = std::stof(val);
				break;
			case TOK_ya:
				y = std::stof(val);
				break;
			case TOK_za:
				z = std::stof(val);
				break;
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for
	rotator->addAngle(x, y, z);
}

void Scene::createLight(const char **attr)
{
	// Create the light
	pl_Light *light = plLightCreate();
	pl_uChar mode = PL_LIGHT_NONE;
	pl_Float x = 0;
	pl_Float y = 0;
	pl_Float z = 0; 
	pl_Float intensity = 1.0; 
	pl_Float halfDist = 1.0;
	string id;

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i  + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_id:
			  id = val;
			  break;
		  case TOK_type:
			  {
sc_TokenPair *type = sc_search(val);
if (type == NULL) {
  throw domain_error(string("Unerwartetes Token: ") + val);
}
switch(type->val) {
case TOK_PL_LIGHT_NONE:
	mode = PL_LIGHT_NONE;
	break;
case TOK_PL_LIGHT_VECTOR:
	mode = PL_LIGHT_VECTOR;
	break;
                case TOK_PL_LIGHT_POINT:
	mode = PL_LIGHT_POINT;
	break;
case TOK_PL_LIGHT_POINT_DISTANCE:
	mode = PL_LIGHT_POINT_DISTANCE;
	break;
case TOK_PL_LIGHT_POINT_ANGLE:
	mode = PL_LIGHT_POINT_ANGLE;
	break;
default:
    throw domain_error(string("Unerwartetes Token: ") + name);
}
			  }
			  break;
		  case TOK_xp:
			  x = std::stof(val);
			  break;
		  case TOK_yp:
			  y = std::stof(val);
			  break;
		  case TOK_zp:
			  z = std::stof(val);
			  break;
		  case TOK_intensity:
			  intensity = std::stof(val);
			  break;
		  case TOK_falloff:
			  halfDist = std::stof(val);
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for
	plLightSet(light, mode, x, y, z, intensity, halfDist);

	lights_.insert(make_pair(id, light));
}

void Scene::createTexture(const char **attr)
{
	string src;
	pl_Bool rescale = 1; // #DEFAULT
	pl_Bool optimize = 1; // #DEFAULT
	string id;

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i  + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_id:
			  id = val;
			  break;
		  case TOK_src:
			  src = val;
			  break;
		  case TOK_rescale:
			  rescale = toYesNo(val);
			  break;
		  case TOK_optimize:
			  optimize = toYesNo(val);
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for
	pl_Texture *tex = plReadPCXTex((char *)src.c_str(), rescale, optimize);
	if (tex == NULL) {
		throw invalid_argument(string("Fehler beim Lesen der Textur \"") + src + '\"');
	}
	textures_.insert(make_pair(id, tex));
}

void Scene::createMaterial(const char **attr)
{
	pl_Mat *mat = plMatCreate();
	string id;

	assert(mat->TexEnvMode == PL_TEXENV_ADD); // #IMPLIED

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
			case TOK_id:
			  id = val;
			  break;			
			case TOK_ambient0:
mat->Ambient[0] = std::stoi(val);
break;
			case TOK_ambient1:
mat->Ambient[1] = std::stoi(val);
break;
			case TOK_ambient2:
mat->Ambient[2] = std::stoi(val);
break;
			case TOK_diffuse0:
mat->Diffuse[0] = std::stoi(val);
break;
			case TOK_diffuse1:
mat->Diffuse[1] = std::stoi(val);
break;
			case TOK_diffuse2:
mat->Diffuse[2] = std::stoi(val);
break;
			case TOK_specular0:
mat->Specular[0] = std::stoi(val);
break;
			case TOK_specular1:
mat->Specular[1] = std::stoi(val);
break;
			case TOK_specular2:
mat->Specular[2] = std::stoi(val);
break;
			case TOK_shininess:
mat->Shininess = std::stoi(val);
break;
			case TOK_fadedist:
mat->FadeDist = std::stof(val);
break;
			case TOK_shadetype:
{
	sc_TokenPair *type = sc_search(val);
	if (type == NULL) {
	  throw domain_error(string("Unerwartetes Token: ") + val);
	}
	switch(type->val) {
	case TOK_PL_SHADE_NONE:
		mat->ShadeType = PL_SHADE_NONE;
		break;
	case TOK_PL_SHADE_FLAT:
		mat->ShadeType = PL_SHADE_FLAT;
		break;
	case TOK_PL_SHADE_FLAT_DISTANCE:
		mat->ShadeType = PL_SHADE_FLAT_DISTANCE;
		break;
	case TOK_PL_SHADE_GOURAUD:
		mat->ShadeType = PL_SHADE_GOURAUD;
		break;
	case TOK_PL_SHADE_GOURAUD_DISTANCE:
		mat->ShadeType = PL_SHADE_GOURAUD_DISTANCE;
		break;
	default:
		throw domain_error(string("Unerwartetes Token: ") + name);
	}
}
break;
			case TOK_transparent:
mat->Transparent = std::stoi(val);
break;
			case TOK_perspectivecorrect:
mat->PerspectiveCorrect = std::stoi(val);
break;
			case TOK_texture: case TOK_environment:
{
	pl_Texture *tex = findTexture( val );
	if (tex == NULL) {
		throw domain_error(string("Textur nicht gefunden: ") + val);
	}
	switch(res->val) {
	case TOK_texture:
		mat->Texture = tex;
		break;
	case TOK_environment:
		mat->Environment = tex;
		break;
	}
}
break;
			case TOK_texscaling:
mat->TexScaling = std::stof(val);
break;
			case TOK_envscaling:
mat->EnvScaling = std::stof(val);
break;
			case TOK_texenvmode:
{
	sc_TokenPair *type = sc_search(val);
	if (type == NULL) {
	  throw domain_error(string("Unerwartetes Token: ") + val);
	}
	switch(type->val) {
	case TOK_PL_TEXENV_ADD:
		mat->TexEnvMode = PL_TEXENV_ADD;
		break;
	case TOK_PL_TEXENV_MUL:
		mat->TexEnvMode = PL_TEXENV_MUL;
		break;
	case TOK_PL_TEXENV_AVG:
		mat->TexEnvMode = PL_TEXENV_AVG;
		break;
	case TOK_PL_TEXENV_TEXMINUSENV:
		mat->TexEnvMode = PL_TEXENV_TEXMINUSENV;
		break;
	case TOK_PL_TEXENV_ENVMINUSTEX:
		mat->TexEnvMode = PL_TEXENV_ENVMINUSTEX;
		break;
	case TOK_PL_TEXENV_MIN:
		mat->TexEnvMode = PL_TEXENV_MIN;
		break;
	case TOK_PL_TEXENV_MAX:
		mat->TexEnvMode = PL_TEXENV_MAX;
		break;
    default:
	    throw domain_error(string("Unerwartetes Token: ") + name);
	}
}
break;
			case TOK_numgradients:
mat->NumGradients = std::stoi(val);
break;
			default:
throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for
	plMatInit(mat); // Initialize material
	materials_.insert(make_pair(id, mat));

}

void Scene::createObject(enum sc_Tokens tok, const char **attr)
{
	pl_Mat *material = NULL;
	pl_Float d = 0.0;
	pl_uInt divr = 0;
	pl_uInt divh = 0;
	pl_Float h = 0.0;
	pl_Float r = 0.0;
	pl_uInt resolution = 0;
	pl_Float w = 0.0;
        bool backfacecull = true;
	bool cap = false;
	bool capbottom = false;
	bool captop = false;
        bool flipnormals = false;
	pl_Float r1 = 0.0;
	pl_Float r2 = 0.0;
	string id;

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_id:
			  id = val;
			  break;
		  case TOK_material:
			  {
pl_Mat *mat = findMaterial( val );
if (mat == NULL) {
  throw domain_error(string("Material nicht gefunden: ") + val);
}
material = mat;
			  }
			  break;
          case TOK_backfacecull:
			  backfacecull = toYesNo(val);
                          break;
          case TOK_flipnormals:
			  flipnormals = toYesNo(val);
                          break;                          
		  case TOK_cap:
			  cap = toYesNo(val);
			  break;
		  case TOK_capbottom:
			  capbottom = toYesNo(val);
			  break;
		  case TOK_captop:
			  captop = toYesNo(val);
			  break;
		  case TOK_d:
			  d = std::stof(val);
			  break;
		  case TOK_divr:
			  divr = std::stoi(val);
			  break;
		  case TOK_divh:
			  divh = std::stoi(val);
			  break;
		  case TOK_h:
			  h = std::stof(val);
			  break;
		  case TOK_r:
			  r = std::stof(val);
			  break;
		  case TOK_r1:
			  r1 = std::stof(val);
			  break;
		  case TOK_r2:
			  r2 = std::stof(val);
			  break;
		  case TOK_res:
			  resolution = std::stoi(val);
			  break;
		  case TOK_w:
			  w = std::stof(val);
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for
	pl_Obj *obj = NULL;
	switch(tok) {
	case TOK_plane:
		obj = plMakePlane(w, d, resolution, material);
		break;
	case TOK_box:
		obj = plMakeBox(w, d, h, material);
		break;
	case TOK_sphere:
		obj = plMakeSphere(r, divr, divh, material);
		break;
	case TOK_cone:
		obj = plMakeCone(r, h, divr, cap, material);
		break;
	case TOK_cylinder:
		obj = plMakeCylinder(r, h, divr, captop, capbottom, material);
		break;
	case TOK_torus:
		obj = plMakeTorus(r1, r2, divr, divh, material);
		break;
	default:
		throw domain_error(string("Unerwartetes Token: ") +(char)tok);
	}
	assert(obj != NULL);

        if (!backfacecull) obj->BackfaceCull = 0;
        if (flipnormals) plObjFlipNormals(obj);

	objects_.insert(make_pair(id, obj));
}

void Scene::createObjectFromFile(enum sc_Tokens tok, const char **attr)
{
	pl_Mat *material = NULL;
	string src;
	string id;

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_id:
			  id = val;
			  break;
		  case TOK_material:
			  {
pl_Mat *mat = findMaterial( val );
if (mat == NULL) {
  throw domain_error(string("Material nicht gefunden: ") + val);
}
material = mat;
			  }
			  break;
		  case TOK_src:
			  src = val;
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
		} else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}		
	} // end for
	pl_Obj *obj = NULL;
	switch(tok) {
	case TOK_o3ds:
		obj = plRead3DSObj( (char *)src.c_str(), material);
		break;
	case TOK_cob:
		obj = plReadCOBObj( (char *)src.c_str(), material);
		break;
	case TOK_jaw:
		obj = plReadJAWObj( (char *)src.c_str(), material);
		break;
	default:
		throw domain_error(string("Unerwartetes Token: ") + (char)tok);
	}
	assert(obj != NULL);
	objects_.insert(make_pair(id, obj));
}

void Scene::createTransformation(enum sc_Tokens tok, const char **attr) 
{
	pl_Float Xp = 0.0, Yp = 0.0, Zp = 0.0, Xa = 0.0, Ya = 0.0, Za = 0.0;
	bool relative = false;	// #DEFAULT
	string id;

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_obj:
			  id = val;
			  break;
		  case TOK_relative:
			  relative = toYesNo(val);
			  break;
		  case TOK_xp:
			  Xp = std::stof(val);
			  break;
		  case TOK_yp:
			  Yp = std::stof(val);
			  break;
		  case TOK_zp:
			  Zp = std::stof(val);
			  break;
		  case TOK_xa:
			  Xa = std::stof(val);
			  break;
		  case TOK_ya:
			  Ya = std::stof(val);
			  break;
		  case TOK_za:
			  Za = std::stof(val);
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for

	pl_Obj *obj = findObject( id );
	if (obj == NULL) {
		throw domain_error(string("Objekt nicht gefunden: ") + id);
	}
	switch (tok) {
	case TOK_rotate:
		if (relative) {
			obj->Xa += Xa;
			obj->Ya += Ya;
			obj->Za += Za;
		} else {
			obj->Xa = Xa;
			obj->Ya = Ya;
			obj->Za = Za;
		}
		break;
	case TOK_translate:
		if (relative) {
			obj->Xp += Xp;
			obj->Yp += Yp;
			obj->Zp += Zp;
		} else {
			obj->Xp = Xp;
			obj->Yp = Yp;
			obj->Zp = Zp;
		}
		break;
	default:
		throw domain_error(string("Unerwartetes Token: ") + (char)tok);
	}
}

void Scene::doScale(enum sc_Tokens tok, const char **attr) 
{
	pl_Float X = 0.0, Y = 0.0, Z = 0.0;
	bool relative = false;	// #DEFAULT
	string id;

	for (int i = 0; attr[i]; i += 2) {
		const char *name = attr[ i ];
		const char *val = attr[ i + 1 ];

	    sc_TokenPair *res = sc_search(name);
		if (res) {
		  switch (res->val) {
		  case TOK_obj:
			  id = val;
			  break;
		  case TOK_x:
			  X = std::stof(val);
			  break;
		  case TOK_y:
			  Y = std::stof(val);
			  break;
		  case TOK_z:
			  Z = std::stof(val);
			  break;
		  default:
			  throw domain_error(string("Unerwartetes Token: ") + name);
		  }
	  } else {
		  throw domain_error(string("Unerwartetes Token: ") + name);
	  }		
	} // end for

	pl_Obj *obj = findObject( id );
	if (obj == NULL) {
		throw domain_error(string("Objekt nicht gefunden: ") + id);
	}
	plObjStretch(obj, X, Y, Z);
}

void Scene::createMover(enum sc_Tokens tok, const char** attr)
{
	bool repeat = true;	// #DEFAULT
	string target;
	string type;
	int duration = 0;
	pl_Obj* obj = NULL;
	pl_Cam* cam = NULL;
	pl_Light* light = NULL;

	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
			case TOK_target:
				target = val;
				break;
			case TOK_repeat:
				repeat = toYesNo(val);
				break;
			case TOK_duration:
				duration = std::stoi(val);
				break;
			case TOK_type:
			{
				sc_TokenPair* type = sc_search(val);
				if (type == NULL) {
					throw domain_error(string("Unerwartetes Token: ") + val);
				}
				switch (type->val) {
				case TOK_CAMERA:
					cam = findCamera(target);
					if (cam == NULL) {
						throw domain_error(string("Kamera nicht gefunden: ") + target);
					}
					break;
				case TOK_LIGHT:
					light = findLight(target);
					if (light == NULL) {
						throw domain_error(string("Licht nicht gefunden: ") + target);
					}
					break;
				case TOK_OBJECT:
					obj = findObject(target);
					if (obj == NULL) {
						throw domain_error(string("Objekt nicht gefunden: ") + target);
					}
					break;
				default:
					throw domain_error(string("Unerwartetes Token: ") + name);
				}
				break;
			}
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for

	string id = target + "/Mover";
	bool isSequence = getCurrSequence() != NULL;
	Mover* mover = new Mover(obj, cam, light, duration, isSequence ? false : repeat);
	setCurrMover(mover);
	if (isSequence) {
		getCurrSequence()->addTargetCommand(make_pair(id, mover));
	} else {
		actions_.insert(make_pair(id, mover));
	}
}

void Scene::createRotator(enum sc_Tokens tok, const char** attr)
{
	bool repeat = true;	// #DEFAULT
	string target;
	string relativeToId;
	string type;
	int duration = 0;
	pl_Obj* obj = NULL;
	pl_Cam* cam = NULL;
	pl_Obj* relativeTo = NULL;
	bool isRelativeTo = false;
	float angle = 360; // #DEFAULT

	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
			case TOK_target:
				target = val;
				break;
			case TOK_repeat:
				repeat = toYesNo(val);
				break;
			case TOK_relativeTo:
			{
				string relativeToId = val;
				relativeTo = findObject(relativeToId);
				if (relativeTo == NULL) {
					throw domain_error(string("Objekt nicht gefunden: ") + target);
				}
				isRelativeTo = true;
				break;
			}
			case TOK_angle:
				angle = std::stof(val);
				break;
			case TOK_duration:
				duration = std::stoi(val);
				break;
			case TOK_type:
			{
				sc_TokenPair* type = sc_search(val);
				if (type == NULL) {
					throw domain_error(string("Unerwartetes Token: ") + val);
				}
				switch (type->val) {
				case TOK_CAMERA:
					cam = findCamera(target);
					if (cam == NULL) {
						throw domain_error(string("Kamera nicht gefunden: ") + target);
					}
					break;
				case TOK_OBJECT:
					obj = findObject(target);
					if (obj == NULL) {
						throw domain_error(string("Objekt nicht gefunden: ") + target);
					}
					break;
				default:
					throw domain_error(string("Unerwartetes Token: ") + name);
				}
				break;
			}
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for
	
	Rotator* rotator = NULL;
	string id = target + "/Rotator" + (isRelativeTo ? "/relative" : "");
	bool isSequence = getCurrSequence() != NULL;
	if (isRelativeTo) {
		rotator = new Rotator(obj, cam, relativeTo, angle, duration, isSequence ? false : repeat);
	}
	else {
		rotator = new Rotator(obj, cam, duration, isSequence ? false : repeat);
	}
	setCurrRotator(rotator);
	if (isSequence) {
		getCurrSequence()->addTargetCommand(make_pair(id, rotator));
	} else {
		actions_.insert(make_pair(id, rotator));
	}
}

void Scene::createSequence(enum sc_Tokens tok, const char** attr)
{
	bool repeat = true;	// #DEFAULT
	int duration = 0;
	pl_Obj* obj = NULL;
	string id;
	string target;

	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
		  	case TOK_id:
			  id = val;
			  break;
			case TOK_target:
				target = val;
				obj = findObject(target);
				if (obj == NULL) {
					throw domain_error(string("Objekt nicht gefunden: ") + target);
				}
				break;
				break;
			case TOK_repeat:
				repeat = toYesNo(val);
				break;
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for
	
	Sequence* sequence = new Sequence(obj, repeat);
	setCurrSequence(sequence);
	actions_.insert(make_pair(id, sequence));
}

void Scene::createPause(sc_Tokens tok, const char** attr)
{
	bool repeat = true;	// #DEFAULT
	string id;
	int duration = 0;

	for (int i = 0; attr[i]; i += 2) {
		const char* name = attr[i];
		const char* val = attr[i + 1];

		sc_TokenPair* res = sc_search(name);
		if (res) {
			switch (res->val) {
			case TOK_id:
				id = val;
				break;
			case TOK_duration:
				duration = std::stoi(val);
				break;
			default:
				throw domain_error(string("Unerwartetes Token: ") + name);
			}
		}
		else {
			throw domain_error(string("Unerwartetes Token: ") + name);
		}
	} // end for

	Pause* pause = new Pause(duration);
	bool isSequence = getCurrSequence() != NULL;
	if (isSequence) {
		getCurrSequence()->addTargetCommand(make_pair(id, pause));
	}
	else {
		actions_.insert(make_pair(id, pause));
	}
}

void Scene::makePalette(pl_sInt pstart, pl_sInt pend)
{
	typedef pl_Mat *pl_MatP;

	MatMap::iterator it;
	pl_MatP *AllMaterials = new pl_MatP[ materials_.size() + 1];

	pl_MatP *currMat = AllMaterials;
	for(it = materials_.begin(); 
		it != materials_.end(); ++it, ++currMat) 
	{
		*currMat = it->second;
	}
	*currMat = 0;  // Null terminate list of materials

	// Create a nice palette
	plMatMakeOptPal(ThePalette_,pstart,pend,AllMaterials, materials_.size());
	delete [] AllMaterials;

	for(it = materials_.begin(); 
		it != materials_.end(); ++it) 
	{
		plMatMapToPal(it->second, ThePalette_, pstart, pend);
	}	
}

void Scene::reloadPalette() 
{
  if (!colorsAllocated_) {
	  colorsAllocated_ = true;

	  if (paletteMode_) {
		  firstFreeColor_ = -1;
		  GrColor oldCell = -1;

		  for (int i = Scene::nEgaCols; i < Scene::nCols; i++) {
			  GrColor cell = GrAllocCell();
			  assert(cell != GrNOCOLOR);
			  assert(cell < nCols);
			  if (0 <= cell && cell < nCols && firstFreeColor_ == -1) {
				  firstFreeColor_ = cell;
				  oldCell = cell;
			  }
			  else {
				  assert(cell == oldCell + 1);
			  }
			  oldCell = cell;
			  lastFreeColor_ = cell;
		  }
	  } else {
		  firstFreeColor_ = Scene::nEgaCols;
		  lastFreeColor_ = Scene::nCols - 1;
	  }
  }

  // calculate new colors
  makePalette(firstFreeColor_, lastFreeColor_);

  // set palette
  if (paletteMode_) {
	  for (unsigned int i = firstFreeColor_; i <= lastFreeColor_; i++) {
		  GrSetColor(i, ThePalette_[i * 3], ThePalette_[i * 3 + 1], ThePalette_[i * 3 + 2]);
	  }
  } else {
	  for(unsigned int i = firstFreeColor_; i < nCols; i++) {
		GrColor col = GrAllocColor( ThePalette_[i*3], ThePalette_[i*3+1], ThePalette_[i*3+2] );
		TheGrxPalette_[i] = col;
	  }
  }
}

void Scene::setEgaColors(GrColor *egaColors) {
	for (int i = 0; i < nEgaCols; i++) {
		TheGrxPalette_[i] = egaColors[i];
	}
}

} // namespace scene
