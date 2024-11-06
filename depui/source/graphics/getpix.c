#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

MxColor MxImageGetPixel(struct MxImage *image, int x1, int y1)
{
	 assert(image);

	 if (MxClipPixel(0, 0, MxImageWidth(image), MxImageHeight(image), x1, y1))
		  return 0;

	 return MxImageGetPixelFast(image, x1, y1);
}
