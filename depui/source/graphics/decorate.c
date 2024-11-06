#include "depui/config.h"
#include "depui/types.h"
#include "depui/graphics/decorate.h"
#include "depui/desktop/driver.h"
#include "depui/graphics/clip.h"
#include "depui/draw/region.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void Mx_Decorate(const MxDecoration * decoration, int x, int y, struct MxImage *image, MxImagePixelFunc pixel)
{
	 int i, j;
	 unsigned int r;
	 const unsigned char *ptr = &decoration->data[0];

	 for (j = y; j < y + decoration->height; j++) {
		  for (i = x; i < x + decoration->width; i++) {

				const unsigned int pix = *ptr++;

				if (pix) {

					 for (r = 0; r < MxRegionNumber(mx_region); r++) {
						  const MxRect *const s = MxRegionRect(mx_region, r);

						  if (!MxClipPixel(s->x1, s->y1, s->x2, s->y2, i, j)) {
								pixel(image, i, j, mx_output->colors[pix - 1]);
								break;
						  }
					 }
				}
		  }
	 }
}
