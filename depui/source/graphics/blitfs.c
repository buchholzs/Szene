#include "depui/config.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxBlitFromScreen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 assert(dest);

	 MxClipBlit(0, 0, MxScreenWidth(0), MxScreenHeight(0), 0, 0, MxImageWidth(dest), MxImageHeight(dest), &sx, &sy, &dx, &dy, &w, &h);

	 MxBlitFromScreenFast(src, dest, sx, sy, dx, dy, w, h);
}
