#include "depui/platform/platform.h"
#include "depui/platform/empty.h"
#include "depui/draw/region.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_empty_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title)
{
	 (void) driver;
	 (void) x;
	 (void) y;
	 (void) c;
	 (void) title;
	 return 1;
}

void mx_empty_gfx_exit(void)
{
}

void mx_empty_flush(void)
{
}

void mx_empty_mouse_show(int show)
{
	 (void) show;
}

MxColor mx_empty_blend(MxColor x, MxColor y, unsigned int n)
{
	 return (n > 128) ? y : x;
}

MxColor mx_empty_encode(int index, int r, int g, int b)
{
	 (void) r;
	 (void) g;
	 (void) b;
	 return index;
}

void mx_empty_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
}

void mx_empty_done_drawing_area(void)
{
}

void mx_empty_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_empty_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_empty_screen_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_empty_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_empty_screen_width(struct MxImage *image)
{
	 (void) image;
	 return 320;
}

int mx_empty_screen_height(struct MxImage *image)
{
	 (void) image;
	 return 200;
}

int mx_empty_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return 1;
}

void mx_empty_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 (void) x1;
	 (void) y1;
	 (void) color;
}

MxColor mx_empty_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
	 (void) x1;
	 (void) y1;
	 return (MxColor) 0;
}

void mx_empty_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) color;
}

void mx_empty_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;
	 (void) x1;
	 (void) y1;
	 (void) y2;
	 (void) color;
}

void mx_empty_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 (void) color;
}

void mx_empty_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
	 (void) x1;
	 (void) y1;
	 (void) color;
	 (void) alpha;
}

struct MxImage *mx_empty_image_create(int w, int h)
{
	 (void) w;
	 (void) h;
	 return 0;
}

struct MxImage *mx_empty_image_load(const char *filename)
{
	 (void) filename;
	 return 0;
}

void mx_empty_image_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_empty_image_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_empty_image_release(struct MxImage *image)
{
	 (void) image;
}

int mx_empty_image_width(struct MxImage *image)
{
	 (void) image;
	 return 0;
}

int mx_empty_image_height(struct MxImage *image)
{
	 (void) image;
	 return 0;
}

int mx_empty_image_depth(struct MxImage *image)
{
	 (void) image;
	 return 0;
}

void mx_empty_image_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) x1;
	 (void) y1;
	 (void) color;
	 (void) image;
}

MxColor mx_empty_image_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) x1;
	 (void) y1;
	 (void) image;
	 return (MxColor) 0;
}

void mx_empty_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) color;
	 (void) image;
}

void mx_empty_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) x1;
	 (void) y1;
	 (void) y2;
	 (void) color;
	 (void) image;
}

void mx_empty_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 (void) color;
	 (void) image;
}

void mx_empty_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) x1;
	 (void) y1;
	 (void) image;
	 (void) color;
	 (void) alpha;
}

void mx_empty_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 (void) dest;
	 (void) sx;
	 (void) sy;
	 (void) dx;
	 (void) dy;
	 (void) w;
	 (void) h;
}

void mx_empty_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 (void) dest;
	 (void) sx;
	 (void) sy;
	 (void) dx;
	 (void) dy;
	 (void) w;
	 (void) h;
}

void mx_empty_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 (void) dest;
	 (void) sx;
	 (void) sy;
	 (void) dx;
	 (void) dy;
	 (void) w;
	 (void) h;
}

void mx_empty_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 (void) dest;
	 (void) sx;
	 (void) sy;
	 (void) dx;
	 (void) dy;
	 (void) w;
	 (void) h;
}

void mx_empty_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 (void) decoration;
	 (void) x;
	 (void) y;
}

struct MxFont *mx_empty_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return 0;
}

void mx_empty_font_destroy(struct MxFont *font)
{
	 (void) font;
}

void mx_empty_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											MxColor back)
{
	 (void) image;
	 (void) text;
	 (void) font;
	 (void) x;
	 (void) y;
	 (void) color;
	 (void) back;
}

void mx_empty_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
										  int y, MxColor color, MxColor back)
{
	 (void) image;
	 (void) text;
	 (void) clip;
	 (void) font;
	 (void) x;
	 (void) y;
	 (void) color;
	 (void) back;
}

unsigned int mx_empty_font_length(const struct MxFont *font, const char *text)
{
	 (void) text;
	 (void) font;
	 return 1;
}

unsigned int mx_empty_font_height(const struct MxFont *font)
{
	 (void) font;
	 return 1;
}
