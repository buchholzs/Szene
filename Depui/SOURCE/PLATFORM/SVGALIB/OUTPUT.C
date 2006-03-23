#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/support/font.h"
#include "depui/support/image.h"
#include "depui/support/mouse.h"
#include <vga.h>
#include <vgagl.h>

#warning Compiling DEPUI for Svgalib

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* A list of the valid video modes */
typedef struct mx_mode {
	 int mode;
	 int x, y, c;
} mx_mode;

static mx_mode modelist[] = {
	 {G320x200x256, 320, 200, 8},
	 {G320x200x32K, 320, 200, 15},
	 {G320x200x64K, 320, 200, 16},
	 {G320x200x16M, 320, 200, 24},

	 {G640x480x256, 640, 480, 8},
	 {G640x480x32K, 640, 480, 15},
	 {G640x480x64K, 640, 480, 16},
	 {G640x480x16M, 640, 480, 24},

	 {G800x600x256, 800, 600, 8},
	 {G800x600x32K, 800, 600, 15},
	 {G800x600x64K, 800, 600, 16},
	 {G800x600x16M, 800, 600, 24},

	 {G1024x768x256, 1024, 768, 8},
	 {G1024x768x32K, 1024, 768, 15},
	 {G1024x768x64K, 1024, 768, 16},
	 {G1024x768x16M, 1024, 768, 24},

	 {0, 0, 0, 0}
};

int mx_svgalib_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 int vgamode;

	 int defaultmode;
	 mx_mode *ptr = modelist;

	 (void) title;

	 vga_init();

	 /* Find the default mode */
	 defaultmode = vga_getdefaultmode();
	 if (defaultmode == -1)
		  defaultmode = G320x200x256;

	 /* Walk down the list of modes */
	 vgamode = defaultmode;
	 while ((ptr->mode) && (vgamode == defaultmode)) {

		  /* Does it match */
		  if ((ptr->x == x) && (ptr->y == y) && (ptr->c == c))
				vgamode = ptr->mode;

		  ++ptr;
	 }

	 vga_setmode(vgamode);
	 gl_setcontextvga(vgamode);  /* Physical screen context. */
//  physicalscreen = gl_allocatecontext();
//  gl_getcontext(physicalscreen);

	 if (COLORS == 256)
		  gl_setrgbpalette();

	 driver->font = MxFontBuiltin;

	 driver->colors[MxForeIndex] = gl_rgbcolor(0, 0, 0);
	 driver->colors[MxBackIndex] = gl_rgbcolor(174, 174, 174);
	 driver->colors[MxObjectForeIndex] = gl_rgbcolor(0, 0, 0);
	 driver->colors[MxObjectBackIndex] = gl_rgbcolor(225, 225, 225);

	 driver->colors[MxSelectedForeIndex] = gl_rgbcolor(255, 255, 255);
	 driver->colors[MxSelectedBackIndex] = gl_rgbcolor(84, 124, 82);

	 driver->colors[MxLightIndex] = gl_rgbcolor(215, 215, 215);
	 driver->colors[MxMedIndex] = gl_rgbcolor(154, 154, 154);
	 driver->colors[MxDarkIndex] = gl_rgbcolor(114, 114, 114);
	 driver->colors[MxDesktopIndex] = gl_rgbcolor(92, 156, 69);
	 driver->colors[MxFocusIndex] = gl_rgbcolor(0, 255, 0);
	 driver->colors[MxDisabledIndex] = gl_rgbcolor(147, 147, 147);

	 vga_setpage(0);
//    gl_enableclipping();
	 gl_disableclipping();

	 gl_setfont(8, 8, gl_font8x8);
	 gl_setwritemode(FONT_COMPRESSED + WRITEMODE_OVERWRITE);
	 gl_setfontcolors(0, vga_white());

	 return 1;
}

void mx_svgalib_gfx_exit(void)
{
//  if (virtual_mode)
//      gl_freecontext(backscreen);

	 vga_setmode(TEXT);
}

void mx_svgalib_flush(void)
{
}

void mx_svgalib_mouse_show(const int show)
{
	 Mx_MouseShow(show, mx_svgalib_screen_pixel, mx_svgalib_screen_get_pixel);
}

MxColor mx_svgalib_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_svgalib_encode(int index, int r, int g, int b)
{
	 (void) index;
	 return gl_rgbcolor(r, g, b);
}

void mx_svgalib_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_svgalib_screen_pixel, mx_svgalib_screen_get_pixel);
}

void mx_svgalib_done_drawing_area(void)
{
	 Mx_MouseShow(1, mx_svgalib_screen_pixel, mx_svgalib_screen_get_pixel);
}

void mx_svgalib_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_svgalib_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_svgalib_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_svgalib_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_svgalib_screen_width(struct MxImage *image)
{
	 (void) image;
	 return WIDTH - 1;
}

int mx_svgalib_screen_height(struct MxImage *image)
{
	 (void) image;
	 return HEIGHT - 1;
}

int mx_svgalib_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return BYTESPERPIXEL * 8;
}

void mx_svgalib_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 gl_setpixel(x1, y1, color);
}

MxColor mx_svgalib_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
	 return gl_getpixel(x1, y1);
}

void mx_svgalib_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;
	 gl_line(x1, y1, x2, y1, color);
}

void mx_svgalib_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;
	 gl_line(x1, y1, x1, y2, color);
}

void mx_svgalib_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 gl_fillbox(x1, y1, x2 - x1 + 1, y2 - y1 + 1, color);
}

void mx_svgalib_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
	 gl_setpixel(x1, y1, mx_svgalib_blend(gl_getpixel(x1, y1), color, alpha));
}

struct MxImage *mx_svgalib_image_create(int w, int h)
{
	 return Mx_ImageCreateDepth(w, h, 24);
}

struct MxImage *mx_svgalib_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_svgalib_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = True;
#endif
}

void mx_svgalib_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

void mx_svgalib_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
//  Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel24Fast);
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel24Fast);
}

void mx_svgalib_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel24Fast);
}

void mx_svgalib_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel24Fast);
}

void mx_svgalib_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImagePixel24Fast(image, x1, y1, mx_svgalib_blend(color, Mx_ImageGetPixel24Fast(image, x1, y1), alpha));
}

void mx_svgalib_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(dest->aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel24Fast, Mx_ImagePixel24Fast);
}

void mx_svgalib_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel24Fast, mx_svgalib_screen_pixel);
}

void mx_svgalib_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(dest->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_svgalib_screen_get_pixel, Mx_ImagePixel24Fast);
}

void mx_svgalib_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_svgalib_screen_get_pixel, mx_svgalib_screen_pixel);
}

void mx_svgalib_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_svgalib_screen_pixel);
}

struct MxFont *mx_svgalib_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_svgalib_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_svgalib_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back)
{
	 unsigned int i;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_svgalib_blend, s, mx_svgalib_screen_pixel,
													  mx_svgalib_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(image, text, font, x, y, color, back, s, mx_svgalib_screen_pixel);
	 }
}

void mx_svgalib_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back)
{
	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_svgalib_blend, clip, Mx_ImagePixel24Fast,
												 mx_svgalib_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel24Fast);
}

unsigned int mx_svgalib_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_svgalib_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
