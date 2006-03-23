/* Header for Generic graphics driver functions */
#ifndef MX_GRAPHICS_DRAW_H
#define MX_GRAPHICS_DRAW_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 void MxImagePixel(struct MxImage *, int x1, int y1, MxColor color);
	 MxColor MxImageGetPixel(struct MxImage *, int x1, int y1);
	 void MxImageHLine(struct MxImage *image, int x1, int y1, int x2, MxColor color);
	 void MxImageVLine(struct MxImage *image, int x1, int y1, int y2, MxColor color);
	 void MxImageRectFill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
	 void MxImagePixelTrans(struct MxImage *, int x1, int y1, MxColor color, int alpha);

	 void Mx_ScreenPixel(struct MxImage *, int x1, int y1, MxColor color);
	 MxColor Mx_ScreenGetPixel(struct MxImage *, int x1, int y1);
	 void Mx_ScreenHLine(struct MxImage *image, int x1, int y1, int x2, MxColor color);
	 void Mx_ScreenVLine(struct MxImage *image, int x1, int y1, int y2, MxColor color);
	 void Mx_ScreenRectFill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
	 void Mx_ScreenPixelTrans(struct MxImage *, int x1, int y1, MxColor color, int alpha);

	 void MxBlitImage(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
	 void MxBlitToScreen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
	 void MxBlitFromScreen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
	 void MxBlitScreen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

#ifdef __cplusplus
}
#endif
#endif
