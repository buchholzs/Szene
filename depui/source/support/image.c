#include "depui/config.h"
#ifdef MX_NEED_IMAGE

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/macros.h"
#include "depui/types.h"
#include "depui/debug/alloc.h"
#include "depui/support/image.h"
#include "depui/platform/platform.h"

void Mx_ImageConstructSimple(MxImage * image, int w, int h, int bits, MxImageVTable * vtable)
{
	 int i;
	 unsigned char *ptr;
	 unsigned char **row;

	 assert(image);
	 assert(vtable);

	 image->w = w;
	 image->h = h;
	 image->c = bits;
	 image->vtable = vtable;
	 image->allocated = MxFalse;

	 /* Point to the first rows */
	 row = (unsigned char **) &image->rows;

	 /* Start after the row pointers */
	 ptr = (unsigned char *) &(row[h + 1]);

	 /* Fill in the row pointers */
	 for (i = 0; i <= h; i++) {

		  row[i] = ptr;

		  /* Go to the next row */
		  ptr += _MXIMAGEBYTESPERROW(w, bits);
	 }
}

MxImage *Mx_ImageCreateSimple(int w, int h, int bits, MxImageVTable * vtable)
{
	 const unsigned int bytes = MXIMAGEBYTES(w, h, bits);
	 MxImage *image = (MxImage *) MxMalloc(bytes);

	 if (image) {
		  Mx_ImageConstructSimple(image, w, h, bits, vtable);
		  image->allocated = 1;
	 }

	 return image;
}

MxImage *Mx_ImageCreateDepth(int w, int h, int bits)
{
	 switch (bits) {

#ifdef MX_IMAGE_SUPPORT_1
	 case 1:
		  return Mx_ImageCreate1(w, h);
#endif

#ifdef MX_IMAGE_SUPPORT_4
	 case 4:
		  return Mx_ImageCreate4(w, h);
#endif

#ifdef MX_IMAGE_SUPPORT_8
	 case 8:
		  return Mx_ImageCreate8(w, h);
#endif

#ifdef MX_IMAGE_SUPPORT_16
	 case 16:
		  return Mx_ImageCreate16(w, h);
#endif

#ifdef MX_IMAGE_SUPPORT_24
	 case 24:
		  return Mx_ImageCreate24(w, h);
#endif

#ifdef MX_IMAGE_SUPPORT_32
	 case 32:
		  return Mx_ImageCreate32(w, h);
#endif

	 }
	 /* Requested image depth is not known */
	 return 0;
}

void Mx_ImageDestroy(MxImage * image)
{
	 assert(image);

	 if (image->allocated)
		  MxFree(image);
	 image->allocated = 0;
}

int Mx_ImageWidth(MxImage * image)
{
	 assert(image);
	 return image->w;
}

int Mx_ImageHeight(MxImage * image)
{
	 assert(image);
	 return image->h;
}

int Mx_ImageDepth(MxImage * image)
{
	 assert(image);
	 return image->c;
}

/*
void Mx_ImageClip(MxImage * image, int x1, int y1, int x2, int y2)
{
    image->clipx1 = x1;
    image->clipy1 = y1;
    image->clipx2 = x2;
    image->clipy2 = y2;
}

void Mx_ImageClipGet(MxImage * image, int *x1, int *y1, int *x2, int *y2)
{
    *x1 = image->clipx1;
    *y1 = image->clipy1;
    *x2 = image->clipx2;
    *y2 = image->clipy2;
}
*/

#else
extern int mx_ignore_this;

#endif
