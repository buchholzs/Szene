#include "depui/config.h"
#include "depui/graphics/clip.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_pixel(struct MxImage *image, int x1, int y1, MxColor color, const MxRect * const rect, MxImagePixelFunc pixel)
{
	 if (MxClipPixel(rect->x1, rect->y1, rect->x2, rect->y2, x1, y1))
		  return;

	 pixel(image, x1, y1, color);
}

void mx_pixel_fast(struct MxImage *image, int x1, int y1, MxColor color, const MxRect * const rect, MxImagePixelFunc pixel)
{
	 (void) rect;
	 pixel(image, x1, y1, color);
}
