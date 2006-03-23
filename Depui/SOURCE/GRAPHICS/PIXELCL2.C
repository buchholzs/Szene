#include "depui/config.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_get_pixel(struct MxImage *image, int x1, int y1, MxImageGetPixelFunc getpixel)
{
	 if (MxClipPixel(0, 0, MxScreenWidth(0), MxScreenHeight(0), x1, y1))
		  return 0;

	 return getpixel(image, x1, y1);
}

int mx_get_pixel_fast(struct MxImage *image, int x1, int y1, MxImageGetPixelFunc getpixel)
{
	 return getpixel(image, x1, y1);
}
