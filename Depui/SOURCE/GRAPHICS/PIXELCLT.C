#include "depui/config.h"
#include "depui/graphics/clip.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_pixel_trans(struct MxImage *image, int x1, int y1, MxColor color, int alpha, const MxRect * const rect,
						  MxImagePixelTransFunc trans)
{
	 if (MxClipPixel(rect->x1, rect->y1, rect->x2, rect->y2, x1, y1))
		  return;

	 trans(image, x1, y1, color, alpha);
}

void mx_pixel_trans_fast(struct MxImage *image, int x1, int y1, MxColor color, int alpha, const MxRect * const rect,
								 MxImagePixelTransFunc trans)
{
	 (void) rect;
	 trans(image, x1, y1, color, alpha);
}
