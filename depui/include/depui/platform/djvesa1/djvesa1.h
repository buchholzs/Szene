#ifndef MX_PLATFORM_DJVESA1_H
#define MX_PLATFORM_DJVESA1_H

#include "depui/support/image.h"

int mx_djvesa1_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_djvesa1_gfx_exit(void);
void mx_djvesa1_flush(void);
MxColor mx_djvesa1_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_djvesa1_encode(int index, int r, int g, int b);
void mx_djvesa1_drawing_area(int x1, int y1, int x2, int y2);
void mx_djvesa1_done_drawing_area(void);
void mx_djvesa1_region(const struct MxRegion *const region);

void mx_djvesa1_screen_destroy(struct MxImage *image);
void mx_djvesa1_screen_aquire(struct MxImage *image);
void mx_djvesa1_screen_release(struct MxImage *image);
int mx_djvesa1_screen_width(struct MxImage *image);
int mx_djvesa1_screen_height(struct MxImage *image);
int mx_djvesa1_screen_depth(struct MxImage *image);

void mx_djvesa1_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_djvesa1_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_djvesa1_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_djvesa1_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_djvesa1_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_djvesa1_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_djvesa1_image_create(int w, int h);
struct MxImage *mx_djvesa1_image_load(const char *filename);
void mx_djvesa1_image_destroy(struct MxImage *image);
void mx_djvesa1_image_aquire(struct MxImage *image);
void mx_djvesa1_image_release(struct MxImage *image);
int mx_djvesa1_image_width(struct MxImage *image);
int mx_djvesa1_image_height(struct MxImage *image);
int mx_djvesa1_image_depth(struct MxImage *image);

void mx_djvesa1_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_djvesa1_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_djvesa1_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_djvesa1_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_djvesa1_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_djvesa1_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_djvesa1_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_djvesa1_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_djvesa1_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_djvesa1_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_djvesa1_decorate(const struct MxDecoration *decorate, int x, int y);

struct MxFont *mx_djvesa1_font_load(const char *name, int points, MxFontFlag flags);
void mx_djvesa1_font_destroy(struct MxFont *f);
void mx_djvesa1_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back);
void mx_djvesa1_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back);
unsigned int mx_djvesa1_font_length(const struct MxFont *font, const char *text);
unsigned int mx_djvesa1_font_height(const struct MxFont *font);

int mx_djvesa1_kbd_init(void);
void mx_djvesa1_kbd_exit(void);

void mx_djvesa1_mouse_show(const int show);
void mx_djvesa1_mouse(int *x, int *y, int *b);

int mx_djvesa1_key_pressed(void);
void mx_djvesa1_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_djvesa1_yield(void);

#define MxDriverSystemDJVESA1                      \
    { mx_djvesa1_yield }

#define MxDriverOutputDJVESA1                      \
	 {mx_djvesa1_gfx_init,                            \
	  mx_djvesa1_gfx_exit,                            \
	  mx_djvesa1_flush,                               \
                                                    \
	  mx_djvesa1_mouse_show,                          \
                                                     \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_djvesa1_blend,                               \
     mx_djvesa1_encode,                              \
                                                    \
	  mx_djvesa1_drawing_area,                        \
	  mx_djvesa1_done_drawing_area,                   \
	  mx_djvesa1_region,                               \
                                                    \
	  /* The screen vtable */                        \
	  {mx_djvesa1_screen_destroy,                     \
		mx_djvesa1_screen_aquire,                      \
		mx_djvesa1_screen_release,                     \
                                                    \
		mx_djvesa1_screen_width,                       \
		mx_djvesa1_screen_height,                      \
		mx_djvesa1_screen_depth,                       \
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
	  {mx_djvesa1_screen_destroy,                     \
		mx_djvesa1_screen_aquire,                      \
		mx_djvesa1_screen_release,                     \
                                                    \
		mx_djvesa1_screen_width,                       \
		mx_djvesa1_screen_height,                      \
		mx_djvesa1_screen_depth,                       \
                                                    \
		mx_djvesa1_screen_pixel,                       \
		mx_djvesa1_screen_get_pixel,                   \
                                                    \
		mx_djvesa1_screen_hline,                       \
		mx_djvesa1_screen_vline,                       \
                                                    \
		mx_djvesa1_screen_rectfill}                    \
	  ,                                              \
     /* The clipped screen trans vtable */           \
	  {mx_djvesa1_screen_trans_pixel},                \
                                                    \
	  mx_djvesa1_image_create,                        \
	  mx_djvesa1_image_load,                          \
                                                    \
	  {Mx_ImageDestroy,                              \
		mx_djvesa1_image_aquire,                       \
		mx_djvesa1_image_release,                      \
                                                    \
		Mx_ImageWidth,                                \
		Mx_ImageHeight,                               \
      Mx_ImageDepth,                                \
                                                    \
		Mx_ImagePixel8Fast,                          \
		Mx_ImageGetPixel8Fast,                       \
                                                    \
		mx_djvesa1_image_hline,                        \
		mx_djvesa1_image_vline,                        \
                                                    \
		mx_djvesa1_image_rectfill},                    \
	  {mx_djvesa1_image_trans_pixel},                 \
                                                    \
	  mx_djvesa1_blit,                                \
	  mx_djvesa1_blit_to_screen,                      \
	  mx_djvesa1_blit_from_screen,                    \
	  mx_djvesa1_blit_screen,                         \
                                                     \
     mx_djvesa1_decorate,                            \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_djvesa1_font_load,                           \
	  mx_djvesa1_font_destroy,                        \
                                                    \
	  mx_djvesa1_font_screen_render,                  \
	  mx_djvesa1_font_image_render,                   \
                                                    \
	  mx_djvesa1_font_length,                         \
	  mx_djvesa1_font_height}

#define MxDriverInputDJVESA1                      \
                                                    \
	 {mx_djvesa1_kbd_init,                            \
	  mx_djvesa1_kbd_exit,                            \
                                                    \
	  mx_djvesa1_key_pressed,                         \
	  mx_djvesa1_key,                                 \
                                                    \
	  mx_djvesa1_mouse}                               \


#define MxDriverSystemDefault MxDriverSystemDJVESA1
#define MxDriverOutputDefault MxDriverOutputDJVESA1
#define MxDriverInputDefault MxDriverInputDJVESA1

#endif
