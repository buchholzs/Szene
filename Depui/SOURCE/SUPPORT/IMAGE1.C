#include "depui/config.h"
#ifdef MX_IMAGE_SUPPORT_1

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/debug/alloc.h"
#include "depui/support/image.h"

#ifdef MX_DEBUG_IMAGE_AQUIRE
#include <assert.h>
#endif

void Mx_ImagePixel1Fast(MxImage * image, int x1, int y1, MxColor color)
{
	 UInt8 *ptr = &((UInt8 *) image->rows[y1])[x1 / 8];

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 switch (x1 & 0x07) {
	 case 0:
		  if (color)
				*ptr |= (1 << 0);
		  else
				*ptr &= ~(1 << 0);
		  return;

	 case 1:
		  if (color)
				*ptr |= (1 << 1);
		  else
				*ptr &= ~(1 << 1);
		  return;

	 case 2:
		  if (color)
				*ptr |= (1 << 2);
		  else
				*ptr &= ~(1 << 2);
		  return;

	 case 3:
		  if (color)
				*ptr |= (1 << 3);
		  else
				*ptr &= ~(1 << 3);
		  return;

	 case 4:
		  if (color)
				*ptr |= (1 << 4);
		  else
				*ptr &= ~(1 << 4);
		  return;

	 case 5:
		  if (color)
				*ptr |= (1 << 5);
		  else
				*ptr &= ~(1 << 5);
		  return;

	 case 6:
		  if (color)
				*ptr |= (1 << 6);
		  else
				*ptr &= ~(1 << 6);
		  return;

	 case 7:
		  if (color)
				*ptr |= (1 << 7);
		  else
				*ptr &= ~(1 << 7);
		  return;
	 }
	 /* we should never get here */
	 assert(0);
}

MxColor Mx_ImageGetPixel1Fast(MxImage * image, int x1, int y1)
{
	 UInt8 *ptr = &((UInt8 *) image->rows[y1])[x1 / 8];

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 switch (x1 & 0x07) {

	 case 0:
		  return ((*ptr) & (1 << 0));

	 case 1:
		  return ((*ptr) & (1 << 1)) >> 1;

	 case 2:
		  return ((*ptr) & (1 << 2)) >> 2;

	 case 3:
		  return ((*ptr) & (1 << 3)) >> 3;

	 case 4:
		  return ((*ptr) & (1 << 4)) >> 4;

	 case 5:
		  return ((*ptr) & (1 << 5)) >> 5;

	 case 6:
		  return ((*ptr) & (1 << 6)) >> 6;
	 }

	 return ((*ptr) & (1 << 7)) >> 7;
}

static void HLineFast(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel1Fast);
}

static void VLineFast(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel1Fast);
}

static void RectFillFast(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel1Fast);
}

static void _empty_aquire(struct MxImage *image)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
#endif

	 image->aquired = True;
	 image->wasaquired = True;
}

static void _empty_release(struct MxImage *image)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 image->aquired = False;
}

MxImageVTable MxVtable1 = {

	 Mx_ImageDestroy,

	 _empty_aquire,
	 _empty_release,

	 Mx_ImageWidth,
	 Mx_ImageHeight,
	 Mx_ImageDepth,

	 Mx_ImagePixel1Fast,
	 Mx_ImageGetPixel1Fast,

	 VLineFast,
	 HLineFast,

	 RectFillFast
};

MxImage *Mx_ImageCreate1(int w, int h)
{
	 return Mx_ImageCreateSimple(w, h, 1, &MxVtable1);
}

#else
extern int mx_ignore_this;

#endif
