#ifndef MX_GRAPHICS_CLIP_H
#define MX_GRAPHICS_CLIP_H

#include "depui/config.h"
#include "depui/macros.h"
#include "depui/types.h"
#include "depui/draw/region.h"

#ifdef __cplusplus
extern "C" {
#endif
	 extern MxRegion mx_region;
	 void MxClipRegion(const MxRegion * const region);

#define MxClipPixel(cx1, cy1, cx2, cy2, x1, y1) \
   ((((x1) < (cx1)) ||                             \
     ((x1) > (cx2)) ||                             \
     ((y1) < (cy1)) ||                             \
     ((y1) > (cy2)))                               \
     ? 1 : 0)

#define MxClipVLine(cx1, cy1, cx2, cy2, x1, y1, y2) \
   (((x1 < cx1) ||                                                    \
     (x1 > cx2) ||                                                    \
     (((y2) = MX_MIN((y2), (cy2))) < ((y1) = MX_MAX((y1), (cy1)))))   \
     ? 1 : 0)

#define MxClipHLine(cx1, cy1, cx2, cy2, x1, y1, x2) \
   (((y1 < cy1) ||                                                  \
     (y1 > cy2) ||                                                  \
     (((x2) = MX_MIN((x2), (cx2))) < ((x1) = MX_MAX((x1), (cx1))))) \
     ? 1 : 0)

#define MxClipRect(cx1, cy1, cx2, cy2, x1, y1, x2, y2) \
   (((((x2) = MX_MIN((x2), (cx2))) < ((x1) = MX_MAX((x1), (cx1)))) || \
     (((y2) = MX_MIN((y2), (cy2))) < ((y1) = MX_MAX((y1), (cy1)))))   \
     ? 1 : 0)

/* Ask if a rectangle will be clipped */
#define MxRectClipped(cx1, cy1, cx2, cy2, x1, y1, x2, y2) \
   (((x1 < cx1) || \
     (x2 > cx2) || \
     (x1 > x2)  || \
     (y1 < cy1) || \
     (y2 > cy2) || \
     (y1 > y2))    \
     ? 1 : 0)

	 void MxClipBlit(int sx1, int sy1, int sw, int sh, int dx1, int dx2, int dw, int dh, int *sx, int *sy, int *dx, int *dy, int *w,
						  int *h);

	 void mx_pixel(struct MxImage *image, int x1, int y1, MxColor color, const MxRect * const rect, MxImagePixelFunc pixel);
	 void mx_pixel_fast(struct MxImage *image, int x1, int y1, MxColor color, const MxRect * const rect, MxImagePixelFunc pixel);

	 void mx_pixel_trans(struct MxImage *image, int x1, int y1, MxColor color, int alpha, const MxRect * const rect,
								MxImagePixelTransFunc trans);
	 void mx_pixel_trans_fast(struct MxImage *image, int x1, int y1, MxColor color, int alpha, const MxRect * const rect,
									  MxImagePixelTransFunc trans);

	 int mx_get_pixel(struct MxImage *image, int x1, int y1, MxImageGetPixelFunc getpixel);
	 int mx_get_pixel_fast(struct MxImage *image, int x1, int y1, MxImageGetPixelFunc getpixel);

#ifdef __cplusplus
}
#endif
#endif
