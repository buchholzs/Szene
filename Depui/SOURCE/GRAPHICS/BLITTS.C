#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"
#include "depui/draw/region.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxBlitToScreen(struct MxImage *src, struct MxImage *dest, int rsx, int rsy, int rdx, int rdy, int w, int h)
{
	 unsigned int i;

	 assert(src);

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  int sx = rsx, sy = rsy, dx = rdx, dy = rdy;

		  MxClipBlit(0, 0, MxImageWidth(src), MxImageHeight(src), s->x1, s->y1, s->x2, s->y2, &sx, &sy, &dx, &dy, &w, &h);

		  MxBlitToScreenFast(src, dest, sx, sy, dx, dy, w, h);
	 }
}
