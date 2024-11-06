#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/support/font.h"
#include "depui/support/image.h"
#include "depui/support/mouse.h"

#warning Compiling DEPUI for PORT

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_port_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 /* ^^^ Initialize the video mode here ^^^ */

	 driver->font = MxFontBuiltin;

	 /* ^^^ Set some system colors here ^^^ */
	 driver->colors[MxForeIndex] = 1;
	 driver->colors[MxBackIndex] = 2;
	 driver->colors[MxObjectForeIndex] = 3;
	 driver->colors[MxObjectBackIndex] = 4;

	 driver->colors[MxSelectedForeIndex] = 5;
	 driver->colors[MxSelectedBackIndex] = 6;

	 driver->colors[MxLightIndex] = 7;
	 driver->colors[MxMedIndex] = 8;
	 driver->colors[MxDarkIndex] = 9;
	 driver->colors[MxDesktopIndex] = 10;
	 driver->colors[MxFocusIndex] = 11;
	 driver->colors[MxDisabledIndex] = 12;

	 return 1;
}

void mx_port_gfx_exit(void)
{
	 /* ^^^ Close down any graphics mode here ^^^ */
}

void mx_port_flush(void)
{
}

void mx_port_mouse_show(const int show)
{
	 Mx_MouseShow(show, mx_port_screen_pixel, mx_port_screen_get_pixel);
}

MxColor mx_port_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_port_encode(int index, int r, int g, int b)
{
	 (void) r;
	 (void) g;
	 (void) b;
	 return index;
}

void mx_port_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_port_screen_pixel, mx_port_screen_get_pixel);
}

void mx_port_done_drawing_area(void)
{
	 Mx_MouseShow(1, mx_port_screen_pixel, mx_port_screen_get_pixel);
}

void mx_port_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_port_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_port_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_port_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_port_screen_width(struct MxImage *image)
{
	 (void) image;
	 /* ^^^ Return the screen width ^^^ */
	 return 320;
}

int mx_port_screen_height(struct MxImage *image)
{
	 (void) image;
	 /* ^^^ Return the screen height ^^^ */
	 return 200;
}

int mx_port_screen_depth(struct MxImage *image)
{
	 (void) image;
	 /* ^^^ Return the screen color depth ^^^ */
	 return 8;
}

void mx_port_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 /* ^^^ Plot a screen pixel here ^^^ */
}

MxColor mx_port_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
	 /* ^^^ Read a screen pixel here ^^^ */
}

void mx_port_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 Mx_ImageHLineFast(image, x1, y1, x2, color, mx_port_screen_pixel);
}

void mx_port_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 Mx_ImageVLineFast(image, x1, y1, y2, color, mx_port_screen_pixel);
}

void mx_port_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, mx_port_screen_pixel);
}

void mx_port_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 const int c = mx_port_blend(mx_port_screen_get_pixel(image, x1, y1), color, alpha);

	 mx_port_screen_pixel(image, x1, y1, c);
}

struct MxImage *mx_port_image_create(int w, int h)
{
	 return Mx_ImageCreateDepth(w, h, 24);
}

struct MxImage *mx_port_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_port_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = True;
#endif
}

void mx_port_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

void mx_port_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel24Fast);
}

void mx_port_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel24Fast);
}

void mx_port_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel24Fast);
}

void mx_port_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImagePixel24Fast(image, x1, y1, mx_port_blend(color, Mx_ImageGetPixel24Fast(image, x1, y1), alpha));
}

void mx_port_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(dest->aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel24Fast, Mx_ImagePixel24Fast);
}

void mx_port_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel24Fast, mx_port_screen_pixel);
}

void mx_port_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(dest->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_port_screen_get_pixel, Mx_ImagePixel24Fast);
}

void mx_port_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_port_screen_get_pixel, mx_port_screen_pixel);
}

void mx_port_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_port_screen_pixel);
}

struct MxFont *mx_port_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_port_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_port_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
										  MxColor back)
{
	 unsigned int i;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_port_blend, s, mx_port_screen_pixel,
													  mx_port_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(image, text, font, x, y, color, back, s, mx_port_screen_pixel);
	 }
}

void mx_port_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
										 int y, MxColor color, MxColor back)
{
	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_port_blend, clip, Mx_ImagePixel24Fast,
												 mx_port_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel24Fast);
}

unsigned int mx_port_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_port_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
