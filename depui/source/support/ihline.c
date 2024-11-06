#include "depui/config.h"
#ifdef MX_NEED_GENERIC_DRAWING

#include "depui/platform/platform.h"
#include "depui/support/image.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void Mx_ImageHLineFast(struct MxImage *image, int x1, int y1, int x2, MxColor color, MxImagePixelFunc pixel)
{
	 if (x1 > x2) {
		  int temp = x1;

		  x1 = x2;
		  x2 = temp;
	 }

	 while (x1 <= x2) {
		  pixel(image, x1, y1, color);
		  ++x1;
	 }
}

#else
extern int mx_ignore_this;

#endif
