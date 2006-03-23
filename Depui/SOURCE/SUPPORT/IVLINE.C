#include "depui/config.h"
#ifdef MX_NEED_GENERIC_DRAWING

#include "depui/platform/platform.h"
#include "depui/support/image.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void Mx_ImageVLineFast(struct MxImage *image, int x1, int y1, int y2, MxColor color, MxImagePixelFunc pixel)
{
	 if (y1 > y2) {
		  int temp = y1;

		  y1 = y2;
		  y2 = temp;
	 }

	 while (y1 <= y2) {
		  pixel(image, x1, y1, color);
		  ++y1;
	 }
}

#else
extern int mx_ignore_this;

#endif
