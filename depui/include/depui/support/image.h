#ifndef MX_PLATFORM_SUPPORT_IMAGE_H
#define MX_PLATFORM_SUPPORT_IMAGE_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/platform/vtable.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef MX_NEED_IMAGE
	 typedef struct MxImage {

		  MxImageVTable *vtable;

		  int w, h;					  /* Width height and color depth */
		  unsigned int c:8;

		  unsigned int allocated:1;

		  unsigned int aquired:1;
		  unsigned int wasaquired:1;

		  void *rows[1];			  /* This must be the last thing in the struct */

	 } MxImage;

/* How many bytes in one row of image data, rounded to 4 byte boundary
   for fast access, and good alignmment of the row data */
#define __MXIMAGEBYTESPERROW(w,bits) ((((bits) * ((w) + 1)) + 7) / 8)
#define _MXIMAGEBYTESPERROW(w,bits)  (((__MXIMAGEBYTESPERROW((w),(bits)) + 3) / 4) * 4)

/* How many bytes in an image, so we can possibly make some images static */
#define MXIMAGEBYTES(w,h,bits) (sizeof(MxImage) + \
                               (((h) + 1) * sizeof(unsigned char*)) + \
                               (((h) + 1) * _MXIMAGEBYTESPERROW((w),(bits))))

/* Image creation stuff for internal use */
	 void Mx_ImageConstructSimple(MxImage * image, int w, int h, int bits, MxImageVTable * vtable);
	 MxImage *Mx_ImageCreateSimple(int w, int h, int bits, MxImageVTable * vtable);

/* General creation and destruction functions */
	 MxImage *Mx_ImageCreateDepth(int w, int h, int bits);
	 void Mx_ImageDestroy(MxImage * image);

	 MxImage *Mx_ImageLoad(const char *filename, int bits, MxColorFunc makecol);
	 MxImage *Mx_ImageLoadPCX(const char *filename, int bits, MxColorFunc makecol);
	 MxImage *Mx_ImageLoadBMP(const char *filename, int bits, MxColorFunc makecol);

//    void Mx_ImageClip(MxImage * image, int x1, int y1, int x2, int y2);
//    void Mx_ImageClipGet(MxImage * image, int *x1, int *y1, int *x2, int *y2);

#ifdef MX_IMAGE_SUPPORT_1
	 extern MxImageVTable MxVtable1;
	 void Mx_ImagePixel1Fast(MxImage * image, int x1, int y1, MxColor color);
	 MxColor Mx_ImageGetPixel1Fast(MxImage * image, int x1, int y1);
	 MxImage *Mx_ImageCreate1(int w, int h);
#endif

#ifdef MX_IMAGE_SUPPORT_4
	 extern MxImageVTable MxVtable4;
	 void Mx_ImagePixel4Fast(MxImage * image, int x1, int y1, MxColor color);
	 MxColor Mx_ImageGetPixel4Fast(MxImage * image, int x1, int y1);
	 MxImage *Mx_ImageCreate4(int w, int h);
#endif

#ifdef MX_IMAGE_SUPPORT_8
	 extern MxImageVTable MxVtable8;
	 void Mx_ImagePixel8Fast(MxImage * image, int x1, int y1, MxColor color);
	 MxColor Mx_ImageGetPixel8Fast(MxImage * image, int x1, int y1);
	 MxImage *Mx_ImageCreate8(int w, int h);
#endif

#ifdef MX_IMAGE_SUPPORT_16
	 extern MxImageVTable MxVtable16;
	 void Mx_ImagePixel16Fast(MxImage * image, int x1, int y1, MxColor color);
	 MxColor Mx_ImageGetPixel16Fast(MxImage * image, int x1, int y1);
	 MxImage *Mx_ImageCreate16(int w, int h);
#endif

#ifdef MX_IMAGE_SUPPORT_24
	 extern MxImageVTable MxVtable24;
	 void Mx_ImagePixel24Fast(MxImage * image, int x1, int y1, MxColor color);
	 MxColor Mx_ImageGetPixel24Fast(MxImage * image, int x1, int y1);
	 MxImage *Mx_ImageCreate24(int w, int h);
#endif

#ifdef MX_IMAGE_SUPPORT_32
	 extern MxImageVTable MxVtable32;
	 void Mx_ImagePixel32Fast(MxImage * image, int x1, int y1, MxColor color);
	 MxColor Mx_ImageGetPixel32Fast(MxImage * image, int x1, int y1);
	 MxImage *Mx_ImageCreate32(int w, int h);
#endif

	 int Mx_ImageWidth(MxImage * image);
	 int Mx_ImageHeight(MxImage * image);
	 int Mx_ImageDepth(MxImage * image);

	 int mx_igetw(FILE * f);
	 int mx_igetl(FILE * f);
	 int mx_mgetl(FILE * f);

#endif

#ifdef MX_NEED_GENERIC_DRAWING
	 void Mx_ImageVLineFast(struct MxImage *image, int x1, int y1, int y2, MxColor color, MxImagePixelFunc pixel);
	 void Mx_ImageHLineFast(struct MxImage *image, int x1, int y1, int y2, MxColor color, MxImagePixelFunc pixel);
	 void Mx_ImageRectFillFast(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color, Mx_ImageHLineFunc hline,
										MxImagePixelFunc pixel);

	 void Mx_ImageBlitFast(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h,
								  MxImageGetPixelFunc getpixel, MxImagePixelFunc pixel);
#endif

#ifdef __cplusplus
}
#endif
#endif
