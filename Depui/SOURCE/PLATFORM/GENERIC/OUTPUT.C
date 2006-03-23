#include "depui/platform/platform.h"
#include "depui/support/font.h"
#include "depui/support/mouse.h"
#include "depui/graphics/draw.h"
#include "depui/draw/region.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/platform/generic/generic.h"
#include <allegro.h>

#warning Compiling DEPUI for Generic(Allegro)

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_generic_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 int ret;

	 (void) title;

	 allegro_init();

	 /* Force 16 bit for now */
	 c = 16;
	 set_color_depth(c);

#ifdef __DJGPP__
	 ret = set_gfx_mode(GFX_AUTODETECT, x, y, 0, 0);
#else
	 ret = set_gfx_mode(GFX_SAFE, x, y, 0, 0);
#endif

	 /* Returned value *less than zero* means failure */
	 if (ret >= 0) {

		  text_mode(-1);
		  show_mouse(NULL);
		  set_clip(screen, 0, 0, SCREEN_W, SCREEN_H);

		  driver->font = MxFontBuiltin;
//        driver->font = MxFontBuiltin8x8;
//        driver->font = MxFontBuiltinTimes;
//        driver->font = MxFontBuiltinArial;

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
	 }
	 return (ret >= 0);
}

void mx_generic_gfx_exit(void)
{
	 allegro_exit();
}

void mx_generic_flush(void)
{
}

void mx_generic_mouse_show(int show)
{
	 Mx_MouseShow(show, mx_generic_screen_pixel, mx_generic_screen_get_pixel);
}

MxColor mx_generic_blend(MxColor xx, MxColor yy, unsigned int n)
{
	 unsigned int result;

	 unsigned long x = xx;
	 unsigned long y = yy;

	 if (n)
		  n = (n + 1) / 8;

	 x = ((x & 0xFFFF) | (x << 16)) & 0x7E0F81F;
	 y = ((y & 0xFFFF) | (y << 16)) & 0x7E0F81F;

	 result = ((x - y) * n / 32 + y) & 0x7E0F81F;

	 return ((result & 0xFFFF) | (result >> 16));
}

MxColor mx_generic_encode(int index, int r, int g, int b)
{
	 (void) index;
	 return makecol(r, g, b);
}

void mx_generic_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_generic_screen_pixel, mx_generic_screen_get_pixel);
}

void mx_generic_done_drawing_area(void)
{
	 Mx_MouseShow(1, mx_generic_screen_pixel, mx_generic_screen_get_pixel);
}

void mx_generic_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_generic_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

#ifdef MX_DEBUG_IMAGE_AQUIRE
#include <assert.h>

static unsigned int screen_aquired = MxFalse;

#endif

void mx_generic_screen_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!screen_aquired);
	 screen_aquired = MxTrue;
#endif
}

void mx_generic_screen_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
	 screen_aquired = MxFalse;
#endif
}

int mx_generic_screen_width(struct MxImage *image)
{
	 (void) image;
	 return SCREEN_W - 1;
}

int mx_generic_screen_height(struct MxImage *image)
{
	 (void) image;
	 return SCREEN_H - 1;
}

int mx_generic_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return 16;
}

void mx_generic_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 _putpixel16(screen, x1, y1, color);
}

MxColor mx_generic_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 return (MxColor) _getpixel16(screen, x1, y1);
}

void mx_generic_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, mx_generic_screen_pixel);
}

void mx_generic_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, mx_generic_screen_pixel);
}

void mx_generic_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, mx_generic_screen_pixel);
}

void mx_generic_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 _putpixel16(screen, x1, y1, mx_generic_blend(color, _getpixel16(screen, x1, y1), alpha));
}

struct MxImage *mx_generic_image_create(int w, int h)
{
	 return Mx_ImageCreateDepth(w, h, 16);
}

struct MxImage *mx_generic_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_generic_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = MxTrue;
#endif
}

void mx_generic_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

void mx_generic_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel16Fast);
}

void mx_generic_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel16Fast);
}

void mx_generic_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel16Fast);
}

void mx_generic_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImagePixel16Fast(image, x1, y1, mx_generic_blend(color, Mx_ImageGetPixel16Fast(image, x1, y1), alpha));
}

void mx_generic_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(dest->aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel16Fast, Mx_ImagePixel16Fast);
}

void mx_generic_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel16Fast, mx_generic_screen_pixel);
}

void mx_generic_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(dest->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_generic_screen_get_pixel, Mx_ImagePixel16Fast);
}

void mx_generic_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_generic_screen_get_pixel, mx_generic_screen_pixel);
}

void mx_generic_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_generic_screen_pixel);
}

struct MxFont *mx_generic_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_generic_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_generic_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back)
{
	 unsigned int i;

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_generic_blend, s, mx_generic_screen_pixel,
													  mx_generic_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(image, text, font, x, y, color, back, s, mx_generic_screen_pixel);
	 }
}

void mx_generic_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_generic_blend, clip, Mx_ImagePixel16Fast,
												 mx_generic_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel16Fast);
}

unsigned int mx_generic_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_generic_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
