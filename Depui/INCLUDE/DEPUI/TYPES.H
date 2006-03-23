#ifndef MX_TYPES_H
#define MX_TYPES_H

#include "depui/config.h"

#ifdef __cplusplus
extern "C" {
#endif
	 struct MxFont;
	 struct MxImage;
	 struct MxObject;
	 struct MxObjectArgs;
	 struct MxMenu;
	 struct MxWindow;
	 struct MxRegion;

	 typedef struct MxRect {
		  int x1;
		  int y1;
		  int x2;
		  int y2;
	 } MxRect;

#define MxFalse 0
#define MxTrue  0xffffffffl

	 typedef enum MxFontFlag { MxFontNoFlags = 0,
		  MxFontAntialiased = 1 << 0
	 } MxFontFlag;

	 typedef void (*MxCallback) (struct MxObject * object, void *data, unsigned int selected);

	 /* General New function for creation of objects */
	 typedef struct MxObject *(*MxNewFunc) (struct MxObject * parent, int x, int y, int w, int h, struct MxObjectArgs * args);

/* Some handy typedefs for graphic functions */
	 typedef void (*MxImageDestroyFunc) (struct MxImage * image);

	 typedef void (*MxImageAquireFunc) (struct MxImage * image);
	 typedef void (*MxImageReleaseFunc) (struct MxImage * image);

	 typedef int (*MxImageWidthFunc) (struct MxImage * image);
	 typedef int (*MxImageHeightFunc) (struct MxImage * image);
	 typedef int (*MxImageDepthFunc) (struct MxImage * image);

	 typedef void (*MxImagePixelFunc) (struct MxImage * image, int x1, int y1, MxColor color);
	 typedef MxColor(*MxImageGetPixelFunc) (struct MxImage * image, int x1, int y1);
	 typedef void (*MxImageHLineFunc) (struct MxImage * image, int x1, int y1, int x2, MxColor color);
	 typedef void (*MxImageVLineFunc) (struct MxImage * image, int x1, int y1, int x2, MxColor color);
	 typedef void (*MxImageLineFunc) (struct MxImage * image, int x1, int y1, int x2, int y2, MxColor color);
	 typedef void (*MxImageRectFillFunc) (struct MxImage * image, int x1, int y1, int x2, int y2, MxColor color);

	 typedef void (*MxImagePixelTransFunc) (struct MxImage * image, int x1, int y1, MxColor color, int alpha);

	 typedef MxColor(*MxBlendFunc) (MxColor fore, MxColor back, unsigned int alpha);
	 typedef MxColor(*MxColorFunc) (int cindex, int r, int g, int b);

	 typedef void (*Mx_ImageHLineFunc) (struct MxImage * image, int x1, int y1, int x2, MxColor color, MxImagePixelFunc pixel);

	 typedef void (*MxPixelClipFunc) (struct MxImage * image, int x1, int y1, MxColor color, const MxRect * const rect,
												 MxImagePixelFunc pixel);
	 typedef void (*MxPixelTransClipFunc) (struct MxImage * image, int x1, int y1, MxColor color, int alpha, const MxRect * const rect,
														MxImagePixelTransFunc pixel);

	 typedef int (*MxGetPixelClipFunc) (struct MxImage * image, int x1, int y1, MxImageGetPixelFunc getpixel);

	 typedef void (*MxVoidFunc) (void);

	 typedef int (*MxTabstopFunc) (const struct MxObject * object, const int tab);

	 typedef int (*MxChildSortFunc) (struct MxObject ** one, struct MxObject ** two);

#ifdef __cplusplus
}
#endif
#endif
