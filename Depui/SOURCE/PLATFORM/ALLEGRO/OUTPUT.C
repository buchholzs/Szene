#include "depui/platform/platform.h"
#include "depui/graphics/draw.h"
#include "depui/graphics/clip.h"
#include "depui/graphics/decorate.h"

/* Allegro does a strange macro thing with main so we have to compensate <sigh> */
#undef main
#include <allegro.h>

#ifdef __MSDOS__
#warning Compiling DEPUI for DOS/Allegro
#else
#warning Compiling DEPUI for Linux/Allegro
#endif

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_allegro_gfx_init(MxDriverOutput * platform, int x, int y, int c, const char *title)
{
	 int ret;

	 allegro_init();
	 install_keyboard();
	 install_timer();
	 install_mouse();

	 set_color_depth(c);
	 ret = set_gfx_mode(GFX_AUTODETECT, x, y, 0, 0);
//  ret = set_gfx_mode(GFX_SAFE, 320, 200, 0, 0);

	 /* Returned value *less than zero* means failure */
	 if (ret >= 0) {

		  text_mode(-1);
		  show_mouse(NULL);

		  platform->font = (struct MxFont *) font;

		  platform->colors[MxForeIndex] = makecol(0, 0, 0);
		  platform->colors[MxBackIndex] = makecol(174, 174, 174);
		  platform->colors[MxObjectForeIndex] = makecol(0, 0, 0);
		  platform->colors[MxObjectBackIndex] = makecol(225, 225, 225);
		  platform->colors[MxSelectedForeIndex] = makecol(0, 0, 0);
		  platform->colors[MxSelectedBackIndex] = makecol(122, 196, 89);
		  platform->colors[MxLightIndex] = makecol(215, 215, 215);
		  platform->colors[MxMedIndex] = makecol(154, 154, 164);
		  platform->colors[MxDarkIndex] = makecol(114, 114, 114);
		  platform->colors[MxDesktopIndex] = makecol(47, 96, 106);
		  platform->colors[MxFocusIndex] = makecol(0, 255, 0);
		  platform->colors[MxDisabledIndex] = makecol(107, 107, 107);
	 }
	 return (ret >= 0);
}

void mx_allegro_gfx_exit(void)
{
	 allegro_exit();
}

void mx_allegro_flush(void)
{
}

void mx_allegro_mouse_show(const int show)
{
	 if (show)
		  show_mouse(screen);
	 else
		  show_mouse(NULL);
}

MxColor mx_allegro_blend(MxColor xx, MxColor yy, unsigned int n)
{
	 return (n > 128) ? yy : xx;
}

MxColor mx_allegro_encode(int index, int r, int g, int b)
{
	 (void) index;
	 return makecol(r, g, b);
}

static MxColor _blend(MxColor x, MxColor y, unsigned int n)
{
}

void mx_allegro_drawing_area(int x1, int y1, int x2, int y2)
{
	 (void) x1;
	 (void) y1;
	 (void) x2;
	 (void) y2;
	 show_mouse(NULL);
}

void mx_allegro_done_drawing_area(void)
{
	 show_mouse(screen);
}

void mx_allegro_region(const MxRegion * const region)
{
	 (void) region;
}

void mx_allegro_screen_destroy(struct MxImage *image)
{
	 (void) image;
}

void mx_allegro_screen_aquire(struct MxImage *image)
{
	 (void) image;
//  _farsetsel(screen->seg);
}

void mx_allegro_screen_release(struct MxImage *image)
{
	 (void) image;
}

int mx_allegro_screen_width(struct MxImage *image)
{
	 (void) image;
	 return SCREEN_W - 1;
}

int mx_allegro_screen_height(struct MxImage *image)
{
	 (void) image;
	 return SCREEN_H - 1;
}

int mx_allegro_screen_depth(struct MxImage *image)
{
	 (void) image;
	 return bitmap_color_depth(screen);
}

void mx_allegro_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 (void) image;
	 putpixel(screen, x1, y1, color);
}

MxColor mx_allegro_screen_get_pixel(struct MxImage *image, int x1, int y1)
{
	 (void) image;
	 return (MxColor) getpixel(screen, x1, y1);
}

void mx_allegro_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 (void) image;
	 hline(screen, x1, y1, x2, color);
}

void mx_allegro_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 (void) image;
	 vline(screen, x1, y1, y2, color);
}

void mx_allegro_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 (void) image;
	 rectfill(screen, x1, y1, x2, y2, color);
}

void mx_allegro_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 (void) image;
	 putpixel(screen, x1, y1, _blend(color, getpixel(screen, x1, y1), alpha));
}

struct MxImage *mx_allegro_image_create(int w, int h)
{
	 return (struct MxImage *) create_bitmap(w, h);
}

struct MxImage *mx_allegro_image_load(const char *filename)
{
	 PALETTE pal;

	 return (struct MxImage *) load_bitmap((char *) filename, pal);
//      return 0;
}

void mx_allegro_image_destroy(struct MxImage *image)
{
	 destroy_bitmap((BITMAP *) image);
}

void mx_allegro_image_aquire(struct MxImage *image)
{
	 (void) image;
}

void mx_allegro_image_release(struct MxImage *image)
{
	 (void) image;
}

int mx_allegro_image_width(struct MxImage *image)
{
	 return ((BITMAP *) image)->w;
}

int mx_allegro_image_height(struct MxImage *image)
{
	 return ((BITMAP *) image)->h;
}

int mx_allegro_image_depth(struct MxImage *image)
{
	 return bitmap_color_depth((BITMAP *) image);
}

void mx_allegro_image_pixel(struct MxImage *image, int x1, int y1, MxColor color)
{
	 putpixel((BITMAP *) image, x1, y1, color);
}

MxColor mx_allegro_image_get_pixel(struct MxImage *image, int x1, int y1)
{
	 return (MxColor) getpixel((BITMAP *) image, x1, y1);
}

void mx_allegro_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color)
{
	 hline((BITMAP *) image, x1, y1, x2, color);
}

void mx_allegro_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color)
{
	 vline((BITMAP *) image, x1, y1, y2, color);
}

void mx_allegro_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color)
{
	 rectfill((BITMAP *) image, x1, y1, x2, y2, color);
}

void mx_allegro_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha)
{
	 putpixel((BITMAP *) image, x1, y1, _blend(color, getpixel((BITMAP *) image, x1, y1), alpha));
}

void mx_allegro_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 blit((BITMAP *) src, (BITMAP *) dest, sx, sy, dx, dy, w + 1, h + 1);
}

void mx_allegro_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) dest;
	 blit((BITMAP *) src, screen, sx, sy, dx, dy, w + 1, h + 1);
}

void mx_allegro_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 blit(screen, (BITMAP *) dest, sx, sy, dx, dy, w + 1, h + 1);
}

void mx_allegro_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h)
{
	 (void) src;
	 (void) dest;
	 blit(screen, screen, sx, sy, dx, dy, w + 1, h + 1);
}

void mx_allegro_decorate(const struct MxDecoration *decoration, int x, int y)
{
	 Mx_Decorate(decoration, x, y, 0, mx_allegro_screen_pixel);
}

struct MxFont *mx_allegro_font_load(const char *name, int points, MxFontFlag flags)
{
	 (void) name;
	 (void) points;
	 (void) flags;
	 return (struct MxFont *) font;
}

void mx_allegro_font_destroy(struct MxFont *f)
{
	 if ((FONT *) f != font)
		  destroy_font((FONT *) f);
}

void mx_allegro_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back)
{
	 unsigned int i;

	 (void) image;

	 text_mode(color == back ? -1 : back);

	 for (i = 0; i < MxRegionNumber(mx_region); i++) {
		  const MxRect *const s = MxRegionRect(mx_region, i);

		  set_clip(screen, s->x1, s->y1, s->x2, s->y2);

		  textout(screen, (FONT *) font, (char *) text, x, y, color);
	 }
	 set_clip(screen, 0, 0, SCREEN_W, SCREEN_H);
}

void mx_allegro_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back)
{
	 if (clip)
		  set_clip((BITMAP *) image, clip->x1, clip->y1, clip->x2, clip->y2);

	 text_mode(color == back ? -1 : back);
	 textout((BITMAP *) image, (FONT *) font, (char *) text, x, y, color);

	 if (clip)
		  set_clip((BITMAP *) image, 0, 0, ((BITMAP *) image)->w, ((BITMAP *) image)->h);
}

unsigned int mx_allegro_font_length(const struct MxFont *font, const char *text)
{
	 if (!text)
		  return 0;

	 return text_length((FONT *) font, (char *) text);
}

unsigned int mx_allegro_font_height(const struct MxFont *font)
{
	 return text_height((FONT *) font);
}
