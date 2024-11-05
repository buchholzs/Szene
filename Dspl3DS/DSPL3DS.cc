// Ex1.c: simple Plush example
// Rotiert ein 3ds-Objekt

#include <dos.h>
#include <conio.h>
#include <grx20.h>

#include <float.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <sys/stat.h>
// Include the plush header file
#include <PLUSH.H> 

using namespace std;

extern "C" int       getopt(int, char* const*, const char*);
extern char *optarg;
extern int optind, opterr;
extern char optopt;

// Our variables
pl_Light *TheLight;		// Our light
pl_Obj *TheObj;			// Our Obj object
pl_Obj *ThePlane;		// Plane
pl_Mat *ObjMat;			// The material for the Obj
pl_Mat *PlaneMatDark;		// The material for the Plane
pl_Mat *PlaneMatLight;		// The material for the Plane
pl_Mat *AllMaterials[10];	// Used for creating palette
pl_Cam *TheCamera;		// Our camera
pl_uChar *TheFrameBuffer;	// Our framebuffer to render to
pl_ZBuffer *TheZBuffer=NULL;	// Our zbuffer
pl_uChar ThePalette[768];
int key=0;

// constants
const pl_Float cAngle = 5.0;	// movement
const int cFields = 8;		// plane fields (one direction)
void usage(const char *programm)
{
  cout << "Benutzung:\n\t"
       << programm << " -s -z <Zoomfaktor> <3ds-Datei>\n"
       << "\t-s\tZBuffer ist aus\n"
       << "\t-z\tZoomfaktor\n";
}
int main(int argc, char *argv[]) { // Main
  int i;
  GrContext screen;
  pl_Float zoom_factor = 1.0;
  char *input_filename=NULL;
  pl_Bool use_zbuffer=1;
  bool doRotate=true;
  pl_sChar lastmessage[80] = "DSPL3DS"; // last message used for status line

#if defined(DJGPP)
  int c;
  opterr = 0;
  while ((c=getopt(argc, argv, "sz:")) != -1)
    {
      switch (c)
	{
	case 'z':
	  zoom_factor = atof(optarg);
	  break;
	case 's':
	  use_zbuffer = !use_zbuffer;
	  break;
	case '?':
	  cout << "Unbekannte Option -" << optopt << endl;
	  usage(argv[0]);
	  exit(-1);
	}
    }
  if (optind==argc) {
    cout << "3ds-Datei fehlt.\n";
    usage(argv[0]);
    exit(-2);
  }
  input_filename = argv[optind];
#else
  if (1==argc) {
    cout << "3ds-Datei fehlt.\n";
    exit(-2);
  }
  input_filename = argv[argc-1];  
#endif

  struct stat s;
#if defined(DJGPP)
  if (stat(input_filename, &s)!=0 || !S_ISREG(s.st_mode)) {
#else
  if (stat(input_filename, &s)!=0) {
#endif
    cout << input_filename << " kann nicht ge�ffnet werden\n";
    exit(-2);
  }

#if defined(DJGPP) || defined(__WATCOMC__)
  // Put the fpu in a low precision, no exception state
  _control87(MCW_EM|PC_24,MCW_EM|MCW_PC); 
#endif
  cout << "Graphik initialisieren" << endl;
  GrSetMode(GR_width_height_color_graphics, 640, 480, 256);
  cout << "Aufl�sung: " << GrSizeX() << 'x' << GrSizeY() << endl;
  TheFrameBuffer = new pl_uChar[GrSizeX()*GrSizeY()];
  if (use_zbuffer) {
    TheZBuffer = new pl_ZBuffer[GrSizeX()*GrSizeY()];
  }
  assert(GrNumPlanes()==1);   // nur eine Plane supportet
  char *memory[4] = { (char *)TheFrameBuffer, NULL, NULL, NULL };
  GrCreateContext(GrSizeX(),GrSizeY(), memory, &screen);

  // object material 
  ObjMat = plMatCreate();    // Create the material for the Obj
  ObjMat->NumGradients = 100; // Have it use 100 colors
  ObjMat->ShadeType = PL_SHADE_GOURAUD; // Make the Obj flat shaded
  plMatInit(ObjMat);          // Initialize the material

  // plane material #1
  PlaneMatLight = plMatCreate();    // Create the material for the Obj
  PlaneMatLight->NumGradients = 100; // Have it use 100 colors
  PlaneMatLight->ShadeType = PL_SHADE_FLAT;
  PlaneMatLight->Ambient[0] = 0; // Set red ambient component
  PlaneMatLight->Ambient[1] = 0;  // Set green ambient component
  PlaneMatLight->Ambient[2] = 19; // Set blue ambient component

  PlaneMatLight->Diffuse[0] = 0; // Set red diffuse component
  PlaneMatLight->Diffuse[1] = 0; // Set green diffuse component
  PlaneMatLight->Diffuse[2] = 196; // Set blue diffuse component

  plMatInit(PlaneMatLight);          // Initialize the material

  // plane material #2
  PlaneMatDark = plMatCreate();    // Create the material for the Obj
  PlaneMatDark->NumGradients = 100; // Have it use 100 colors
  PlaneMatDark->ShadeType = PL_SHADE_FLAT;
  PlaneMatDark->Ambient[0] = 0; // Set red ambient component
  PlaneMatDark->Ambient[1] = 0;  // Set green ambient component
  PlaneMatDark->Ambient[2] = 9; // Set blue ambient component

  PlaneMatDark->Diffuse[0] = 0; // Set red diffuse component
  PlaneMatDark->Diffuse[1] = 0; // Set green diffuse component
  PlaneMatDark->Diffuse[2] = 98; // Set blue diffuse component

  plMatInit(PlaneMatDark);          // Initialize the material
  
  // Palette generation
  int matCnt=0;
  AllMaterials[matCnt++] = PlaneMatLight; // Make list of materials
  AllMaterials[matCnt++] = PlaneMatDark; // Make list of materials
  AllMaterials[matCnt++] = ObjMat; // Make list of materials
  AllMaterials[matCnt] = 0; // Null terminate list of materials
  plMatMakeOptPal(ThePalette,1,255,AllMaterials,matCnt); // Create a nice palette

  ThePalette[0] = ThePalette[1] = ThePalette[2] = 0; // Color 0 is black

  plMatMapToPal(PlaneMatLight,ThePalette,0,255); // Map the material to our palette
  plMatMapToPal(PlaneMatDark,ThePalette,0,255); // Map the material to our palette
  plMatMapToPal(ObjMat,ThePalette,0,255); // Map the material to our palette

  // Convert std 8 bit/chan palette to vga's 6 bit/chan palette
  for (i = 0; i < 256; i ++)
    GrSetColor(i,ThePalette[i*3],
	ThePalette[i*3+1],
	ThePalette[i*3+2]);


  ThePlane = plMakePlane(100.0, 100.0,cFields,PlaneMatLight); // Create the Plane
  assert((ThePlane->NumFaces % 4) == 0);
  for (int i = 0; i < ThePlane->NumFaces; i+=4) {
    if ((i / (cFields * 2)) % 2) {
      ThePlane->Faces[i].Material = PlaneMatDark;
      ThePlane->Faces[i+1].Material = PlaneMatDark;
      ThePlane->Faces[i+2].Material = PlaneMatLight;
      ThePlane->Faces[i+3].Material = PlaneMatLight;
    } else{
      ThePlane->Faces[i].Material = PlaneMatLight;
      ThePlane->Faces[i+1].Material = PlaneMatLight;
      ThePlane->Faces[i+2].Material = PlaneMatDark;
      ThePlane->Faces[i+3].Material = PlaneMatDark;
    }
  }
  

  ThePlane->Xa = 45;
  TheObj = plRead3DSObj(input_filename,ObjMat); // Create the Obj

  if (zoom_factor != 1.0)
    plObjScale(TheObj, zoom_factor);

  TheCamera = plCamCreate(GrSizeX(), // Screen width
      GrSizeY(), // Screen height
      (GrSizeX()*3.0)/(GrSizeY()*4.0), // Aspect ratio
      90.0, // Field of view
      TheFrameBuffer, // Framebuffer
      ((use_zbuffer) ? TheZBuffer:NULL) // ZBuffer
                          ); // Create the camera
  TheCamera->Z = -300; // Back the camera up from the origin
  TheCamera->Sort = !use_zbuffer; // Sortieren, falls kein Z-Buffer

  TheLight = plLightSet(plLightCreate(), // Create a light to be set up
      PL_LIGHT_VECTOR, // vector light
      0.0,0.0,0.0, // rotation angles
      1.0, // intensity
      1.0); // falloff, not used for vector lights
             
  while (key!='q') { // While the keyboard hasn't been touched
    if (kbhit()) {
      key = getch();
      switch (key) {
      case '+':
	plObjScale(TheObj, 2.0);
	break;
      case '-':
	plObjScale(TheObj, 0.5);
	break;
      case 'f':
	TheObj=plObjFlipNormals(TheObj);
	break;
      case 'c':
	plObjCalcNormals(TheObj);
	break;
      case 'r':
	doRotate=!doRotate;
	break;
      case 'x':
	TheObj->Xa += cAngle;
	break;
      case 'y':
	TheObj->Ya += cAngle;
	break;
      case 'z':
	TheObj->Za += cAngle;
	break;
      }
    }
    // TheObj->Xa += 1.0; // Rotate by 1 degree on each axis
    if (doRotate) {
      TheObj->Ya += 1.0;
    }
    // TheObj->Za += 1.0;
    memset(TheFrameBuffer,0,GrSizeX()*GrSizeY()); // clear framebuffer for next frame

    if (use_zbuffer) {
      memset(TheZBuffer,0,GrSizeX()*GrSizeY()*sizeof(pl_ZBuffer));
    }

    plRenderBegin(TheCamera);	// Start rendering with the camera
    plRenderLight(TheLight);	// Render our light
    plRenderObj(ThePlane);	// Render plane
    plRenderObj(TheObj);	// Render our object
    plRenderEnd();		// Finish rendering
    // display last message
    plTextPrintf(TheCamera,TheCamera->ClipLeft+5,TheCamera->ClipBottom-16,0.0,156,lastmessage);
    //    exWaitVSync();                   // Sync with retrace

    GrBitBlt(NULL,0,0,&screen,0,0,GrMaxX(),GrMaxY(),GrWRITE);
  }
  GrSetMode(GR_default_text); // Restore text mode
  return 0;          // Quit
}
