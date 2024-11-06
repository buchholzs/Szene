#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxImageHLine(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 assert(image);

	 if (MxClipHLine(0, 0, MxImageWidth(image), MxImageHeight(image), x1, y1, x2))
		  return;

	 MxImageHLineFast(image, x1, y1, x2, color);
}
