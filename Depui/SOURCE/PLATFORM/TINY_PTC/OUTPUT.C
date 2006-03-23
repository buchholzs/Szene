#include "depui/platform/platform.h"
#include "depui/support/font.h"
#include "depui/support/mouse.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
//#include "platform/tiny_ptc/tinyptc.h"
//#include "platform/tiny_ptc/tiny_ptc.h"

#warning Compiling DEPUI for TinyPTC

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static MxColor makecol(int r, int g, int b)
{
	 return b + (g << 8) + (r >> 16);
}

static MxImage *buffer = 0;

int mx_tinyptc_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 (void) c;
	 if (!ptc_open(title, x, y))
		  return 0;

	 buffer = Mx_ImageCreate32(x - 1, y - 1);
	 if (!buffer)
		  return 0;

	 driver->font = Mx_FontBuiltin;

	 driver->colors[MxForeIndex] = makecol(0, 0, 0);
	 driver->colors[MxBackIndex] = makecol(174, 174, 174);
	 driver->colors[MxObjectForeIndex] = makecol(0, 0, 0);
	 driver->colors[MxObjectBackIndex] = makecol(225, 225, 225);

	 driver->colors[MxSelectedForeIndex] = makecol(255, 255, 255);
	 driver->colors[MxSelectedBackIndex] = makecol(84, 124, 82);

	 driver->colors[MxLightIndex] = makecol(215, 215, 215);
	 driver->colors[MxMedIndex] = makecol(154, 154, 154);
	 driver->colors[MxDarkIndex] = makecol(114, 114, 114);
	 driver->colors[MxDesktopIndex] = makecol(92, 156, 69);
	 driver->colors[MxFocusIndex] = makecol(0, 255, 0);
	 driver->colors[MxDisabledIndex] = makecol(147, 147, 147);

	 return 1;
}

void mx_tinyptc_gfx_exit(void)
{
	 Mx_ImageDestroy(buffer);
	 ptc_close();
}

void mx_tinyptc_flush(void)
{
	 ptc_update(&(((UInt32 *) buffer->rows[0])[0]));
}

void mx_tinyptc_mouse_show(int show)
{
	 Mx_MouseShow(show, mx_tinyptc_screen_pixel, mx_tinyptc_screen_get_pixel);
}

MxColor mx_tinyptc_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_tinyptc_encode(int index, int r, int g, int b)
{
	 (void) index;
	 return b + (g << 8) + (r >> 16);
}

void mx_tinyptc_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_tinyptc_screen_pixel, mx_tinyptc_screen_get_pixel);
}

void mx_tinyptc_done_drawing_area(void)
{
	 Mx_MouseShow(1, mx_tinyptc_screen_pixel, mx_tinyptc_screen_get_pixel);
}

void mx_tinyptc_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_tinyptc_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

#ifdef MX_DEBUG_IMAGE_AQUIRE
#include <assert.h>

static unsigned int screen_aquired = MxFalse;

#endif

void mx_tinyptc_screen_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!screen_aquired);
	 screen_aquired = True;
#endif
}

void mx_tinyptc_screen_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
	 screen_aquired = MxFalse;
#endif
}

int mx_tinyptc_screen_width(struct MxImage *image)
{
	 (void) image;
	 return Mx_ImageWidth(buffer);
}

int mx_tinyptc_screen_height(struct MxImage *image)
{
	 (void) image;
	 return Mx_ImageHeight(buffer);
}

int mx_tinyptc_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return Mx_ImageDepth(buffer);
}

void mx_tinyptc_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImagePixel32Fast(buffer, x1, y1, color);
}

MxColor mx_tinyptc_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 return (MxColor) Mx_ImageGetPixel32Fast(buffer, x1, y1);
}

void mx_tinyptc_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 (void) image;
	 Mx_ImageHLineFast(buffer, x1, y1, x2, color, mx_tinyptc_screen_pixel);
}

void mx_tinyptc_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 (void) image;
	 Mx_ImageVLineFast(buffer, x1, y1, y2, color, mx_tinyptc_screen_pixel);
}

void mx_tinyptc_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 (void) image;
	 Mx_ImageRectFillFast(buffer, x1, y1, x2, y2, color, Mx_ImageHLineFast, mx_tinyptc_screen_pixel);
}

void mx_tinyptc_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImagePixel32Fast(buffer, x1, y1, _blend(color, Mx_ImageGetPixel32Fast(buffer, x1, y1), alpha));
}

struct MxImage *mx_tinyptc_image_create(int w, int h)
{
	 return Mx_ImageCreate32(w, h);
}

struct MxImage *mx_tinyptc_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_tinyptc_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = True;
#endif
}

void mx_tinyptc_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

void mx_tinyptc_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel32Fast);
}

void mx_tinyptc_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel32Fast);
}

void mx_tinyptc_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel32Fast);
}

void mx_tinyptc_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImagePixel32Fast(image, x1, y1, _blend(color, Mx_ImageGetPixel32Fast(image, x1, y1), alpha));
}

void mx_tinyptc_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(dest->aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel32Fast, Mx_ImagePixel32Fast);
}

void mx_tinyptc_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel32Fast, mx_tinyptc_screen_pixel);
}

void mx_tinyptc_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(dest->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_tinyptc_screen_get_pixel, Mx_ImagePixel32Fast);
}

void mx_tinyptc_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_tinyptc_screen_get_pixel, mx_tinyptc_screen_pixel);
}

void mx_tinyptc_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_tinyptc_screen_pixel);
}

struct MxFont *mx_tinyptc_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_tinyptc_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_tinyptc_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back)
{
	 int i;

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(buffer, text, font, x, y, color, back, _blend, s, Mx_ImagePixel32Fast,
													  mx_tinyptc_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(buffer, text, font, x, y, color, back, s, Mx_ImagePixel32Fast);
	 }
}

void mx_tinyptc_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, _blend, clip, Mx_ImagePixel32Fast,
												 mx_tinyptc_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel32Fast);
}

unsigned int mx_tinyptc_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_tinyptc_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
