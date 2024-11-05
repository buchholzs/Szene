/*
** Flurry2: a Plush demo program. VGA-MODE13 specific version
** Copyright (c) 1997, Justin Frankel
** For use with djgpp v2.x and Allegro
** For more information on Plush, see http://nullsoft.home.ml.org/plush/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <PLUSH.H>

// Include our example graphics interface module
#include "ex.h" 


#define NUM_ITERS 4
#define BOX_DIST 2.75
#define BOX_ROTFACTOR 2.6

void makeBoxes(pl_Obj *obj, pl_Float s, 
               pl_Mat **m, int i);       // Makes hierarchy of cubes
void rotateBoxes(pl_Obj *obj, pl_Float r); // Rotates hierarchy

pl_uChar *TheFrameBuffer; // Our framebuffer to render to

int main(int argc, char **argv) {
  int i, done = 0;

  pl_Mat *mat[NUM_ITERS + 1]; // Materials
  pl_Obj *obj;             // Head object
  pl_Light *light;
  pl_Cam *cam;

  pl_Float ar;          // Aspect ratio
  pl_uChar cpal[768];

  printf("Flurry v1.0\n"
         "Copyright (c) 1996, Justin Frankel\n");
  printf("Using:\n"
         "  %s\n",plVersionString);

  exSetGraphics(); // Set graphics
  TheFrameBuffer=exAllocFrameBuffer();
  if (!TheFrameBuffer) { 
    exSetText(); 
    printf("Out of memory!\n");
    exit(1);
  }
  ar = GrSizeX()*3.0/(GrSizeY()*4.0); // Calc aspect ratio

  cam = plCamCreate(GrSizeX(),GrSizeY(),ar,90.0,TheFrameBuffer,0);
  cam->Sort = 1;
  cam->Z = -350;

  // Initialize materials
  for (i = 0; i < NUM_ITERS; i ++) {
    mat[i] = plMatCreate();
    mat[i]->NumGradients = 200;
    mat[i]->Transparent = 2;
    mat[i]->Ambient[0] = mat[i]->Ambient[1] = mat[i]->Ambient[2] = 20;
    mat[i]->Shininess = 3;
    mat[i]->ShadeType = PL_SHADE_GOURAUD;
  }
  mat[0]->Diffuse[0] = 190; mat[0]->Diffuse[1]= 190;  mat[0]->Diffuse[2]= 0;
  mat[0]->Specular[0] = 240; mat[0]->Specular[1] = 240; mat[0]->Specular[2] = 0;
  mat[1]->Diffuse[0] = 0; mat[1]->Diffuse[1]= 0;  mat[1]->Diffuse[2]= 100;
  mat[1]->Specular[0] = 0; mat[1]->Specular[1] = 0; mat[1]->Specular[2] = 100;
  mat[2]->Diffuse[0] = 0; mat[2]->Diffuse[1]= 130;  mat[2]->Diffuse[2]= 0;
  mat[2]->Specular[0] = 0; mat[2]->Specular[1] = 130; mat[2]->Specular[2] = 0;
  mat[3]->Diffuse[0] = 100; mat[3]->Diffuse[1]= 0;  mat[3]->Diffuse[2]= 0;
  mat[3]->Specular[0] = 100; mat[3]->Specular[1] = 0; mat[3]->Specular[2] = 0;  
  mat[4] = 0;

  memset(cpal,0,768);
  for (i = 0; i < NUM_ITERS; i ++) {
    plMatInit(mat[i]);
  }
  plMatMakeOptPal(cpal,1,255,mat,NUM_ITERS);
  cpal[0] = cpal[1] = cpal[2] = 0;
  for (i = 0; i < NUM_ITERS; i ++) {
    plMatMapToPal(mat[i],cpal,0,255);
  }
   exSetPalette(cpal); // Set the new palette

  // Make objects
  obj = plMakeBox(100,100,100,mat[0]);
  makeBoxes(obj,100.0,&mat[1],NUM_ITERS-1);

  // Setup light
  light = plLightCreate();
  plLightSet(light,PL_LIGHT_VECTOR,0,0,0,1.0,1.0);

  float prevtime = clock() / (float) CLOCKS_PER_SEC; 
  float currtime = prevtime , difftime = 0.0; 
  while (!done) {
    currtime = (clock() / (float) CLOCKS_PER_SEC);
    difftime = currtime - prevtime;
    if (difftime < 0.05) {
      GrSleep(50-difftime*1000);
      continue;
    }
    prevtime = currtime;

    rotateBoxes(obj,1.0);
    exClearBuffers(TheFrameBuffer, NULL);
    plRenderBegin(cam);
    plRenderLight(light);
    plRenderObj(obj);
    plRenderEnd();
    exWaitVSync();         // wait for vsync
    exFrameBufferToScreen();
    while (kbhit()) switch(getch()) {
      case 27: done = 1; break;
      case '-': cam->Fov += 1.0; if (cam->Fov > 170) cam->Fov = 170; break;
      case '=': cam->Fov -= 1.0; if (cam->Fov < 10) cam->Fov = 10; break;
    }
  }
  free(TheFrameBuffer); // Free up memory
  plObjDelete(obj);
  plLightDelete(light);
  plCamDelete(cam);
  exSetText();
  printf("Try \"flurry 640x480\"\n");
}

void makeBoxes(pl_Obj *obj, pl_Float s, pl_Mat **m, int i) {
  int x;
  if (i==0) return;
  obj->Children[0] = plMakeBox(s/2,s/2,s/2,*m);
  obj->Children[0]->Xp = s*BOX_DIST;
  obj->Children[1] = plMakeBox(s/2,s/2,s/2,*m);
  obj->Children[1]->Xp = -s*BOX_DIST;
  obj->Children[2] = plMakeBox(s/2,s/2,s/2,*m);
  obj->Children[2]->Yp = s*BOX_DIST;
  obj->Children[3] = plMakeBox(s/2,s/2,s/2,*m);
  obj->Children[3]->Yp = -s*BOX_DIST;
  obj->Children[4] = plMakeBox(s/2,s/2,s/2,*m);
  obj->Children[4]->Zp = s*BOX_DIST;
  obj->Children[5] = plMakeBox(s/2,s/2,s/2,*m);
  obj->Children[5]->Zp = -s*BOX_DIST;
  for (x = 0; x < 6; x ++) 
    makeBoxes(obj->Children[x],s/2,m+1,i-1);
}

void rotateBoxes(pl_Obj *obj, pl_Float r) {
  int i;
  if (!obj) return;
  obj->Ya += r;
  obj->Xa += r;
  for (i = 0 ; i < 6; i ++) 
    rotateBoxes(obj->Children[i],r*BOX_ROTFACTOR);
  rotateBoxes(obj->Children[5],r*BOX_ROTFACTOR);
}

