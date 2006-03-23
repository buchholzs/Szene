#include "depui/config.h"
#include "depui/desktop/driver.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxImagePixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 assert(image);

	 if (MxClipPixel(0, 0, MxImageWidth(image), MxImageHeight(image), x1, y1))
		  return;

	 MxImagePixelFast(image, x1, y1, color);
}
