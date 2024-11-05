// ex.h: provides a standard interface for video and keyboard for the
// example programs to use.

#include <PLUSH.H>
#include "ex.h"

static GrContext *ctx;

int exGetKey() {
  if (kbhit()) return (getch());
  return 0;
}

void exWaitVSync() {
  // This code should work on all three
#ifndef NO_RETRACE_WAIT
  while (!(inportb(0x3DA)&8)); // wait for end
  while ((inportb(0x3DA)&8));  // wait for start
#endif
}

void exSetPalette(pl_uChar *palette) {
  int i;
  for (i = 0; i < 256; i++) {
    GrSetColor(i, palette[ i*3 ], 
	       palette[ i*3 + 1], 
	       palette[ i*3 + 2 ]);
  }
}

void exSetGraphics() {
  GrSetMode( GR_width_height_bpp_graphics,640,480, 8);
  GrResetColors();
}

void exFrameBufferToScreen() {
  GrBitBlt(NULL, 0, 0, ctx, 0, 0, GrMaxX(), GrMaxY(), GrWRITE);
}

pl_ZBuffer *exAllocZBuffer() {
  pl_ZBuffer *TheZBuffer = (pl_ZBuffer *) malloc(GrSizeX()*GrSizeY()*sizeof(pl_ZBuffer));
  return TheZBuffer;
}

pl_uChar *exAllocFrameBuffer() {
  pl_uChar *TheFrameBuffer = (pl_uChar*)malloc(GrSizeX()*GrSizeY());
  char *memory[4] = {(char *)TheFrameBuffer,0,0,0};
  ctx = GrCreateContext(GrSizeX(),GrSizeY(),memory,NULL);
  return TheFrameBuffer;
}

void exClearBuffers(pl_uChar *TheFrameBuffer, pl_ZBuffer *TheZBuffer) {
  if (TheZBuffer) memset(TheZBuffer,0,GrSizeX()*GrSizeY()*sizeof(pl_ZBuffer));
  if (TheFrameBuffer) memset(TheFrameBuffer,0,GrSizeX()*GrSizeY());
}

void exSetText() {
  GrSetMode( GR_default_text );
}
