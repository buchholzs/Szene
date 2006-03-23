#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"
#include "depui/draw/region.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void Mx_ScreenVLine(struct MxImage *image, int rx1, int ry1, int ry2, MxColor color)
{
	 unsigned int i;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  int x1 = rx1, y1 = ry1, y2 = ry2;

		  if (!MxClipVLine(s->x1, s->y1, s->x2, s->y2, x1, y1, y2))
				MxScreenVLineFast(image, x1, y1, y2, color);
	 }
}
