#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"
#include "depui/draw/region.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void Mx_ScreenPixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 unsigned int i;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (!MxClipPixel(s->x1, s->y1, s->x2, s->y2, x1, y1)) {
				MxScreenPixelFast(image, x1, y1, color);

				/* The pixel can only be in one of the regions rect */
				return;
		  }
	 }
}
