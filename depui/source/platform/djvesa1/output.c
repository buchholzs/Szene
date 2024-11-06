#include "depui/platform/platform.h"
#include "depui/support/font.h"
#include "depui/support/mouse.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/platform/djvesa1/djvesa1.h"
#include <pc.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/farptr.h>
#include <string.h>

#warning Compiling DEPUI for DJGPP/Vesa1

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

typedef struct VESA_INFO {
	 unsigned char VESASignature[4] __attribute__ ((packed));
	 unsigned short VESAVersion __attribute__ ((packed));
	 unsigned long OEMStringPtr __attribute__ ((packed));
	 unsigned char Capabilities[4] __attribute__ ((packed));
	 unsigned long VideoModePtr __attribute__ ((packed));
	 unsigned short TotalMemory __attribute__ ((packed));
	 unsigned short OemSoftwareRev __attribute__ ((packed));
	 unsigned long OemVendorNamePtr __attribute__ ((packed));
	 unsigned long OemProductNamePtr __attribute__ ((packed));
	 unsigned long OemProductRevPtr __attribute__ ((packed));
	 unsigned char Reserved[222] __attribute__ ((packed));
	 unsigned char OemData[256] __attribute__ ((packed));
} VESA_INFO;

static int get_vesa_info(VESA_INFO * vesa_info)
{
	 __dpmi_regs r;
	 long dosbuf;
	 unsigned int c;

	 /* Clear out the transfer buffer to start */
	 dosbuf = __tb & 0xFFFFF;
	 for (c = 0; c < sizeof(VESA_INFO); c++)
		  _farpokeb(_dos_ds, dosbuf + c, 0);

	 /* Get the vesa info to the transfer buffer */
	 r.x.ax = 0x4F00;
	 r.x.di = dosbuf & 0xF;
	 r.x.es = (dosbuf >> 4) & 0xFFFF;
	 __dpmi_int(0x10, &r);

	 /* Vesa info did not work */
	 if (r.h.ah)
		  return -1;

	 /* Copy the transfer data to our memory space */
	 dosmemget(dosbuf, sizeof(VESA_INFO), vesa_info);
	 if (strncmp(vesa_info->VESASignature, "VESA", 4) != 0)
		  return -1;

	 return 0;
}

typedef struct MODE_INFO {
	 unsigned short ModeAttributes __attribute__ ((packed));
	 unsigned char WinAAttributes __attribute__ ((packed));
	 unsigned char WinBAttributes __attribute__ ((packed));
	 unsigned short WinGranularity __attribute__ ((packed));
	 unsigned short WinSize __attribute__ ((packed));
	 unsigned short WinASegment __attribute__ ((packed));
	 unsigned short WinBSegment __attribute__ ((packed));
	 unsigned long WinFuncPtr __attribute__ ((packed));
	 unsigned short BytesPerScanLine __attribute__ ((packed));
	 unsigned short XResolution __attribute__ ((packed));
	 unsigned short YResolution __attribute__ ((packed));
	 unsigned char XCharSize __attribute__ ((packed));
	 unsigned char YCharSize __attribute__ ((packed));
	 unsigned char NumberOfPlanes __attribute__ ((packed));
	 unsigned char BitsPerPixel __attribute__ ((packed));
	 unsigned char NumberOfBanks __attribute__ ((packed));
	 unsigned char MemoryModel __attribute__ ((packed));
	 unsigned char BankSize __attribute__ ((packed));
	 unsigned char NumberOfImagePages __attribute__ ((packed));
	 unsigned char Reserved_page __attribute__ ((packed));
	 unsigned char RedMaskSize __attribute__ ((packed));
	 unsigned char RedMaskPos __attribute__ ((packed));
	 unsigned char GreenMaskSize __attribute__ ((packed));
	 unsigned char GreenMaskPos __attribute__ ((packed));
	 unsigned char BlueMaskSize __attribute__ ((packed));
	 unsigned char BlueMaskPos __attribute__ ((packed));
	 unsigned char ReservedMaskSize __attribute__ ((packed));
	 unsigned char ReservedMaskPos __attribute__ ((packed));
	 unsigned char DirectColorModeInfo __attribute__ ((packed));
	 unsigned long PhysBasePtr __attribute__ ((packed));
	 unsigned long OffScreenMemOffset __attribute__ ((packed));
	 unsigned short OffScreenMemSize __attribute__ ((packed));
	 unsigned char Reserved[206] __attribute__ ((packed));
} MODE_INFO;

static int get_mode_info(int mode, MODE_INFO * mode_info)
{
	 __dpmi_regs r;
	 long dosbuf;
	 unsigned int c;

	 /* First, zero the transfer buffer */
	 dosbuf = __tb & 0xFFFFF;
	 for (c = 0; c < sizeof(MODE_INFO); c++)
		  _farpokeb(_dos_ds, dosbuf + c, 0);

	 /* Get the mode info to the transfer buffer */
	 r.x.ax = 0x4F01;
	 r.x.di = dosbuf & 0xF;
	 r.x.es = (dosbuf >> 4) & 0xFFFF;
	 r.x.cx = mode;
	 __dpmi_int(0x10, &r);

	 /* Mode info did not work */
	 if (r.h.ah)
		  return -1;

	 /* Copy the buffer to our variable */
	 dosmemget(dosbuf, sizeof(MODE_INFO), mode_info);
	 return 0;
}

static int find_vesa_mode(int w, int h)
{
	 int mode_list[1024];
	 int number_of_modes;
	 long mode_ptr;
	 int c;

	 VESA_INFO vesa_info;
	 MODE_INFO mode_info;

	 if (w < 640)
		  w = 640;
	 if (h < 480)
		  h = 480;

	 if (get_vesa_info(&vesa_info) != 0)
		  return 0;

	 mode_ptr = ((vesa_info.VideoModePtr & 0xFFFF0000) >> 12) + (vesa_info.VideoModePtr & 0xFFFF);
	 number_of_modes = 0;

	 while (_farpeekw(_dos_ds, mode_ptr) != 0xFFFF) {
		  mode_list[number_of_modes] = _farpeekw(_dos_ds, mode_ptr);
		  number_of_modes++;
		  mode_ptr += 2;
	 }

	 for (c = 0; c < number_of_modes; c++) {
		  if (get_mode_info(mode_list[c], &mode_info) != 0)
				continue;

		  if ((mode_info.ModeAttributes & 0x19) != 0x19)
				continue;

		  if ((mode_info.XResolution != w) || (mode_info.YResolution != h))
				continue;

		  if (mode_info.NumberOfPlanes != 1)
				continue;

		  if (mode_info.MemoryModel != 4)
				continue;

		  if (mode_info.BitsPerPixel != 8)
				continue;

		  if (mode_info.WinSize != 64)
				continue;

		  if (mode_info.WinGranularity != 64)
				continue;

		  return mode_list[c];
	 }
	 return 0;
}

static unsigned int vesa_bank = 0;
static unsigned int scan_line;
static unsigned int height, width;

static int set_vesa_mode(int w, int h)
{
	 MODE_INFO mode_info;

	 __dpmi_regs r;
	 int mode_number = find_vesa_mode(w, h);

	 if (!mode_number)
		  return -1;

	 get_mode_info(mode_number, &mode_info);
	 scan_line = mode_info.BytesPerScanLine;
	 width = mode_info.XResolution - 1;
	 height = mode_info.YResolution - 1;

	 r.x.ax = 0x4F02;
	 r.x.bx = mode_number;
	 __dpmi_int(0x10, &r);

	 if (r.h.ah)
		  return -1;
	 return 0;
}

static void set_palette(int entry, int r, int g, int b)
{
	 outportb(0x3c8, (unsigned char) entry);
	 outportb(0x3c9, (unsigned char) r >> 2);
	 outportb(0x3c9, (unsigned char) g >> 2);
	 outportb(0x3c9, (unsigned char) b >> 2);
}

static void set_vesa_bank(unsigned int bank_number)
{
	 __dpmi_regs r;

	 r.x.ax = 0x4F05;
	 r.x.bx = 0;
	 r.x.dx = bank_number;
	 __dpmi_int(0x10, &r);

	 r.x.ax = 0x4F05;
	 r.x.bx = 1;
	 r.x.dx = bank_number;
	 __dpmi_int(0x10, &r);

	 vesa_bank = bank_number;
}

static MxColor _blend(MxColor xx, MxColor yy, unsigned int n)
{
	 if (n > 128)
		  return xx;
	 return yy;
}

int mx_djvesa1_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 (void) c;
	 (void) title;

	 /* Try to set the video mode */
	 if (set_vesa_mode(x, y) != 0)
		  return 0;

	 /* Start off with some specific vesa bank */
	 set_vesa_bank(0);

	 /* Set the pixel selector so the other routines don't have to */
	 _farsetsel(_dos_ds);

//  driver->font = MxFontBuiltin;
	 driver->font = MxFontBuiltin8x8;

	 set_palette(1, 0, 0, 0);
	 driver->colors[MxForeIndex] = 1;
	 set_palette(2, 174, 174, 174);
	 driver->colors[MxBackIndex] = 2;
	 set_palette(3, 0, 0, 0);
	 driver->colors[MxObjectForeIndex] = 3;
	 set_palette(4, 225, 225, 225);
	 driver->colors[MxObjectBackIndex] = 4;

	 set_palette(5, 0, 0, 0);
	 driver->colors[MxSelectedForeIndex] = 5;
	 set_palette(6, 0, 184, 84);
	 driver->colors[MxSelectedBackIndex] = 6;

	 set_palette(7, 215, 215, 215);
	 driver->colors[MxLightIndex] = 7;
	 set_palette(8, 144, 144, 144);
	 driver->colors[MxMedIndex] = 8;
	 set_palette(9, 124, 124, 124);
	 driver->colors[MxDarkIndex] = 9;
	 set_palette(10, 90, 138, 50);
	 driver->colors[MxDesktopIndex] = 10;
	 set_palette(11, 0, 255, 0);
	 driver->colors[MxFocusIndex] = 11;
	 set_palette(12, 147, 147, 147);
	 driver->colors[MxDisabledIndex] = 12;

	 return 1;
}

void mx_djvesa1_gfx_exit(void)
{
	 __dpmi_regs reg;

	 reg.x.ax = 0x0003;
	 __dpmi_int(0x10, &reg);
}

void mx_djvesa1_flush(void)
{
}

void mx_djvesa1_mouse_show(int show)
{
	 Mx_MouseShow(show, mx_djvesa1_screen_pixel, mx_djvesa1_screen_get_pixel);
}

MxColor mx_djvesa1_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_djvesa1_encode(int index, int r, int g, int b)
{
	 set_palette(index, r, g, b);
	 return index;
}

void mx_djvesa1_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 Mx_MouseShow(0, mx_djvesa1_screen_pixel, mx_djvesa1_screen_get_pixel);
}

void mx_djvesa1_done_drawing_area(void)
{
	 Mx_MouseShow(1, mx_djvesa1_screen_pixel, mx_djvesa1_screen_get_pixel);
}

void mx_djvesa1_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_djvesa1_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

#ifdef MX_DEBUG_IMAGE_AQUIRE
#include <assert.h>

static unsigned int screen_aquired = MxFalse;

#endif

void mx_djvesa1_screen_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!screen_aquired);
	 screen_aquired = True;
#endif
}

void mx_djvesa1_screen_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
	 screen_aquired = MxFalse;
#endif
}

int mx_djvesa1_screen_width(struct MxImage *image)
{
	 (void) image;
	 return width;
}

int mx_djvesa1_screen_height(struct MxImage *image)
{
	 (void) image;
	 return height;
}

int mx_djvesa1_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return 8;
}

void mx_djvesa1_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 const unsigned int address = y1 * scan_line + x1;
	 const unsigned int bank_number = address >> 16;
	 const unsigned int bank_offset = address & 0xffff;

	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif

	 if (bank_number != vesa_bank)
		  set_vesa_bank(bank_number);

	 _farnspokeb(0xA0000 + bank_offset, color);
}

MxColor mx_djvesa1_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 const unsigned int address = y1 * scan_line + x1;
	 const unsigned int bank_number = address >> 16;
	 const unsigned int bank_offset = address & 0xffff;

	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 if (bank_number != vesa_bank)
		  set_vesa_bank(bank_number);

	 return _farnspeekb(0xA0000 + bank_offset);
}

void mx_djvesa1_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, mx_djvesa1_screen_pixel);
}

void mx_djvesa1_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, mx_djvesa1_screen_pixel);
}

void mx_djvesa1_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, mx_djvesa1_screen_pixel);
}

void mx_djvesa1_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 const unsigned int address = y1 * scan_line + x1;
	 const unsigned int bank_number = address >> 16;
	 const unsigned int bank_offset = address & 0xffff;

	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif

	 if (bank_number != vesa_bank)
		  set_vesa_bank(bank_number);

	 _farnspokeb(0xA0000 + bank_offset, _blend(color, _farnspeekb(0xa0000 + bank_offset), alpha));

}

struct MxImage *mx_djvesa1_image_create(int w, int h)
{
	 return Mx_ImageCreateDepth(w, h, 8);
}

struct MxImage *mx_djvesa1_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_djvesa1_image_aquire(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(!image->aquired);
	 image->aquired = True;
#endif
}

void mx_djvesa1_image_release(struct MxImage *image)
{
	 (void) image;
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
	 image->aquired = MxFalse;
#endif
}

void mx_djvesa1_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageHLineFast(image, x1, y1, x2, color, Mx_ImagePixel8Fast);
}

void mx_djvesa1_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageVLineFast(image, x1, y1, y2, color, Mx_ImagePixel8Fast);
}

void mx_djvesa1_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImageRectFillFast(image, x1, y1, x2, y2, color, Mx_ImageHLineFast, Mx_ImagePixel8Fast);
}

void mx_djvesa1_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif
	 Mx_ImagePixel8Fast(image, x1, y1, _blend(color, Mx_ImageGetPixel8Fast(image, x1, y1), alpha));
}

void mx_djvesa1_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(dest->aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel8Fast, Mx_ImagePixel8Fast);
}

void mx_djvesa1_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(src->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, Mx_ImageGetPixel8Fast, mx_djvesa1_screen_pixel);
}

void mx_djvesa1_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(dest->aquired);
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_djvesa1_screen_get_pixel, Mx_ImagePixel8Fast);
}

void mx_djvesa1_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif
	 Mx_ImageBlitFast(src, dest, sx, sy, dx, dy, w, h, mx_djvesa1_screen_get_pixel, mx_djvesa1_screen_pixel);
}

void mx_djvesa1_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_djvesa1_screen_pixel);
}

struct MxFont *mx_djvesa1_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_djvesa1_font_destroy(struct MxFont *font)
{
	 Mx_FontDestroy(font);
}

void mx_djvesa1_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back)
{
	 unsigned int i;

#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(screen_aquired);
#endif

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (font->flags & MxFontAntialiased)
				Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, _blend, s, mx_djvesa1_screen_pixel,
													  mx_djvesa1_screen_trans_pixel);
		  else
				Mx_FontTextPixmapRender(image, text, font, x, y, color, back, s, mx_djvesa1_screen_pixel);
	 }
}

void mx_djvesa1_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back)
{
#ifdef MX_DEBUG_IMAGE_AQUIRE
	 assert(image->aquired);
#endif

	 if (font->flags & MxFontAntialiased)
		  Mx_FontTextAntialiasedRender(image, text, font, x, y, color, back, _blend, clip, Mx_ImagePixel8Fast,
												 mx_djvesa1_image_trans_pixel);
	 else
		  Mx_FontTextPixmapRender(image, text, font, x, y, color, back, clip, Mx_ImagePixel8Fast);
}

unsigned int mx_djvesa1_font_length(const struct MxFont *font, const char *text)
{
	 return Mx_FontLength(font, text);
}

unsigned int mx_djvesa1_font_height(const struct MxFont *font)
{
	 return Mx_FontHeight(font);
}
