#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxImagePixelTrans(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 assert(image);

	 if (MxClipPixel(0, 0, MxImageWidth(image), MxImageHeight(image), x1, y1))
		  return;

	 MxImagePixelTransFast(image, x1, y1, color, alpha);
}
