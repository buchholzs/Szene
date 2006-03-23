#ifndef MX_PLATFORM_GENERIC_H
#define MX_PLATFORM_GENERIC_H

#include "depui/support/image.h"

int mx_generic_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_generic_gfx_exit(void);
void mx_generic_flush(void);
MxColor mx_generic_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_generic_encode(int index, int r, int g, int b);
void mx_generic_drawing_area(int x1, int y1, int x2, int y2);
void mx_generic_done_drawing_area(void);
void mx_generic_region(const struct MxRegion *const region);

void mx_generic_screen_destroy(struct MxImage *image);
void mx_generic_screen_aquire(struct MxImage *image);
void mx_generic_screen_release(struct MxImage *image);
int mx_generic_screen_width(struct MxImage *image);
int mx_generic_screen_height(struct MxImage *image);
int mx_generic_screen_depth(struct MxImage *image);

void mx_generic_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_generic_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_generic_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_generic_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_generic_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_generic_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_generic_image_create(int w, int h);
struct MxImage *mx_generic_image_load(const char *filename);
void mx_generic_image_destroy(struct MxImage *image);
void mx_generic_image_aquire(struct MxImage *image);
void mx_generic_image_release(struct MxImage *image);
int mx_generic_image_width(struct MxImage *image);
int mx_generic_image_height(struct MxImage *image);
int mx_generic_image_depth(struct MxImage *image);

void mx_generic_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_generic_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_generic_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_generic_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_generic_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_generic_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_generic_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_generic_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_generic_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_generic_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_generic_decorate(const struct MxDecoration *decorate, int x, int y);

struct MxFont *mx_generic_font_load(const char *name, int points, MxFontFlag flags);
void mx_generic_font_destroy(struct MxFont *f);
void mx_generic_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back);
void mx_generic_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back);
unsigned int mx_generic_font_length(const struct MxFont *font, const char *text);
unsigned int mx_generic_font_height(const struct MxFont *font);

int mx_generic_kbd_init(void);
void mx_generic_kbd_exit(void);

void mx_generic_mouse_show(const int show);
void mx_generic_mouse(int *x, int *y, int *b);

int mx_generic_key_pressed(void);
void mx_generic_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_generic_yield(void);

#define MxDriverSystemGeneric16                      \
    { mx_generic_yield }

#define MxDriverOutputGeneric16                      \
	 {mx_generic_gfx_init,                            \
	  mx_generic_gfx_exit,                            \
	  mx_generic_flush,                               \
                                                    \
	  mx_generic_mouse_show,                          \
                                                     \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_generic_blend,                               \
     mx_generic_encode,                              \
                                                    \
	  mx_generic_drawing_area,                        \
	  mx_generic_done_drawing_area,                   \
	  mx_generic_region,                               \
                                                    \
	  /* The screen vtable */                        \
	  {mx_generic_screen_destroy,                     \
		mx_generic_screen_aquire,                      \
		mx_generic_screen_release,                     \
                                                    \
		mx_generic_screen_width,                       \
		mx_generic_screen_height,                      \
		mx_generic_screen_depth,                       \
                                                    \
		Mx_ScreenPixel,                                \
		Mx_ScreenGetPixel,                             \
                                                    \
		Mx_ScreenHLine,                               \
		Mx_ScreenVLine,                               \
                                                    \
		Mx_ScreenRectFill}                            \
	  ,                                              \
     /* The screen trans vtable */                  \
	  {Mx_ScreenPixelTrans},                          \
                                                    \
	  /* The clipped screen vtable */                 \
	  {mx_generic_screen_destroy,                     \
		mx_generic_screen_aquire,                      \
		mx_generic_screen_release,                     \
                                                    \
		mx_generic_screen_width,                       \
		mx_generic_screen_height,                      \
		mx_generic_screen_depth,                       \
                                                    \
		mx_generic_screen_pixel,                       \
		mx_generic_screen_get_pixel,                   \
                                                    \
		mx_generic_screen_hline,                       \
		mx_generic_screen_vline,                       \
                                                    \
		mx_generic_screen_rectfill}                    \
	  ,                                              \
     /* The clipped screen trans vtable */           \
	  {mx_generic_screen_trans_pixel},                \
                                                    \
	  mx_generic_image_create,                        \
	  mx_generic_image_load,                          \
                                                    \
	  {Mx_ImageDestroy,                              \
		mx_generic_image_aquire,                       \
		mx_generic_image_release,                      \
                                                    \
		Mx_ImageWidth,                                \
		Mx_ImageHeight,                               \
      Mx_ImageDepth,                                \
                                                    \
		Mx_ImagePixel16Fast,                          \
		Mx_ImageGetPixel16Fast,                       \
                                                    \
		mx_generic_image_hline,                        \
		mx_generic_image_vline,                        \
                                                    \
		mx_generic_image_rectfill},                    \
	  {mx_generic_image_trans_pixel},                 \
                                                    \
	  mx_generic_blit,                                \
	  mx_generic_blit_to_screen,                      \
	  mx_generic_blit_from_screen,                    \
	  mx_generic_blit_screen,                         \
                                                     \
     mx_generic_decorate,                            \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_generic_font_load,                           \
	  mx_generic_font_destroy,                        \
                                                    \
	  mx_generic_font_screen_render,                  \
	  mx_generic_font_image_render,                   \
                                                    \
	  mx_generic_font_length,                         \
	  mx_generic_font_height}

#define MxDriverInputGeneric16                      \
                                                    \
	 {mx_generic_kbd_init,                            \
	  mx_generic_kbd_exit,                            \
                                                    \
	  mx_generic_key_pressed,                         \
	  mx_generic_key,                                 \
                                                    \
	  mx_generic_mouse}

#define MxDriverSystemDefault MxDriverSystemGeneric16
#define MxDriverOutputDefault MxDriverOutputGeneric16
#define MxDriverInputDefault MxDriverInputGeneric16

#endif
