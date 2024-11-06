#include "depui/platform/platform.h"
#include "depui/platform/buffdbl.h"
#include "depui/desktop/driver.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"
#include "depui/draw/region.h"
#include "depui/desktop/desktop.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Initialize a buffered driver */
void MxDriverOutputBufferInit(MxDriverOutputBuffer * buff, MxDriverOutput * other)
{
	 /* The buffered driver uses the image stuff from the target driver */
	 buff->output.ImageCreate = other->ImageCreate;
	 buff->output.ImageLoad = other->ImageLoad;

	 buff->output.image_vtable = other->image_vtable;
	 buff->output.image_trans_vtable = other->image_trans_vtable;

	 buff->output.FontImageRender = other->FontImageRender;

	 /* Connect to the other driver */
	 buff->tobuffer = other;
}

/* Here is the driver to be buffered */
static MxDriverOutput *output = 0;

/* Here is the current buffered space */
static struct MxImage *buffer = 0;
static MxRegion dirty;

int mx_double_buffer_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 int i;
	 int ret;

	 /* Get the driver to be buffered out of the driver struct */
	 MxDriverOutputBuffer *buffered = (MxDriverOutputBuffer *) driver;

	 output = buffered->tobuffer;

	 /* Actually init the other driver */
	 ret = output->Init(output, x, y, c, title);

	 /* Take the same colors and font as the other driver */
	 for (i = 0; i < 12; i++)
		  driver->colors[i] = output->colors[i];
	 driver->font = output->font;

	 /* Create our double buffer and our dirty rectangle list */
	 buffer = MxImageCreate(output->screen_vtable.Width(0), output->screen_vtable.Height(0));
	 if (!buffer)
		  return 0;

	 MxRegionConstruct(&dirty);

	 return ret;
}

//#include <allegro.h>

void mx_double_buffer_gfx_exit(void)
{
//    PALETTE pal;

//    get_palette(pal);
//    save_bitmap("screen2.bmp", screen, pal);

	 /* Clean up our double buffer */
	 if (buffer)
		  MxImageDestroy(buffer);
	 MxRegionDestruct(&dirty);

	 buffer = 0;

	 /* Clean up the other output driver too */
	 output->Exit();
	 output = 0;
}

void mx_double_buffer_flush(void)
{
	 unsigned int i;

	 /* Cleanup the dirty list, by inverting it with the full list */
	 MxRegionOptimize(&dirty);
	 MxRegionSort(&dirty);

	 /* Prepace to draw the data over */
	 output->MouseShow(0);
	 output->screen_vtable.Aquire(0);
	 output->image_vtable.Aquire(buffer);

	 /* Draw the dirty data over */
	 for (i = 0; i < MxRegionNumber(dirty); i++) {
		  const MxRect *const s = MxRegionRect(dirty, i);

//        output->screen_fast_vtable.RectFill(0, s->x1, s->y1, s->x2, s->y2, MxColorFore);

		  output->BlitToScreen(buffer, 0, s->x1, s->y1, s->x1, s->y1, s->x2 - s->x1 + 1, s->y2 - s->y1 + 1);
	 }
	 MxRegionDestruct(&dirty);
	 MxRegionConstruct(&dirty);

	 /* We are done copying the data over */
	 output->screen_vtable.Release(0);
	 output->image_vtable.Release(buffer);
	 output->MouseShow(1);
}

void mx_double_buffer_mouse_show(int show)
{
	 (void) show;
}

void mx_double_buffer_drawing_area(int x1, int y1, int x2, int y2)
{
	 MxRect rect;

	 rect.x1 = x1;
	 rect.y1 = y1;
	 rect.x2 = x2;
	 rect.y2 = y2;

	 MxRegionAddRect(&dirty, &rect);
}

MxColor mx_double_buffer_blend(MxColor x, MxColor y, unsigned int n)
{
	 return output->ColorBlend(x, y, n);
}

MxColor mx_double_buffer_encode(int cindex, int r, int g, int b)
{
	 return output->ColorEncode(cindex, r, g, b);
}

void mx_double_buffer_done_drawing_area(void)
{
}

void mx_double_buffer_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_double_buffer_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_double_buffer_screen_aquire(struct MxImage *image)
{
	 (void) image;
	 MxImageAquire(buffer);
}

void mx_double_buffer_screen_release(struct MxImage *image)
{
	 (void) image;
	 MxImageRelease(buffer);
}

int mx_double_buffer_screen_width(struct MxImage *image)
{
	 (void) image;
	 return MxImageWidth(buffer);
}

int mx_double_buffer_screen_height(struct MxImage *image)
{
	 (void) image;
	 return MxImageHeight(buffer);
}

int mx_double_buffer_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return MxImageDepth(buffer);
}

void mx_double_buffer_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 unsigned int i;

	 (void) image;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (!MxClipPixel(s->x1, s->y1, s->x2, s->y2, x1, y1)) {
				MxImagePixelFast(buffer, x1, y1, color);

				/* The pixel can only be in one of the regions rect */
				return;
		  }
	 }
}

MxColor mx_double_buffer_screen_get_pixel(struct MxImage * image, int x1, int y1)
{
	 (void) image;
	 return output->image_vtable.GetPixel(buffer, x1, y1);
}

void mx_double_buffer_screen_hline(struct MxImage *image, int rx1, int ry1, int rx2, MxColor color)
{
	 unsigned int i;

	 (void) image;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  int x1 = rx1, y1 = ry1, x2 = rx2;

		  if (!MxClipHLine(s->x1, s->y1, s->x2, s->y2, x1, y1, x2))
				MxImageHLineFast(buffer, x1, y1, x2, color);
	 }
}

void mx_double_buffer_screen_vline(struct MxImage *image, int rx1, int ry1, int ry2, MxColor color)
{
	 unsigned int i;

	 (void) image;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  int x1 = rx1, y1 = ry1, y2 = ry2;

		  if (!MxClipVLine(s->x1, s->y1, s->x2, s->y2, x1, y1, y2))
				MxImageVLineFast(buffer, x1, y1, y2, color);
	 }
}

void mx_double_buffer_screen_rectfill(struct MxImage *image, int rx1, int ry1, int rx2, int ry2, MxColor color)
{
	 unsigned int i;

	 (void) image;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  int x1 = rx1, y1 = ry1, x2 = rx2, y2 = ry2;

		  if (!MxClipRect(s->x1, s->y1, s->x2, s->y2, x1, y1, x2, y2))
				MxImageRectFillFast(buffer, x1, y1, x2, y2, color);
	 }
}

void mx_double_buffer_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 unsigned int i;

	 (void) image;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  if (!MxClipPixel(s->x1, s->y1, s->x2, s->y2, x1, y1)) {
				MxImagePixelTransFast(buffer, x1, y1, color, alpha);

				/* The pixel can only be in one of the regions rect */
				return;
		  }
	 }
}

void mx_double_buffer_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 output->Blit(src, dest, sx, sy, dx, dy, w, h);
}

void mx_double_buffer_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) dest;
	 output->Blit(src, buffer, sx, sy, dx, dy, w, h);
}

void mx_double_buffer_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 output->Blit(buffer, dest, sx, sy, dx, dy, w, h);
}

void mx_double_buffer_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 (void) dest;
	 output->Blit(buffer, buffer, sx, sy, dx, dy, w, h);
}

void mx_double_buffer_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, buffer, MxImagePixelFast);
}

struct MxFont *mx_double_buffer_font_load(const char *name, int points, MxFontFlag flags)
{
	 return output->FontLoad(name, points, flags);
}

void mx_double_buffer_font_destroy(struct MxFont *font)
{
	 output->FontDestroy(font);
}

void mx_double_buffer_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y,
													  MxColor color, MxColor back)
{
	 unsigned int i;

	 (void) image;

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const clip = MxRegionRect(mx_region, i);

		  output->FontImageRender(buffer, text, clip, font, x, y, color, back);
	 }
}

unsigned int mx_double_buffer_font_length(const struct MxFont *font, const char *text)
{
	 return output->FontLength(font, text);
}

unsigned int mx_double_buffer_font_height(const struct MxFont *font)
{
	 return output->FontHeight(font);
}
