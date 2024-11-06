#include "depui/config.h"
#ifdef MX_NEED_GENERIC_DRAWING

#include "depui/platform/platform.h"
#include "depui/support/image.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void Mx_ImageRectFillFast(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color, Mx_ImageHLineFunc hline,
								  MxImagePixelFunc pixel)
{
	 while (y1 <= y2) {
		  hline(image, x1, y1, x2, color, pixel);
		  ++y1;
	 }
}

#else
extern int mx_ignore_this;

#endif
