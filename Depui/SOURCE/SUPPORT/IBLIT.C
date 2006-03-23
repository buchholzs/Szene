#include "depui/config.h"
#ifdef MX_NEED_GENERIC_DRAWING

#include "depui/platform/platform.h"
#include "depui/support/image.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void Mx_ImageBlitFast(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h,
							 MxImageGetPixelFunc getpixel, MxImagePixelFunc pixel)
{
	 int x, y;

	 if (src != dest) {
		  for (y = 0; y < h; y++) {
				for (x = 0; x < w; x++) {
					 pixel(dest, dx + x, dy + y, getpixel(src, sx + x, sy + y));
				}
		  }
		  /* source is same as dest, so we must think about what order to do
		     things in */
	 } else {
		  if (sx >= dx) {
				if (sy >= dy) {
					 /* Forward on both direction */
					 for (y = 0; y < h; y++) {
						  for (x = 0; x < w; x++) {
								pixel(dest, dx + x, dy + y, getpixel(src, sx + x, sy + y));
						  }
					 }
				} else {
					 /* Forward on X,backward on Y */
					 for (y = h - 1; y >= 0; y--) {
						  for (x = 0; x < w; x++) {
								pixel(dest, dx + x, dy + y, getpixel(src, sx + x, sy + y));
						  }
					 }
				}
		  } else {
				if (sy >= dy) {
					 /* Backward on X, forward on Y */
					 for (y = 0; y < h; y++) {
						  for (x = w - 1; x >= 0; x--) {
								pixel(dest, dx + x, dy + y, getpixel(src, sx + x, sy + y));
						  }
					 }
				} else {
					 /* backward on both directions */
					 for (y = h - 1; y >= 0; y--) {
						  for (x = w - 1; x >= 0; x--) {
								pixel(dest, dx + x, dy + y, getpixel(src, sx + x, sy + y));
						  }
					 }
				}
		  }
	 }
}

#else
extern int mx_ignore_this;

#endif
