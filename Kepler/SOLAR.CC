///////////////////////////////////////////////////////////////////////////////
//
// MODULE: solar.h
// DESCRIPTION: Klasse Solar
// HISTORY:
// $Log: solar.cc,v $
// Revision 1.4  1998/04/11 22:51:43  buchholz
// Bewegung der Kamera, Zielverfolgung
//
///////////////////////////////////////////////////////////////////////////////
#include "solar.h"

// Systemincludes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>

// Projektincludes
#include <../compat/mousex.h>

//---Konstanten--------------------------------------------------------------
const char *palFilename = "solar.pal";
const pl_Float cSunRadius = 100.0;
const pl_Float cEarthRadius = cSunRadius * 0.1;
const pl_Float cMoonRadius  = cSunRadius * 0.05;
const float cFPS  = 1.0 / 30.0;

inline double min(double a, double b)
{
  return a < b ? a : b;
}
inline double max(double a, double b)
{
  return a > b ? a : b;
}

//---Implementation----------------------------------------------------------
Solar::Solar(int updatePalette, int useTextures)
  : Task("Solar")
{
  int	i;
  int cntMaterial;
  clock_t oldtime;

  GrMouseInit();
  GrMouseSetColors(Solar::cTextColor, Solar::cBlackColor);

  cout << "Auflîsung: " << GrScreenX()	<<	'x' << GrScreenY() << endl;

  // Framebuffer erzeugen  
  TheFrameBuffer = new uchar[GrScreenX() * GrScreenY()];

  // Material erzeugen
  cntMaterial = 0;
  Material[0] = plMatCreate();	 // Create the material for the cube
  Material[0]->NumGradients =	32; // Have it use 100 colors
  Material[0]->ShadeType =	PL_SHADE_GOURAUD;	// Make the cube flat shaded
  Material[0]->Shininess =	10; // Make the torus a bit more shiny

  Material[0]->Ambient[0] = 80; // Set red ambient component
  Material[0]->Ambient[1] = 80;	// Set green ambient component
  Material[0]->Ambient[2] = 0; // Set blue ambient component

  Material[0]->Diffuse[0] = 100;	// Set red diffuse component
  Material[0]->Diffuse[1] = 100;	// Set green diffuse component
  Material[0]->Diffuse[2] = 0; // Set blue diffuse component

  Material[0]->Specular[0]	= 200; // Set red specular component
  Material[0]->Specular[1]	= 200; // Set green specular component
  Material[0]->Specular[2]	= 0; // Set blue specular component
  plMatInit(Material[0]);			  // Initialize the material
  cntMaterial ++;

  Material[1] = plMatCreate();	 // Create the material for the cube
  Material[1]->NumGradients =	32; // Have it use 128 colors
  Material[1]->ShadeType = PL_SHADE_GOURAUD;	// Make the cube flat shaded
  // These are 128 by default, but make it to bright for this app
  Material[1]->Diffuse[0] = Material[1]->Diffuse[1] =	Material[1]->Diffuse[2]	= 0;
  oldtime = clock();
  if (useTextures) {
    Material[1]->Texture = plReadPCXTex("maps/moonmap.pcx",
	1,	// Rescale the texture if necessary
	1	// Tell it to optimize the texture's
	// palette
  					);
  } else {
    Material[1]->Diffuse[0] = 100;	// Set red diffuse component
    Material[1]->Diffuse[1] = 100;	// Set green diffuse component
    Material[1]->Diffuse[2] = 100; // Set blue diffuse component
  
    Material[1]->Specular[0]	= 200; // Set red specular component
    Material[1]->Specular[1]	= 200; // Set green specular component
    Material[1]->Specular[2]	= 200; // Set blue specular component
  }
  cout << "Zeit fÅr Lesen von Textur 1: "
       << (((float) (clock() - oldtime)) / (float) CLOCKS_PER_SEC)
       << " Sekunden" << endl;

  Material[1]->PerspectiveCorrect = 0; // No correction by default
  plMatInit(Material[1]);	// Initialize the material
  cntMaterial ++;

  Material[2] = plMatCreate();	 // Create the material for the cube
  Material[2]->NumGradients =	32; // Have it use 100 colors
  Material[2]->ShadeType =	PL_SHADE_GOURAUD;	// Make the cube flat shaded
  // These are 128 by default, but make it to bright for this app
  Material[2]->Diffuse[0] = Material[2]->Diffuse[1] =	Material[2]->Diffuse[2]	= 0;
  oldtime = clock();
  if (useTextures) {
    Material[2]->Texture = plReadPCXTex("maps/earthma.pcx",
	1,	// Rescale the texture if necessary
	1	// Tell it to optimize the texture's
	// palette
					);
  } else {
    Material[2]->Diffuse[0] = 0;	// Set red diffuse component
    Material[2]->Diffuse[1] = 0;	// Set green diffuse component
    Material[2]->Diffuse[2] = 100; // Set blue diffuse component
  
    Material[2]->Specular[0]	= 0; // Set red specular component
    Material[2]->Specular[1]	= 0; // Set green specular component
    Material[2]->Specular[2]	= 200; // Set blue specular component
  }
  cout << "Zeit fÅr Lesen von Textur 2: "
       << (((float) (clock() - oldtime)) / (float) CLOCKS_PER_SEC)
       << " Sekunden" << endl;

  Material[2]->PerspectiveCorrect =	0;	 // No correction by default
  plMatInit(Material[2]);			  // Initialize the material
  cntMaterial ++;

  Material[cntMaterial]	= 0; // Null terminate list of materials
  oldtime = clock();
  if (updatePalette) {
    cout << "Generiere Palette" << endl;
    plMatMakeOptPal(ThePalette,cFirstFreeColor,255,Material,cntMaterial); // Create a nice palette
    ofstream palfile(palFilename, ios::out|ios::binary);
    if (!palfile) {
      cerr << "Datei " << palFilename
	   << " kann nicht geîffnet werden." << endl;
      exit(0);
    }
    palfile.write((char *)ThePalette, sizeof ThePalette);
    palfile.close();
  } else {
    ifstream palfile(palFilename, ios::in|ios::binary);
    if (!palfile) {
      cerr << "Datei " << palFilename
	   << " kann nicht geîffnet werden." << endl;
      exit(0);
    }
    palfile.read((char *)ThePalette, sizeof ThePalette);
    palfile.close();
  }
  cout << "Zeit fÅr Palettengenerierung: "
       << (((float) (clock() - oldtime)) / (float) CLOCKS_PER_SEC)
       << " Sekunden" << endl;

  ThePalette[0] = ThePalette[1] = ThePalette[2]	= 0; // Color 0 is black

  for	(i=0;	i<cntMaterial;	i++) {
    // Map the material to our palette
    plMatMapToPal(Material[i],ThePalette,cFirstFreeColor,255); 
  }
  TheSun	= plMakeSphere(cSunRadius,	8,	8,	Material[0]);
  TheTargets.push_back(Target(TheSun, cSunRadius, "Sonne"));
  TheEarth = plMakeSphere(cEarthRadius, 8, 8, Material[2]);
  TheTargets.push_back(Target(TheEarth, cEarthRadius, "Erde"));
  TheObjects.push_back(TheEarth);
  TheMoon =	plMakeSphere(cMoonRadius, 8, 8, Material[1]);
  TheTargets.push_back(Target(TheMoon, cMoonRadius, "Mond"));
  TheObjects.push_back(TheMoon);

  TheCamera	= plCamCreate(GrScreenX(),	// Screen width
      GrScreenY(),	// Screen height
      GrScreenX()*3.0/(GrScreenY()*4.0), // Aspect ratio
      90.0, // Field of view
      TheFrameBuffer,	// Framebuffer
      NULL // ZBuffer (none)
			      ); // Create the camera
  TheCamera->Z	= -600; // Back the camera up from the origin
  TheCamera->Y	= 600; // Back the camera up from the origin
  plCamSetTarget(TheCamera, 0.0,	0.0, 0.0);

  TheLight = plLightSet(plLightCreate(), // Create a light to be set up
      PL_LIGHT_POINT, // point light
      0.0,0.0,0.0, // Position
      1.0,	// intensity
      200.0);	// falloff, not used for vector lights
  TheSunLight = plLightSet(plLightCreate(), // Create a light to be set up
      PL_LIGHT_VECTOR,	// point light
      0.0,0.0,0.0, // Position
      1.0,	// intensity
      200.0);	// falloff, not used for vector lights

  // Convert std 8 bit/chan palette to vga's 6 bit/chan palette
  //  for	(i = 0; i < 768; i ++) ThePalette[i] >>= 2;

  // Palette setzen

  GrSetColor(cTextColor, 0, 192, 0);
  for(i=cFirstFreeColor; i< 256; i++)	{
    GrSetColor(i, ThePalette[i*3], ThePalette[i*3+1], ThePalette[i*3+2]	);
  }

  // Kontext zum Zeichnen erzeugen
  char far *memory[4] = { (char *)TheFrameBuffer, NULL, NULL, NULL };
  GrCreateContext(GrScreenX(),GrScreenY(), memory, &screen);

  // aktuelles Ziel ausw‰hlen
  currTarget_ = TheTargets.begin();
}

Solar::~Solar()
{
  delete [] TheFrameBuffer;
}

void Solar::TaskMain()
{
  MouseEvent event;
  int vorwaerts	= 1;
  int followMode	= 0;	// Kamera folgt currTarget_
  // Alte Koordinaten des Zielobjektes
  pl_Float old_Xp;
  pl_Float old_Yp;
  pl_Float old_Zp;
  pl_Float	TravelSpeed = 0.0;	// Reisegeschwindigkeit
  int	key;

  pl_Float rot_Earth	= 0.0;
  pl_Float rot_Moon = 0.0;
  pl_Float rot_dx	= (2.0 * PL_PI) / 360.0;	// Kreis in 36 Teile
  clock_t oldtime = clock();
  while ('q' != key) { // While the keyboard hasn't been touched
    // Framerate von 1/30s einhalten
    float clk_diff = ((float) (clock() - oldtime)) / (float) CLOCKS_PER_SEC;    
    if (clk_diff < cFPS) {
      sleep((int)fabs(clk_diff - cFPS) * 1000 /* msec */);
    }
    oldtime = clock();

    rot_Earth += rot_dx	/ 2;
    normAngleRad(rot_Earth);

    TheEarth->Xp = cSunRadius*20.0 * cos(rot_Earth);
    TheEarth->Zp = cSunRadius*20.0 * sin(rot_Earth);
	 
    rot_Moon += rot_dx;
    normAngleRad(rot_Moon);

    TheMoon->Xp =	TheEarth->Xp +	cEarthRadius*10.0 * cos(rot_Moon);
    TheMoon->Zp =	TheEarth->Zp +	cEarthRadius*10.0 * sin(rot_Moon);

    MouseGetEvent(M_POLL |	M_EVENT,	&event);
    if (event.flags == M_KEYPRESS) {		
      key =	event.key;
      cout << key << ' ';
      cout.flush();
      switch	(key)	{
      case '+':
	TheCamera->Fov	-=	10.0;
	if	(TheCamera->Fov <	10.0)
	  TheCamera->Fov = 10.0;
        break;
      case '-':
	TheCamera->Fov	+=	10.0;
	if	(TheCamera->Fov >	120.0)
	  TheCamera->Fov = 120.0;
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '8':
      case '9':
	TravelSpeed = (key-'0') * 2;
        break;
      case 's':	// Drehen nach oben
	TheCamera->Pitch += 5.0;
	normAngleDeg(TheCamera->Pitch);
	break;
      case 'x':	// Drehen nach unten
	TheCamera->Pitch -= 5.0;
	normAngleDeg(TheCamera->Pitch);
	break;
      case 'y':	// Drehen nach links
	TheCamera->Pan += 5.0;
	normAngleDeg(TheCamera->Pan);
	break;
      case 'c':	// Drehen nach rechts
	TheCamera->Pan -= 5.0;
	normAngleDeg(TheCamera->Pan);
	break;
      case 127:	// Backspace, Bewegung umkehren
	vorwaerts = -1 * vorwaerts;
	break;
      case 'f':	// Toggle Follow-Mode
	followMode = !followMode;
	break;
      case '\t':	// N‰chstes/Vorheriges Zielobjekt
	if (event.kbstat == KB_SHIFT) {
	  if(currTarget_ == TheTargets.begin()) {
	    currTarget_ = TheTargets.end();
	  }
	  --currTarget_;
	} else {
	  ++currTarget_;
	  if (currTarget_ == TheTargets.end()) {
	    currTarget_ = TheTargets.begin();
	  }
       	}
	break;
      }
    }
    if (!followMode) {
      // Vorw‰rtsbewegung
      TheCamera->X -=

        vorwaerts*TravelSpeed*sin(TheCamera->Pan*PL_PI/180.0)
	*cos(TheCamera->Pitch*PL_PI/180.0);
      TheCamera->Z += 

        vorwaerts*TravelSpeed*cos(TheCamera->Pan*PL_PI/180.0)
	*cos(TheCamera->Pitch*PL_PI/180.0);
      TheCamera->Y += 

        vorwaerts*TravelSpeed*sin(TheCamera->Pitch*PL_PI/180.0);
    } else {
      // Automatische Zielverfolgung
      register Target *TheTarget = &(*currTarget_);
      pl_Float nearDist = 2*TheTarget->radius_;
      pl_Float *cam;
      pl_Float *target;
      pl_Float *old;
      for (register int i=0; i<3; i++) {
	pl_Float Speed = TravelSpeed;

	cout << "\n" << TheTarget->name_;
	switch (i) {
	case 0:
	  cam = &TheCamera->X;
	  target = &TheTarget->Obj_->Xp;
	  old = &old_Xp;
	  cout << " X ";
	  break;
	case 1:
	  cam = &TheCamera->Y;
	  target = &TheTarget->Obj_->Yp;
	  old = &old_Yp;
	  cout << " Y ";
	  break;
	case 2:
	  cam = &TheCamera->Z;
	  target = &TheTarget->Obj_->Zp;
	  old = &old_Zp;
	  cout << " Z ";
	  break;
	};
	if (fabs(*cam - *target) > nearDist) {
	  Speed = min(fabs(*cam - *target), TravelSpeed);

	  *cam = (*cam > *target) ?
	    *cam - Speed : *cam + Speed;

	  *old = *target;
        } else {
	  // Kamera dem Objekt nachfÅhren
	  cout << "Diff: " << fabs(*target - *old)
	       << " TheCamera "  << *cam
	       << " TheTarget " <<	*target
	       << " old " <<	*old;

	  *cam = (*target > *old) ?
	    *cam + fabs(*target - *old) : *cam - fabs(*target - *old);
      	}

	*old = *target;
      }
      plCamSetTarget(TheCamera,
	  TheTarget->Obj_->Xp,
	  TheTarget->Obj_->Yp,
	  TheTarget->Obj_->Zp);
    }
    memset(TheFrameBuffer,0,GrScreenX()*GrScreenY());	// clear framebuffer
    // for next frame
    plRenderBegin(TheCamera);			 // Start rendering with the camera
    plRenderLight(TheSunLight);			 // Render our light
    plRenderObj(TheSun);				// Render our object
    plRenderLight(TheLight);			 // Render our light
    for (list<pl_Obj *>::iterator it = TheObjects.begin(); 
	 it != TheObjects.end(); ++it) {
      plRenderObj(*it);
    }
    plRenderEnd();						 // Finish rendering

    // Textausgabe
    if (followMode) {
      plTextPrintf(TheCamera, 5,5,-300,cTextColor,
	  (signed char *)"X:%3.1f Y:%3.1f Z:%3.1f\nFOV:%3.1f Pitch:%3.1f Pan:%3.1f\nZiel:%s Distanz:%3.1f",
	  TheCamera->X, TheCamera->Y, TheCamera->Z,TheCamera->Fov,
	  TheCamera->Pitch, TheCamera->Pan,
	  currTarget_->name_.c_str(),
	  sqrt(pow(TheCamera->X-currTarget_->Obj_->Xp,2) +
	      pow(TheCamera->Y-currTarget_->Obj_->Yp,2) +
	      pow(TheCamera->Z-currTarget_->Obj_->Zp,2)));
    } else {
      plTextPrintf(TheCamera, 5,5,-300,cTextColor,
	  (signed char *)"X:%3.1f Y:%3.1f Z:%3.1f\nFOV:%3.1f Pitch:%3.1f Pan:%3.1f",
	  TheCamera->X, TheCamera->Y, TheCamera->Z,TheCamera->Fov,
	  TheCamera->Pitch, TheCamera->Pan);
    }
    GrMouseEraseCursor();
    GrBitBlt(NULL,0,0,&screen,0,0,GrScreenX()-1,GrScreenY()-1,GrWRITE);
    GrMouseDisplayCursor();
  }
  scheduler(0);			// letzter Task
}

