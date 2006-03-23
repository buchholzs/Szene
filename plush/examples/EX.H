// ex.h: provides a standard interface for video and keyboard for the
// example programs to use.

// DJGPP: we will use grx for video
#include <grx20.h>
#ifndef EX_H
#define EX_H

struct pl_uChar;

int exGetKey();
void exWaitVSync();
void exSetPalette(pl_uChar *palette);
void exSetGraphics();
pl_uChar *exAllocFrameBuffer();
pl_ZBuffer *exAllocZBuffer();
void exClearBuffers(pl_uChar *TheFrameBuffer, pl_ZBuffer *TheZBuffer);
void exFrameBufferToScreen();
void exSetText();
#endif
