#include "depui/config.h"
#ifdef MX_IMAGE_SUPPORT_24

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/debug/alloc.h"
#include "depui/support/image.h"

#ifdef MX_DEBUG_IMAGE_AQUIRE
#include <assert.h>
#endif

void Mx_ImagePixel24Fast(MxImage * image, int x1, int y1, MxColor color)
{
	 unsigned char *ptr = &((unsigned char *) image->rows[y1])[x1 * 3];

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 *(ptr++) = color;
	 *(ptr++) = color >> 8;
	 *ptr = color >> 16;
}

MxColor Mx_ImageGetPixel24Fast(MxImage * image, int x1, int y1)
{
	 unsigned char *ptr = &((unsigned char *) image->rows[y1])[x1 * 3];

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 return ptr[0] + (ptr[1] << 8) + (ptr[2] << 16);
}

static void HLineFast(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel24Fast);
}

static void VLineFast(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel24Fast);
}

static void RectFillFast(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel24Fast);
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

MxImageVTable MxVtable24 = {

	 Mx_ImageDestroy,

	 _empty_aquire,
	 _empty_release,

	 Mx_ImageWidth,
	 Mx_ImageHeight,
	 Mx_ImageDepth,

	 Mx_ImagePixel24Fast,
	 Mx_ImageGetPixel24Fast,

	 VLineFast,
	 HLineFast,

	 RectFillFast
};

MxImage *Mx_ImageCreate24(int w, int h)
{
	 return Mx_ImageCreateSimple(w, h, sizeof(unsigned char) * 24, &MxVtable24);
}

#else
extern int mx_ignore_this;

#endif
