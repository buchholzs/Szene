// Ex4.c: simple Plush example
// Rotates a flat shaded texture mapped cube
// Reads texture from texture1.pcx

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
pl_uChar ThePalette[768];

int main() { // Main
  int i, done;
  // Show user controls
  printf("Controls:\n"
         "  SPACE: toggle perspective correction\n"
         "  ESC: quit\n"
         " Hit any key to begin\n");
  while (!exGetKey()); // Wait for key
  while (exGetKey());  // Make sure no other keys are in the queue
  
  exSetGraphics(); // Set graphics
TheFrameBuffer=exAllocFrameBuffer();
  if (!TheFrameBuffer) { 
    exSetText(); 
    printf("Out of memory!\n");
    exit(1);
  }
  CubeMat = plMatCreate();    // Create the material for the cube
  CubeMat->NumGradients = 256; // Have it use 256 colors
  CubeMat->ShadeType = PL_SHADE_FLAT; // Make the cube flat shaded
  CubeMat->Texture = plReadPCXTex("texture1.pcx",
                                 1, // Rescale the texture if necessary
                                 1  // Tell it to optimize the texture's palette
                                );
  CubeMat->PerspectiveCorrect = 0;  // No correction by default
    // These are 128 by default, but make it to bright for this app
  CubeMat->Diffuse[0] = CubeMat->Diffuse[1] = CubeMat->Diffuse[2] = 0;
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
                          60.0, // Field of view
                          TheFrameBuffer, // Framebuffer
                          NULL // ZBuffer (none)
                          ); // Create the camera
  TheCamera->Z = -300; // Back the camera up from the origin

  TheLight = plLightSet(plLightCreate(), // Create a light to be set up
             PL_LIGHT_VECTOR, // vector light
             0.0,0.0,0.0, // rotation angles
             1.0, // intensity
             1.0); // falloff, not used for vector lights
             
  done = 0;
  while (!done) { // While the keyboard hasn't been touched
    TheCube->Xa += 1.0; // Rotate by 1 degree on each axis
    TheCube->Ya += 1.0;
    TheCube->Za += 1.0;
    exClearBuffers(TheFrameBuffer, NULL); // clear framebuffer for next frame
    plRenderBegin(TheCamera);        // Start rendering with the camera
    plRenderLight(TheLight);         // Render our light
    plRenderObj(TheCube);            // Render our object
    plRenderEnd();                   // Finish rendering
    exWaitVSync();                   // Sync with retrace
    exFrameBufferToScreen(); // dump to screen
    switch (exGetKey()) {
      case 0: break; // no key
      case 27: done = 1; break; // esc
      case ' ':  // space
        CubeMat->PerspectiveCorrect ^= 8; // Toggle whether or not it's 8
        plMatInit(CubeMat);
      break;
    }
  }
  exSetText(); // Restore text mode
  return 0;          // Quit
}
