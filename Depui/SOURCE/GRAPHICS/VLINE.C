#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxImageVLine(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 assert(image);

	 if (MxClipVLine(0, 0, MxImageWidth(image), MxImageHeight(image), x1, y1, y2))
		  return;

	 MxImageVLineFast(image, x1, y1, y2, color);
}
