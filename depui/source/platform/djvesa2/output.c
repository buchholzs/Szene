#include "depui/platform/platform.h"
#include "depui/support/font.h"
#include "depui/support/mouse.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/platform/djvesa2/djvesa2.h"
#include <pc.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/farptr.h>

#include <stdlib.h>

#warning Compiling DEPUI for DJGPP/Vesa2

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

typedef struct {
	 unsigned ModeAttributes;
	 unsigned granularity, startseg, farfunc;
	 short bscanline;
	 short XResolution;
	 short YResolution;
	 short charpixels;
	 unsigned bogus1, bogus2, bogus3, bogus4;
	 unsigned PhysBasePtr;
	 char bogus[228];
} ModeInfoBlock;

static unsigned int ADDR;
static unsigned width, height, depth;

static ModeInfoBlock *get_mode_info(int mode)
{
	 static ModeInfoBlock info;
	 __dpmi_regs r;

	 /* Use the transfer buffer to store the results of VBE call */
	 r.x.ax = 0x4F01;
	 r.x.cx = mode;
	 r.x.es = __tb / 16;
	 r.x.di = 0;
	 __dpmi_int(0x10, &r);

	 if (r.h.ah)
		  return 0;

	 dosmemget(__tb, sizeof(ModeInfoBlock), &info);
	 return &info;
}

static int init_graphics(int mode)
{
	 __dpmi_meminfo info;
	 __dpmi_regs reg;
	 ModeInfoBlock *mb;

	 mb = get_mode_info(mode);

	 if (!mb)
		  return 0;

	 if (!(mb->ModeAttributes & 0x80))
		  return 0;

	 width = mb->XResolution;
	 height = mb->YResolution;
	 depth = 8;

	 info.size = width * height;
	 info.address = mb->PhysBasePtr;

	 if (__dpmi_physical_address_mapping(&info) == -1)
		  return 0;

	 ADDR = info.address;		  /* Updated by above call */

	 reg.x.ax = 0x4f02;
	 reg.x.bx = 0x4000 | mode;
	 __dpmi_int(0x10, &reg);	  /* set the mode */

	 if (reg.h.al != 0x4f || reg.h.ah)
		  return 0;

	 return 1;
}

static void set_palette(int entry, int r, int g, int b)
{
	 outportb(0x3c8, (unsigned char) entry);
	 outportb(0x3c9, (unsigned char) r >> 2);
	 outportb(0x3c9, (unsigned char) g >> 2);
	 outportb(0x3c9, (unsigned char) b >> 2);
}

static MxColor _blend(MxColor xx, MxColor yy, unsigned int n)
{
	 if (n > 128)
		  return xx;
	 return yy;
}

/* A list of the valid video modes */
typedef struct mx_mode {
	 int mode;
	 int x, y;
} mx_mode;

static mx_mode modelist[] = {
	 {0x4100, 640, 400},
	 {0x4101, 640, 480},
	 {0x4103, 800, 600},
	 {0x4105, 1024, 768},
	 {0x4107, 1280, 1024},
	 {0, 0, 0}
};

int mx_djvesa2_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 int my_video_ds = 0;

	 /* Find the graphics mode */
	 int mode = 0x4101;
	 mx_mode *ptr = modelist;

	 (void) c;						  /* We can only do 8 bit modes */
	 (void) title;

	 /* Walk the list */
	 while ((ptr->mode) && (mode == 0x4101)) {

		  /* Have we found a match */
		  if ((ptr->x == x) && (ptr->y == y))
				mode = ptr->mode;

		  /* Look more in the list */
		  ++ptr;
	 }

	 /* Try to set the video mode */
	 if (!init_graphics(mode))
		  return 0;

	 /* Note: Video mode probably doesn't support text writes at this point */
	 my_video_ds = __dpmi_allocate_ldt_descriptors(1);
	 __dpmi_set_segment_base_address(my_video_ds, ADDR);
	 __dpmi_set_segment_limit(my_video_ds, (width * height) | 0xfff);
	 _farsetsel(my_video_ds);

	 driver->font = MxFontBuiltin;

	 set_palette(1, 0, 0, 0);
	 driver->colors[MxForeIndex] = 1;
	 set_palette(2, 174, 174, 174);
	 driver->colors[MxBackIndex] = 2;
	 set_palette(3, 0, 0, 0);
	 driver->colors[MxObjectForeIndex] = 3;
	 set_palette(4, 225, 225, 225);
	 driver->colors[MxObjectBackIndex] = 4;

	 set_palette(5, 255, 255, 255);
	 driver->colors[MxSelectedForeIndex] = 5;
	 set_palette(6, 84, 124, 82);
	 driver->colors[MxSelectedBackIndex] = 6;

	 set_palette(7, 215, 215, 215);
	 driver->colors[MxLightIndex] = 7;
	 set_palette(8, 154, 154, 154);
	 driver->colors[MxMedIndex] = 8;
	 set_palette(9, 114, 114, 114);
	 driver->colors[MxDarkIndex] = 9;
	 set_palette(10, 92, 156, 69);
	 driver->colors[MxDesktopIndex] = 10;
	 set_palette(11, 0, 255, 0);
	 driver->colors[MxFocusIndex] = 11;
	 set_palette(12, 147, 147, 147);
	 driver->colors[MxDisabledIndex] = 12;

	 /* We can use the fast screen access by only setting the screen segment
	    once */
	 _farsetsel(my_video_ds);

	 return 1;
}

void mx_djvesa2_gfx_exit(void)
{
	 __dpmi_regs reg;

	 reg.x.ax = 0x0003;
	 __dpmi_int(0x10, &reg);
}

void mx_djvesa2_flush(void)
{
}

void mx_djvesa2_mouse_show(int show)
{
	 Mx_MouseShow(show, mx_djvesa2_screen_pixel, mx_djvesa2_screen_get_pixel);
}

MxColor mx_djvesa2_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_djvesa2_encode(int index, int r, int g, int b)
{
	 set_palette(index, r, g, b);
	 return index;
}

void mx_djvesa2_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_djvesa2_screen_pixel, mx_djvesa2_screen_get_pixel);
}

void mx_djvesa2_done_drawing_area(void)
{
	 Mx_MouseShow(1, mx_djvesa2_screen_pixel, mx_djvesa2_screen_get_pixel);
}

void mx_djvesa2_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_djvesa2_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

#ifdef MX_DEBUG_IMAGE_AQUIRE
#include <assert.h>

static unsigned int screen_aquired = MxFalse;

#endif

void mx_djvesa2_screen_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!screen_aquired);
	 screen_aquired = True;
#endif
}

void mx_djvesa2_screen_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
	 screen_aquired = MxFalse;
#endif
}

int mx_djvesa2_screen_width(struct MxImage *image)
{
	 (void) image;
	 return width;
}

int mx_djvesa2_screen_height(struct MxImage *image)
{
	 (void) image;
	 return height;
}

int mx_djvesa2_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return depth;
}

void mx_djvesa2_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 _farnspokeb(y1 * width + x1, color);
}

MxColor mx_djvesa2_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 return _farnspeekb(y1 * width + x1);
}

void mx_djvesa2_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, mx_djvesa2_screen_pixel);
}

void mx_djvesa2_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, mx_djvesa2_screen_pixel);
}

void mx_djvesa2_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, mx_djvesa2_screen_pixel);
}

void mx_djvesa2_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 _farnspokeb(y1 * width + x1, _blend(color, _farnspeekb(y1 * width + x1), alpha));
}

struct MxImage *mx_djvesa2_image_create(int w, int h)
{
	 return Mx_ImageCreateDepth(w, h, 8);
}

struct MxImage *mx_djvesa2_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_djvesa2_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = True;
#endif
}

void mx_djvesa2_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

void mx_djvesa2_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel8Fast);
}

void mx_djvesa2_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel8Fast);
}

void mx_djvesa2_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel8Fast);
}

void mx_djvesa2_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImagePixel8Fast(image, x1, y1, _blend(color, Mx_ImageGetPixel8Fast(image, x1, y1), alpha));
}

void mx_djvesa2_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(dest->aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel8Fast, Mx_ImagePixel8Fast);
}

void mx_djvesa2_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel8Fast, mx_djvesa2_screen_pixel);
}

void mx_djvesa2_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(dest->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_djvesa2_screen_get_pixel, Mx_ImagePixel8Fast);
}

void mx_djvesa2_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_djvesa2_screen_get_pixel, mx_djvesa2_screen_pixel);
}

void mx_djvesa2_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_djvesa2_screen_pixel);
}

struct MxFont *mx_djvesa2_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_djvesa2_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_djvesa2_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back)
{
	 unsigned int i;

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, _blend, s, mx_djvesa2_screen_pixel,
													  mx_djvesa2_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(image, text, font, x, y, color, back, s, mx_djvesa2_screen_pixel);
	 }
}

void mx_djvesa2_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, _blend, clip, Mx_ImagePixel8Fast,
												 mx_djvesa2_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel8Fast);
}

unsigned int mx_djvesa2_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_djvesa2_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
