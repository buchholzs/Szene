#include "depui/config.h"
#ifdef MX_IMAGE_SUPPORT_4

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/debug/alloc.h"
#include "depui/support/image.h"

#ifdef MX_DEBUG_IMAGE_AQUIRE
#include <assert.h>
#endif

void Mx_ImagePixel4Fast(MxImage * image, int x1, int y1, MxColor color)
{
	 unsigned char *ptr = &((unsigned char *) image->rows[y1])[x1 / 2];
	 const unsigned char temp = *ptr;

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 if (x1 & 0x01)
		  *ptr = (temp & 0x0f) | ((color << 4) & 0xf0);
	 else
		  *ptr = (temp & 0xf0) | (color & 0x0f);
}

MxColor Mx_ImageGetPixel4Fast(MxImage * image, int x1, int y1)
{
	 unsigned char *ptr = &((unsigned char *) image->rows[y1])[x1 / 2];

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 if (x1 & 0x01)
		  return ((*ptr) >> 4);

	 return ((*ptr) & 0x0f);
}

static void HLineFast(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel4Fast);
}

static void VLineFast(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel4Fast);
}

static void RectFillFast(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel4Fast);
}

static void _empty_aquire(struct MxImage *image)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
#endif

	 image->aquired = MxTrue;
	 image->wasaquired = MxTrue;
}

static void _empty_release(struct MxImage *image)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 image->aquired = MxFalse;
}

MxImageVTable MxVtable4 = {

	 Mx_ImageDestroy,

	 _empty_aquire,
	 _empty_release,

	 Mx_ImageWidth,
	 Mx_ImageHeight,
	 Mx_ImageDepth,

	 Mx_ImagePixel4Fast,
	 Mx_ImageGetPixel4Fast,

	 VLineFast,
	 HLineFast,

	 RectFillFast
};

MxImage *Mx_ImageCreate4(int w, int h)
{
	 return Mx_ImageCreateSimple(w, h, 4, &MxVtable4);
}

#else
extern int mx_ignore_this;

#endif
