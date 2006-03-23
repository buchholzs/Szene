#ifndef MX_PLATFORM_TINYPTC_H
#define MX_PLATFORM_TINYPTC_H

#include "depui/platform/support/image.h"

int mx_tinyptc_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_tinyptc_gfx_exit(void);
void mx_tinyptc_flush(void);
MxColor mx_tinyptc_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_tinyptc_encode(int index, int r, int g, int b);
void mx_tinyptc_drawing_area(int x1, int y1, int x2, int y2);
void mx_tinyptc_done_drawing_area(void);
void mx_tinyptc_region(const struct MxRegion *const region);

void mx_tinyptc_screen_destroy(struct MxImage *image);
void mx_tinyptc_screen_aquire(struct MxImage *image);
void mx_tinyptc_screen_release(struct MxImage *image);
int mx_tinyptc_screen_width(struct MxImage *image);
int mx_tinyptc_screen_height(struct MxImage *image);
int mx_tinyptc_screen_depth(struct MxImage *image);

void mx_tinyptc_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_tinyptc_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_tinyptc_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_tinyptc_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_tinyptc_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_tinyptc_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_tinyptc_image_create(int w, int h);
struct MxImage *mx_tinyptc_image_load(const char *filename);
void mx_tinyptc_image_destroy(struct MxImage *image);
void mx_tinyptc_image_aquire(struct MxImage *image);
void mx_tinyptc_image_release(struct MxImage *image);
int mx_tinyptc_image_width(struct MxImage *image);
int mx_tinyptc_image_height(struct MxImage *image);
int mx_tinyptc_image_depth(struct MxImage *image);

void mx_tinyptc_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_tinyptc_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_tinyptc_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_tinyptc_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_tinyptc_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_tinyptc_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_tinyptc_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_tinyptc_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_tinyptc_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_tinyptc_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_tinyptc_decorate(const struct MxDecoration *decorate, int x, int y);

struct MxFont *mx_tinyptc_font_load(const char *name, int points, MxFontFlag flags);
void mx_tinyptc_font_destroy(struct MxFont *f);
void mx_tinyptc_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back);
void mx_tinyptc_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back);
unsigned int mx_tinyptc_font_length(const struct MxFont *font, const char *text);
unsigned int mx_tinyptc_font_height(const struct MxFont *font);

int mx_tinyptc_kbd_init(void);
void mx_tinyptc_kbd_exit(void);

void mx_tinyptc_mouse_show(const int show);
void mx_tinyptc_mouse(int *x, int *y, int *b);

int mx_tinyptc_key_pressed(void);
void mx_tinyptc_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_tinyptc_yield(void);

#define MxDriverSystemTinyPTC                      \
    { mx_tinyptc_yield }

#define MxDriverOutputTinyPTC                      \
	 {mx_tinyptc_gfx_init,                            \
	  mx_tinyptc_gfx_exit,                            \
	  mx_tinyptc_flush,                               \
                                                    \
	  mx_tinyptc_mouse_show,                          \
                                                     \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_tinyptc_blend,                               \
     mx_tinyptc_encode,                              \
                                                    \
	  mx_tinyptc_drawing_area,                        \
	  mx_tinyptc_done_drawing_area,                   \
	  mx_tinyptc_region,                               \
                                                    \
	  /* The screen vtable */                        \
	  {mx_tinyptc_screen_destroy,                     \
		mx_tinyptc_screen_aquire,                      \
		mx_tinyptc_screen_release,                     \
                                                    \
		mx_tinyptc_screen_width,                       \
		mx_tinyptc_screen_height,                      \
		mx_tinyptc_screen_depth,                       \
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
	  {mx_tinyptc_screen_destroy,                     \
		mx_tinyptc_screen_aquire,                      \
		mx_tinyptc_screen_release,                     \
                                                    \
		mx_tinyptc_screen_width,                       \
		mx_tinyptc_screen_height,                      \
		mx_tinyptc_screen_depth,                       \
                                                    \
		mx_tinyptc_screen_pixel,                       \
		mx_tinyptc_screen_get_pixel,                   \
                                                    \
		mx_tinyptc_screen_hline,                       \
		mx_tinyptc_screen_vline,                       \
                                                    \
		mx_tinyptc_screen_rectfill}                    \
	  ,                                              \
     /* The clipped screen trans vtable */           \
	  {mx_tinyptc_screen_trans_pixel},                \
                                                    \
	  mx_tinyptc_image_create,                        \
	  mx_tinyptc_image_load,                          \
                                                    \
	  {Mx_ImageDestroy,                              \
		mx_tinyptc_image_aquire,                       \
		mx_tinyptc_image_release,                      \
                                                    \
		Mx_ImageWidth,                                \
		Mx_ImageHeight,                               \
      Mx_ImageDepth,                                \
                                                    \
		Mx_ImagePixel32Fast,                          \
		Mx_ImageGetPixel32Fast,                       \
                                                    \
		mx_tinyptc_image_hline,                        \
		mx_tinyptc_image_vline,                        \
                                                    \
		mx_tinyptc_image_rectfill},                    \
	  {mx_tinyptc_image_trans_pixel},                 \
                                                    \
	  mx_tinyptc_blit,                                \
	  mx_tinyptc_blit_to_screen,                      \
	  mx_tinyptc_blit_from_screen,                    \
	  mx_tinyptc_blit_screen,                         \
                                                     \
     mx_tinyptc_decorate,                            \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_tinyptc_font_load,                           \
	  mx_tinyptc_font_destroy,                        \
                                                    \
	  mx_tinyptc_font_screen_render,                  \
	  mx_tinyptc_font_image_render,                   \
                                                    \
	  mx_tinyptc_font_length,                         \
	  mx_tinyptc_font_height}

#define MxDriverInputTinyPTC                      \
                                                    \
	 {mx_tinyptc_kbd_init,                            \
	  mx_tinyptc_kbd_exit,                            \
                                                    \
	  mx_tinyptc_key_pressed,                         \
	  mx_tinyptc_key,                                 \
                                                    \
	  mx_tinyptc_mouse}

#define MxDriverSystemDefault MxDriverSystemTinyPTC
#define MxDriverOutputDefault MxDriverOutputTinyPTC
#define MxDriverInputDefault MxDriverInputTinyPTC

#endif
