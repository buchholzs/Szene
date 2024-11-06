#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/support/font.h"
#include "depui/support/image.h"
#include "depui/support/mouse.h"
#include "depui/platform/opengui/opengui.h"
#include <fastgl/base.h>

#warning Compiling DEPUI for OpenGUI

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

typedef struct openguimode {
	 int m, x, y;
} openguimode;

static const openguimode modes[] = {
//   {   G320x200,      320,   200  },   /* This mode does not work for me */
	 {G640x480, 640, 480},
	 {G800x600, 800, 600},
	 {G1024x768, 1024, 768},
	 {G1600x1200, 1600, 1200},
	 {0, 0, 0}
};

int mx_opengui_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 const openguimode *mode = &modes[0];
	 int m = mode->m;

	 (void) c;
	 (void) title;

	 /* Look for a matching mode */
	 while (mode->x) {
		  if ((mode->x == x) && (mode->y == y))
				m = mode->m;
		  ++mode;
	 }

	 /* Initialize the mode */
	 if (graph_set_mode(m) == FALSE)
		  return 0;

	 driver->font = MxFontBuiltin;

	 driver->colors[MxForeIndex] = 1;
	 CreateColor(0, 0, 0, 1);
	 driver->colors[MxBackIndex] = 2;
	 CreateColor(174, 174, 174, 2);
	 driver->colors[MxObjectForeIndex] = 3;
	 CreateColor(0, 0, 0, 3);
	 driver->colors[MxObjectBackIndex] = 4;
	 CreateColor(225, 225, 225, 4);
	 driver->colors[MxSelectedForeIndex] = 5;
	 CreateColor(255, 255, 255, 5);
	 driver->colors[MxSelectedBackIndex] = 6;
	 CreateColor(84, 124, 182, 6);
	 driver->colors[MxLightIndex] = 7;
	 CreateColor(215, 215, 215, 7);
	 driver->colors[MxMedIndex] = 8;
	 CreateColor(154, 154, 154, 8);
	 driver->colors[MxDarkIndex] = 9;
	 CreateColor(114, 114, 114, 9);
	 driver->colors[MxDesktopIndex] = 10;
	 CreateColor(92, 156, 169, 10);
	 CreateColor(46, 78, 84, 10);
	 driver->colors[MxFocusIndex] = 11;
	 CreateColor(0, 255, 0, 11);
	 driver->colors[MxDisabledIndex] = 12;
	 CreateColor(147, 147, 147, 12);

	 return 1;
}

void mx_opengui_gfx_exit(void)
{
	 graph_set_mode(GTEXT);
}

void mx_opengui_flush(void)
{
}

void mx_opengui_mouse_show(const int show)
{
	 Mx_MouseShow(show, mx_opengui_screen_pixel, mx_opengui_screen_get_pixel);
}

MxColor mx_opengui_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_opengui_encode(int cindex, int r, int g, int b)
{
	 return CreateColor(r, g, b, cindex);
}

void mx_opengui_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_opengui_screen_pixel, mx_opengui_screen_get_pixel);
}

void mx_opengui_done_drawing_area(void)
{
	 Mx_MouseShow(1, mx_opengui_screen_pixel, mx_opengui_screen_get_pixel);
}

void mx_opengui_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_opengui_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_opengui_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_opengui_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_opengui_screen_width(struct MxImage *image)
{
	 (void) image;
	 return X_max;
}

int mx_opengui_screen_height(struct MxImage *image)
{
	 (void) image;
	 return Y_max;
}

int mx_opengui_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return 8;
}

void mx_opengui_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 set_fcolor(color);
	 draw_point(x1, y1);
}

MxColor mx_opengui_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
	 return get_point(x1, y1);
}

void mx_opengui_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;
	 set_fcolor(color);
	 draw_hline(x1, y1, x2 - x1 + 1);
}

void mx_opengui_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;
	 set_fcolor(color);
	 moveto(x1, y1);
	 drawto_line(x1, y2);
}

void mx_opengui_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 set_fcolor(color);
	 fill_box(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

void mx_opengui_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 const int c = mx_opengui_blend(mx_opengui_screen_get_pixel(image, x1, y1), color, alpha);

	 mx_opengui_screen_pixel(image, x1, y1, c);
}

struct MxImage *mx_opengui_image_create(int w, int h)
{
	 return Mx_ImageCreateDepth(w, h, 8);
}

struct MxImage *mx_opengui_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_opengui_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = True;
#endif
}

void mx_opengui_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

void mx_opengui_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel8Fast);
}

void mx_opengui_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel8Fast);
}

void mx_opengui_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel8Fast);
}

void mx_opengui_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImagePixel8Fast(image, x1, y1, mx_opengui_blend(color, Mx_ImageGetPixel8Fast(image, x1, y1), alpha));
}

void mx_opengui_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(dest->aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel8Fast, Mx_ImagePixel8Fast);
}

void mx_opengui_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel8Fast, mx_opengui_screen_pixel);
}

void mx_opengui_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(dest->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_opengui_screen_get_pixel, Mx_ImagePixel8Fast);
}

void mx_opengui_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_opengui_screen_get_pixel, mx_opengui_screen_pixel);
}

void mx_opengui_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_opengui_screen_pixel);
}

struct MxFont *mx_opengui_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_opengui_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_opengui_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back)
{
	 unsigned int i;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_opengui_blend, s, mx_opengui_screen_pixel,
													  mx_opengui_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(image, text, font, x, y, color, back, s, mx_opengui_screen_pixel);
	 }
}

void mx_opengui_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back)
{
	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_opengui_blend, clip, Mx_ImagePixel8Fast,
												 mx_opengui_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel8Fast);
}

unsigned int mx_opengui_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_opengui_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
