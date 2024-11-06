#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/platform/borland/bgi/bgi.h"
#include <graphics.h>
#include <dos.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_borland_bgi_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 int gdriver = DETECT, gmode = VGAHI;

	 (void) x;
	 (void) y;
	 (void) c;

	 initgraph(&gdriver, &gmode, "");

	 setviewport(0, 0, getmaxx(), getmaxy(), 0);

	 cleardevice();
	 setlinestyle(SOLID_LINE, 0, 1);

	 driver->font = MxFontBuiltin;

	 driver->colors[MxForeIndex] = EGA_BLACK;
	 driver->colors[MxBackIndex] = EGA_LIGHTGRAY;
	 driver->colors[MxObjectForeIndex] = EGA_BLACK;
	 driver->colors[MxObjectBackIndex] = EGA_WHITE;
	 driver->colors[MxSelectedForeIndex] = EGA_BLACK;
	 driver->colors[MxSelectedBackIndex] = EGA_GREEN;
	 driver->colors[MxLightIndex] = EGA_WHITE;
	 driver->colors[MxMedIndex] = EGA_CYAN;
	 driver->colors[MxDarkIndex] = EGA_BLACK;
	 driver->colors[MxDesktopIndex] = EGA_BLUE;
	 driver->colors[MxFocusIndex] = EGA_YELLOW;
	 driver->colors[MxDisabledIndex] = EGA_LIGHTRED;

	 return 1;
}

void mx_borland_bgi_gfx_exit(void)
{
	 closegraph();
}

void mx_borland_bgi_flush(void)
{
}

void mx_borland_bgi_mouse_show(int show)
{
	 union REGS regs;

	 regs.x.ax = show ? 0x0001 : 0x0002;
	 int86(0x33, &regs, &regs);
}

MxColor mx_borland_bgi_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_borland_bgi_encode(int index, int r, int g, int b)
{
	 int code = 0;

	 (void) index;

	 if (r + b + g > 384)
		  code |= 8;
	 if (-r + b + g > 127)
		  code |= 4;
	 if (r - b + g > 127)
		  code |= 2;
	 if (r + b - g > 127)
		  code |= 1;
	 return code;
}

void mx_borland_bgi_drawing_area(int x1, int y1, int x2, int y2)
{
	 union REGS regs;

	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;

	 regs.x.ax = 0x0002;
	 int86(0x33, &regs, &regs);
}

void mx_borland_bgi_done_drawing_area(void)
{
	 union REGS regs;

	 regs.x.ax = 0x0001;
	 int86(0x33, &regs, &regs);
}

void mx_borland_bgi_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_borland_bgi_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_borland_bgi_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_borland_bgi_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_borland_bgi_screen_width(struct MxImage *image)
{
	 (void) image;
	 return getmaxx();
}

int mx_borland_bgi_screen_height(struct MxImage *image)
{
	 (void) image;
	 return getmaxy();
}

int mx_borland_bgi_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return 4;
}

void mx_borland_bgi_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 putpixel(x1, y1, color);
}

MxColor mx_borland_bgi_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
	 return (MxColor) getpixel(x1, y1);
}

void mx_borland_bgi_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;
	 setcolor(color);
	 line(x1, y1, x2, y1);
}

void mx_borland_bgi_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;
	 setcolor(color);
	 line(x1, y1, x1, y2);
}

void mx_borland_bgi_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 setfillstyle(SOLID_FILL, color);
	 bar(x1, y1, x2, y2);
}

void mx_borland_bgi_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
	 (void) alpha;
	 putpixel(x1, y1, color);
}

struct MxImage *mx_borland_bgi_image_create(int w, int h)
{
	 return Mx_ImageCreateDepth(w, h, 4);
}

struct MxImage *mx_borland_bgi_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_borland_bgi_image_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_borland_bgi_image_release(struct MxImage *image)
{
	 (void) image;
}

void mx_borland_bgi_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel4Fast);
}

void mx_borland_bgi_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel4Fast);
}

void mx_borland_bgi_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel4Fast);
}

void mx_borland_bgi_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 Mx_ImagePixel4Fast(image, x1, y1, mx_borland_bgi_blend(color, Mx_ImageGetPixel4Fast(image, x1, y1), alpha));
}

void mx_borland_bgi_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel4Fast, Mx_ImagePixel4Fast);
}

void mx_borland_bgi_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel4Fast, mx_borland_bgi_screen_pixel);
}

void mx_borland_bgi_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_borland_bgi_screen_get_pixel, Mx_ImagePixel4Fast);
}

void mx_borland_bgi_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_borland_bgi_screen_get_pixel, mx_borland_bgi_screen_pixel);
}

void mx_borland_bgi_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_borland_bgi_screen_pixel);
}

struct MxFont *mx_borland_bgi_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_borland_bgi_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_borland_bgi_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
													MxColor back)
{
	 int i;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_borland_bgi_blend, s, mx_borland_bgi_screen_pixel,
													  mx_borland_bgi_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(image, text, font, x, y, color, back, s, mx_borland_bgi_screen_pixel);
	 }
}

void mx_borland_bgi_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font,
												  int x, int y, MxColor color, MxColor back)
{
	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, mx_borland_bgi_blend, clip, Mx_ImagePixel4Fast,
												 mx_borland_bgi_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel4Fast);
}

unsigned int mx_borland_bgi_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_borland_bgi_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
