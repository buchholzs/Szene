#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/support/font.h"
#include "depui/support/image.h"
#include "depui/support/mouse.h"
#include <microwin/nano-X.h>

/*
 * Definitions to make it easy to define cursors
 */
#define _       ((unsigned) 0)  /* off bits */
#define X       ((unsigned) 1)  /* on bits */
#define MASK(a,b,c,d,e,f,g) \
        (((((((((((((a * 2) + b) * 2) + c) * 2) + d) * 2) \
        + e) * 2) + f) * 2) + g) << 9)

#warning Compiling DEPUI for Nano-X

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

GR_WINDOW_ID w1;
GR_GC_ID gc1;
GR_GC_ID bgc;

int mx_nanox_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 GR_SCREEN_INFO i;

	 if (GrOpen() < 0) {
		  fprintf(stderr, "Cannot open graphics\n");
		  exit(1);
	 }
	 GrReqShmCmds(65536);

	 GrGetScreenInfo(&i);
	 /* We must do everything with the root window. This is because of DEPUI's 
	    architecture */
	 w1 = GrNewWindow(GR_ROOT_WINDOW_ID, 0, 0, i.cols, i.rows, 0, 0, 0);
	 GrMapWindow(w1);
	 gc1 = GrNewGC();

	 GrSelectEvents(w1,
						 GR_EVENT_MASK_MOUSE_MOTION | GR_EVENT_MASK_MOUSE_POSITION | GR_EVENT_MASK_BUTTON_DOWN | GR_EVENT_MASK_BUTTON_UP |
						 GR_EVENT_MASK_KEY_DOWN);

	 /* Sets NANOX's default fixed font */
	 /* Set this to whatever you like */
	 driver->font = (struct MxFont *) GrCreateFont(GR_FONT_SYSTEM_FIXED, 0, NULL);

	 driver->colors[MxForeIndex] = MWRGB(0, 0, 0);
	 driver->colors[MxBackIndex] = MWRGB(174, 174, 174);
	 driver->colors[MxObjectForeIndex] = MWRGB(0, 0, 0);
	 driver->colors[MxObjectBackIndex] = MWRGB(225, 225, 225);

	 driver->colors[MxSelectedForeIndex] = MWRGB(255, 255, 255);
	 driver->colors[MxSelectedBackIndex] = MWRGB(84, 124, 82);

	 driver->colors[MxLightIndex] = MWRGB(215, 215, 215);
	 driver->colors[MxMedIndex] = MWRGB(154, 154, 154);
	 driver->colors[MxDarkIndex] = MWRGB(114, 114, 114);
	 driver->colors[MxDesktopIndex] = MWRGB(92, 156, 69);
	 driver->colors[MxFocusIndex] = MWRGB(0, 255, 0);
	 driver->colors[MxDisabledIndex] = MWRGB(147, 147, 147);

	 return 1;
}

void mx_nanox_gfx_exit(void)
{
	 GrClose();
}

void mx_nanox_flush(void)
{
}

void mx_nanox_mouse_show(const int show)
{
}

MxColor mx_nanox_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_nanox_encode(int index, int r, int g, int b)
{
	 (void) index;
	 return MWRGB(r, g, b);
}

void mx_nanox_drawing_area(int x1, int y1, int x2, int y2)
{
}

void mx_nanox_done_drawing_area(void)
{
}

void mx_nanox_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_nanox_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_nanox_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_nanox_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_nanox_screen_width(struct MxImage *image)
{
	 GR_SCREEN_INFO i;

	 GrGetScreenInfo(&i);
	 return i.cols;
}

int mx_nanox_screen_height(struct MxImage *image)
{
	 GR_SCREEN_INFO i;

	 GrGetScreenInfo(&i);
	 return i.rows;
}

int mx_nanox_screen_depth(struct MxImage *image)
{
	 GR_SCREEN_INFO i;

	 GrGetScreenInfo(&i);
	 (void) image;
	 return i.bpp;
}

void mx_nanox_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 GrSetGCForeground(gc1, (GR_COLOR) color);
	 GrPoint(w1, gc1, x1, y1);
}

MxColor mx_nanox_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 GR_PIXELVAL p;

	 (void) image;
	 GrReadArea(w1, x1, y1, 1, 1, &p);
	 return ((MxColor) p);
}

void mx_nanox_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;
	 GrSetGCForeground(gc1, (GR_COLOR) color);
	 GrLine(w1, gc1, x1, y1, x2, y1);
}

void mx_nanox_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;
	 GrSetGCForeground(gc1, (GR_COLOR) color);
	 GrLine(w1, gc1, x1, y1, x1, y2);
}

void mx_nanox_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 GrSetGCForeground(gc1, (GR_COLOR) color);
	 GrFillRect(w1, gc1, x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

void mx_nanox_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 GR_PIXELVAL p;

	 GrReadArea(w1, x1, y1, 1, 1, &p);
	 GrSetGCForeground(gc1, (GR_COLOR) mx_nanox_blend(color, p, alpha));
	 GrPoint(w1, gc1, x1, y1);
}

struct MxImage *mx_nanox_image_create(int w, int h)
{
	 GR_GC_ID gc;
	 GR_REGION_ID rid;

	 gc = GrNewGC();
	 rid = GrNewRegion();
	 GrSetGCRegion(gc, rid);
	 gc1 = gc;
	 return (struct MxImage *) gc;
//    return Mx_ImageCreateDepth(w, h, 24);
}

void mx_nanox_image_destroy(struct MxImage *image)
{
	 GrDestroyGC((GR_GC_ID) image);
}

struct MxImage *mx_nanox_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_nanox_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = True;
#endif
}

void mx_nanox_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

int mx_nanox_image_depth(struct MxImage *image)
{
	 GR_SCREEN_INFO i;

	 GrGetScreenInfo(&i);
	 (void) image;
	 return i.bpp;
}

int mx_nanox_image_width(struct MxImage *image)
{
	 GR_RECT r;

	 gc1 = (GR_REGION_ID) image;
	 GrGetRegionBox(gc1, &r);
	 return r.width;
}

int mx_nanox_image_height(struct MxImage *image)
{
	 GR_RECT r;

	 gc1 = (GR_REGION_ID) image;
	 GrGetRegionBox(gc1, &r);
	 return r.height;
}

void mx_nanox_image_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 gc1 = (GR_REGION_ID) image;
	 GrSetGCForeground(gc1, (GR_COLOR) color);
	 GrPoint(w1, gc1, x1, y1);
}

MxColor mx_nanox_image_get_pixel(struct MxImage *image, int x1, int y1)
{
	 GR_PIXELVAL p;

	 GrReadArea(w1, x1, y1, 1, 1, &p);
	 return ((MxColor) p);
}

void mx_nanox_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 GrSetGCForeground((GR_GC_ID) image, (GR_COLOR) color);
	 GrLine(w1, (GR_GC_ID) image, x1, y1, x2, y1);
}

void mx_nanox_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 GrSetGCForeground((GR_GC_ID) image, (GR_COLOR) color);
	 GrLine(w1, (GR_GC_ID) image, x1, y1, x1, y2);
}

void mx_nanox_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 GrSetGCForeground((GR_GC_ID) image, (GR_COLOR) color);
	 GrFillRect(w1, (GR_GC_ID) image, x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

void mx_nanox_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 GR_PIXELVAL p;

	 GrReadArea(w1, x1, y1, 1, 1, &p);
	 GrSetGCForeground((GR_GC_ID) image, (GR_COLOR) mx_nanox_blend(color, p, alpha));
	 GrPoint(w1, (GR_GC_ID) image, x1, y1);
}

void mx_nanox_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
//    Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel24Fast,
//         Mx_ImagePixel24Fast);
}

void mx_nanox_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
//    Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel24Fast,
//         mx_nanox_screen_pixel);
}

void mx_nanox_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
//    Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_nanox_screen_get_pixel,
//                   Mx_ImagePixel24Fast);
}

void mx_nanox_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
//    Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_nanox_screen_get_pixel,
//         mx_nanox_screen_pixel);
}

void mx_nanox_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_nanox_screen_pixel);
}

struct MxFont *mx_nanox_font_load(const char *name, int points, MxFontFlag flags)
{
	 GR_FONT_ID id;

	 (void) flags;
	 id = GrCreateFont((GR_CHAR *) name, (GR_COORD) points, NULL);
	 return (struct MxFont *) id;
}

void mx_nanox_font_destroy(struct MxFont *font)
{
	 GrDestroyFont((GR_FONT_ID) font);
}

/* XXXX SOME PROBLEMS HERE, PLEASE CHECK CLIPPING ON NANOX TEXT */
void mx_nanox_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											MxColor back)
{
	 int i;
	 GR_REGION_ID reg;
	 GR_GC_INFO gc_info;
	 GR_RECT r;
	 const int len = strlen(text);

	 GrSetGCForeground(gc1, (GR_COLOR) color);
	 GrSetGCBackground(gc1, (GR_COLOR) back);
	 GrSetGCFont(gc1, (GR_FONT_ID) font);

	 GrGetGCInfo(gc1, &gc_info);

	 reg = GrNewRegion();
	 GrSetGCRegion(gc1, reg);

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  r.x = s->x1;
		  r.y = s->y1;
		  r.width = s->x2 - s->x1;
		  r.height = s->y2 - s->y1;
		  GrUnionRectWithRegion(reg, &r);
		  GrText(w1, gc1, x, y, (char *) text, (GR_COUNT) len, GR_TFTOP);
	 }

	 GrSetGCRegion(gc1, 0);
	 GrDestroyRegion(reg);
}

void mx_nanox_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
										  int y, MxColor color, MxColor back)
{
	 const int len = strlen(text);

	 GrSetGCForeground((GR_GC_ID) image, (GR_COLOR) color);
	 GrSetGCBackground((GR_GC_ID) image, (GR_COLOR) back);
	 GrSetGCFont((GR_GC_ID) image, (GR_FONT_ID) font);
	 GrText(w1, (GR_GC_ID) image, x, y, (char *) text, (GR_COUNT) len, GR_TFTOP);
}

unsigned int mx_nanox_font_length(const struct MxFont *font, const char *text)
{
	 int w, h, b;
	 const int len = strlen(text);

	 GrSetGCFont(gc1, (GR_FONT_ID) font);
	 GrGetGCTextSize(gc1, (char *) text, len, 0, &w, &h, &b);
	 return w;
}

unsigned int mx_nanox_font_height(const struct MxFont *font)
{
	 int w, h, b;

	 GrSetGCFont(gc1, (GR_FONT_ID) font);
	 GrGetGCTextSize(gc1, "M", 1, 0, &w, &h, &b);
	 return h;
}
