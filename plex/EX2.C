// Ex2.c: simple Plush example
// Rotates a flat shaded cube
// The cube is now a different colored cube then ex1.c
// ZBuffering has been added, as well as dynamic framebuffer allocation

#include <float.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

// Include the plush header file
#include <plush.h> 

// Include our example graphics interface module
#include "ex.h" 

// Our variables
pl_Light *TheLight;   // Our light
pl_Obj *TheCube;      // Our cube object
pl_Mat *CubeMat;      // The material for the cube
pl_Mat *AllMaterials[2]; // Used for creating palette
pl_Cam *TheCamera; // Our camera
pl_uChar *TheFrameBuffer; // Our framebuffer to render to
pl_ZBuffer *TheZBuffer;   // Our zbuffer
pl_uChar  ThePalette[768];

int main() { // Main
  int i;
  exSetGraphics(); // Set graphics
  TheFrameBuffer = exAllocFrameBuffer(); // Alloc framebuffer
  if (!TheFrameBuffer) { 
    exSetText(); 
    printf("Out of memory!\n");
    exit(1);
  }
  // Alloc z-buffer
  TheZBuffer =  exAllocZBuffer();
  CubeMat = plMatCreate();    // Create the material for the cube
  CubeMat->NumGradients = 100; // Have it use 100 colors
  CubeMat->ShadeType = PL_SHADE_FLAT; // Make the cube flat shaded

  CubeMat->Ambient[0] = 32; // Set red ambient component
  CubeMat->Ambient[1] = 0;  // Set green ambient component
  CubeMat->Ambient[2] = 16; // Set blue ambient component

  CubeMat->Diffuse[0] = 200; // Set red diffuse component
  CubeMat->Diffuse[1] = 100; // Set green diffuse component
  CubeMat->Diffuse[2] = 150; // Set blue diffuse component

  plMatInit(CubeMat);          // Initialize the material

  AllMaterials[0] = CubeMat; // Make list of materials
  AllMaterials[1] = 0; // Null terminate list of materials
  plMatMakeOptPal(ThePalette,1,255,AllMaterials,1); // Create a nice palette

  ThePalette[0] = ThePalette[1] = ThePalette[2] = 0; // Color 0 is black

  plMatMapToPal(CubeMat,ThePalette,0,255); // Map the material to our palette

  exSetPalette(ThePalette); // Set the palette
 
  TheCube = plMakeBox(100.0,100.0,100.0,CubeMat); // Create the cube

  TheCamera = plCamCreate(GrSizeX(), // Screen width
                          GrSizeY(), // Screen height
                          GrSizeX()*3.0/(GrSizeY()*4.0), // Aspect ratio
                          90.0, // Field of view
                          TheFrameBuffer, // Framebuffer
                          TheZBuffer // ZBuffer
                          ); // Create the camera
  TheCamera->Z = -300; // Back the camera up from the origin
  TheCamera->Sort = 0; // We don't need to sort since zbuffering takes care
                       // of it for us!

  TheLight = plLightSet(plLightCreate(), // Create a light to be set up
             PL_LIGHT_VECTOR, // vector light
             0.0,0.0,0.0, // rotation angles
             1.0, // intensity
             1.0); // falloff, not used for vector lights
             
  while (!exGetKey()) { // While the keyboard hasn't been touched
    TheCube->Xa += 1.0; // Rotate by 1 degree on each axis
    TheCube->Ya += 1.0;
    TheCube->Za += 1.0;

    // clear framebuffer, zbuffer for next frame
    exClearBuffers(TheFrameBuffer, TheZBuffer);
    plRenderBegin(TheCamera);        // Start rendering with the camera
    plRenderLight(TheLight);         // Render our light
    plRenderObj(TheCube);            // Render our object
    plRenderEnd();                   // Finish rendering
    exWaitVSync();                   // Sync with retrace
    exFrameBufferToScreen();
  }
  exSetText(); // Restore text mode
  return 0;          // Quit
}
