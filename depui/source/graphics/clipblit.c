#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/platform/platform.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxClipBlit(int sx1, int sy1, int sw, int sh, int dx1, int dy1, int dw, int dh, int *sx, int *sy, int *dx, int *dy, int *w, int *h)
{
	 int sx2 = *sx + *w, sy2 = *sy + *h, dx2 = *dx + *w, dy2 = *dy + *h;

	 /* See if the blit is clipped by the edges of the source image */
	 if (MxClipRect(sx1, sy1, sw, sh, *sx, *sy, sx2, sy2))
		  return;

	 /* See if the blit is clipped by the edges of the dest image */
	 if (MxClipRect(dx1, dy1, dw, dh, *dx, *dy, dx2, dy2))
		  return;

	 /* Find the real width and height */
	 *w = MX_MIN(dx2 - *dx, sx2 - *sx);
	 *h = MX_MIN(dy2 - *dy, sy2 - *sy);
}
