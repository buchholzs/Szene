#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/support/font.h"
#include "depui/support/image.h"
#include <grx20.h>
#include <grxkeys.h>

#ifdef __MSDOS__
#pragma warning Compiling DEPUI for DOS/GRX
#else
#pragma warning Compiling DEPUI for Linux/GRX
#endif

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static int depth = 0;

static int screen_context;

int mx_grx_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 (void) title;

	 GrSetMode(GR_width_height_bpp_graphics, x, y, c);
	 depth = c;

	 GrMouseDetect();
	 GrMouseInit();
	 GrMouseEventEnable(0, 1);
	 GrMouseEraseCursor();

	 GrSetRGBcolorMode();

	 driver->font = (struct MxFont *) &GrDefaultFont;

	 driver->colors[MxForeIndex] = GrBuildRGBcolorT(0, 0, 0);
	 driver->colors[MxBackIndex] = GrBuildRGBcolorT(174, 174, 174);
	 driver->colors[MxObjectForeIndex] = GrBuildRGBcolorT(0, 0, 0);
	 driver->colors[MxObjectBackIndex] = GrBuildRGBcolorT(225, 225, 225);

	 driver->colors[MxSelectedForeIndex] = GrBuildRGBcolorT(255, 255, 255);
	 driver->colors[MxSelectedBackIndex] = GrBuildRGBcolorT(84, 124, 82);

	 driver->colors[MxLightIndex] = GrBuildRGBcolorT(215, 215, 215);
	 driver->colors[MxMedIndex] = GrBuildRGBcolorT(154, 154, 154);
	 driver->colors[MxDarkIndex] = GrBuildRGBcolorT(114, 114, 114);
	 driver->colors[MxDesktopIndex] = GrBuildRGBcolorT(92, 156, 69);
	 driver->colors[MxFocusIndex] = GrBuildRGBcolorT(0, 255, 0);
	 driver->colors[MxDisabledIndex] = GrBuildRGBcolorT(147, 147, 147);

	 GrSetContext(GrScreenContext());
	 screen_context = 1;

	 return 1;
}

void mx_grx_gfx_exit(void)
{
	 GrMouseUnInit();
	 GrSetMode(GR_default_text);
}

void mx_grx_flush(void)
{
}

void mx_grx_mouse_show(const int show)
{
  Mx_MouseShow(show, mx_grx_screen_pixel, mx_grx_screen_get_pixel);
}

MxColor mx_grx_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_grx_encode(int index, int r, int g, int b)
{
	 (void) index;
	 return GrBuildRGBcolorT(r, g, b);
}

void mx_grx_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_grx_screen_pixel, mx_grx_screen_get_pixel);
}

void mx_grx_done_drawing_area(void)
{
  Mx_MouseShow(1, mx_grx_screen_pixel, mx_grx_screen_get_pixel);
}

void mx_grx_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_grx_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_grx_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_grx_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_grx_screen_width(struct MxImage *image)
{
	 (void) image;
	 return GrScreenX();
}

int mx_grx_screen_height(struct MxImage *image)
{
	 (void) image;
	 return GrScreenY();
}

int mx_grx_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return depth;
}

void mx_grx_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;

	 if (!screen_context) {
		  GrSetContext(GrScreenContext());
		  screen_context = 1;
	 }
	// GrPlotNC(x1, y1, color);
    GrPlot(x1, y1, color);
}

MxColor mx_grx_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;

	 if (!screen_context) {
		  GrSetContext(GrScreenContext());
		  screen_context = 1;
	 }
	 return GrPixelNC(x1, y1);
//  return GrPixel(x1, y1);
}

void mx_grx_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;

	 if (!screen_context) {
		  GrSetContext(GrScreenContext());
		  screen_context = 1;
	 }
	 GrHLineNC(x1, x2, y1, color);
//  GrHLine(x1, x2, y1, color);
}

void mx_grx_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;

	 if (!screen_context) {
		  GrSetContext(GrScreenContext());
		  screen_context = 1;
	 }
	 GrVLineNC(x1, y1, y2, color);
//  GrVLine(x1, y1, y2, color);
}

void mx_grx_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;

	 if (!screen_context) {
		  GrSetContext(GrScreenContext());
		  screen_context = 1;
	 }
	 GrFilledBoxNC(x1, y1, x2, y2, color);
//  GrFilledBox(x1, y1, x2, y2, color);
}

void mx_grx_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;

	 if (!screen_context) {
		  GrSetContext(GrScreenContext());
		  screen_context = 1;
	 }
	 GrPlotNC(x1, y1, mx_grx_blend(color, GrPixelNC(x1, y1), alpha));
//  GrPlot(x1, y1, mx_grx_blend(color, GrPixel(x1, y1), alpha));
}

struct MxImage *mx_grx_image_create(int w, int h)
{
	 return (struct MxImage *) GrCreateContext(w, h, 0, 0);
}

struct MxImage *mx_grx_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_grx_image_destroy(struct MxImage *image)
{
	 GrDestroyContext((GrContext *) image);
}

void mx_grx_image_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_grx_image_release(struct MxImage *image)
{
	 (void) image;
}

int mx_grx_image_width(struct MxImage *image)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 return GrMaxX();
}

int mx_grx_image_height(struct MxImage *image)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 return GrMaxY();
}

int mx_grx_image_depth(struct MxImage *image)
{
	 (void) image;

	 return depth;
}

void mx_grx_image_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 GrPlotNC(x1, y1, color);
//  GrPlot(x1, y1, color);
}

MxColor mx_grx_image_get_pixel(struct MxImage *image, int x1, int y1)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 return GrPixelNC(x1, y1);
//  return GrPixel(x1, y1);
}

void mx_grx_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 GrHLineNC(x1, x2, y1, color);
//  GrHLine(x1, x2, y1, color);
}

void mx_grx_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 GrVLineNC(x1, y1, y2, color);
//  GrVLine(x1, y1, y2, color);
}

void mx_grx_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 GrFilledBoxNC(x1, y1, x2, y2, color);
//  GrFilledBox(x1, y1, x2, y2, color);
}

void mx_grx_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }
	 GrPlotNC(x1, y1, mx_grx_blend(color, GrPixelNC(x1, y1), alpha));
//  GrPlot(x1, y1, mx_grx_blend(color, GrPixel(x1, y1), alpha));
}

void mx_grx_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
//    GrBitBltNC((GrContext*)dest, dx, dy, (GrContext*)src, sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
	 GrBitBlt((GrContext *) dest, dx, dy, (GrContext *) src, sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
}

void mx_grx_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) dest;

	 GrBitBltNC(GrScreenContext(), dx, dy, (GrContext *) src, sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
//  GrBitBlt(GrScreenContext(), dx, dy, (GrContext *) src, sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
}

void mx_grx_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;

	 GrBitBltNC((GrContext *) dest, dx, dy, GrScreenContext(), sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
//  GrBitBlt((GrContext *) dest, dx, dy, GrScreenContext(), sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
}

void mx_grx_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 (void) dest;

	 GrBitBltNC(GrScreenContext(), dx, dy, GrScreenContext(), sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
//  GrBitBlt(GrScreenContext(), dx, dy, GrScreenContext(), sx, sy, sx + w - 1, sy + h - 1, GrWRITE);
}

void mx_grx_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_grx_screen_pixel);
}

struct MxFont *mx_grx_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) points;
	 (void) flags;
	 return (struct MxFont *) GrLoadFont((char *) name);
}

void mx_grx_font_destroy(struct MxFont *f)
{
	 if (f != (struct MxFont *) &GrDefaultFont)
		  GrUnloadFont((GrFont *) f);
}

void mx_grx_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
										 MxColor back)
{
	 unsigned int i;
	 const int len = strlen(text);

	 GrTextOption option;

	 (void) image;

	 option.txo_font = (GrFont *) font;
	 option.txo_fgcolor.v = color;
	 option.txo_bgcolor.v = back;
	 option.txo_chrtype = GR_BYTE_TEXT;
	 option.txo_direct = GR_TEXT_RIGHT;
	 option.txo_xalign = GR_ALIGN_DEFAULT;
	 option.txo_yalign = GR_ALIGN_DEFAULT;

	 if (!screen_context) {
		  GrSetContext(GrScreenContext());
		  screen_context = 1;
	 }

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  GrSetClipBox(s->x1, s->y1, s->x2, s->y2);

		  GrDrawString((char *) text, len, x, y, &option);
	 }
	 GrResetClipBox();
}

void mx_grx_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
										int y, MxColor color, MxColor back)
{
	 const int len = strlen(text);

	 GrTextOption option;

	 option.txo_font = (GrFont *) font;
	 option.txo_fgcolor.v = color;
	 option.txo_bgcolor.v = back;
	 option.txo_chrtype = GR_BYTE_TEXT;
	 option.txo_direct = GR_TEXT_RIGHT;
	 option.txo_xalign = GR_ALIGN_DEFAULT;
	 option.txo_yalign = GR_ALIGN_DEFAULT;

	 if (screen_context) {
		  GrSetContext((GrContext *) image);
		  screen_context = 0;
	 }

	 GrSetClipBox(clip->x1, clip->y1, clip->x2, clip->y2);
	 GrDrawString((char *) text, len, x, y, &option);
	 GrResetClipBox();
}

unsigned int mx_grx_font_length(const struct MxFont *font, const char *text)
{
	 GrTextOption option;

	 option.txo_font = (GrFont *) font;
//    option.txo_fgcolor = 0; /* Just put in some crazy vales for colors */
//    option.txo_bgcolor = 1;
	 option.txo_chrtype = GR_BYTE_TEXT;
	 option.txo_direct = GR_TEXT_RIGHT;
	 option.txo_xalign = GR_ALIGN_DEFAULT;
	 option.txo_yalign = GR_ALIGN_DEFAULT;

	 return GrStringWidth((char *) text, strlen(text), &option);
}

unsigned int mx_grx_font_height(const struct MxFont *font)
{
	 GrTextOption option;

	 option.txo_font = (GrFont *) font;
//    option.txo_fgcolor.v = 0; /* Just put in some crazy vales for colors */
//    option.txo_bgcolor.v = 1;
	 option.txo_chrtype = GR_BYTE_TEXT;
	 option.txo_direct = GR_TEXT_RIGHT;
	 option.txo_xalign = GR_ALIGN_DEFAULT;
	 option.txo_yalign = GR_ALIGN_DEFAULT;

	 return GrStringHeight("H", 1, &option);
}
