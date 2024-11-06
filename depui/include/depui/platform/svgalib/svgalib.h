#ifndef MX_PLATFORM_SVGALIB_H
#define MX_PLATFORM_SVGALIB_H

#include "depui/support/image.h"

int mx_svgalib_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_svgalib_gfx_exit(void);
void mx_svgalib_flush(void);
MxColor mx_svgalib_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_svgalib_encode(int index, int r, int g, int b);
void mx_svgalib_drawing_area(int x1, int y1, int x2, int y2);
void mx_svgalib_done_drawing_area(void);
void mx_svgalib_region(const struct MxRegion *const region);

void mx_svgalib_screen_destroy(struct MxImage *image);
void mx_svgalib_screen_aquire(struct MxImage *image);
void mx_svgalib_screen_release(struct MxImage *image);
int mx_svgalib_screen_width(struct MxImage *image);
int mx_svgalib_screen_height(struct MxImage *image);
int mx_svgalib_screen_depth(struct MxImage *image);

void mx_svgalib_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_svgalib_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_svgalib_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_svgalib_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_svgalib_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_svgalib_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_svgalib_image_create(int w, int h);
struct MxImage *mx_svgalib_image_load(const char *filename);

//void mx_svgalib_image_destroy(struct MxImage *image);
void mx_svgalib_image_aquire(struct MxImage *image);
void mx_svgalib_image_release(struct MxImage *image);

//int mx_svgalib_image_width(struct MxImage *image);
//int mx_svgalib_image_height(struct MxImage *image);
//int mx_svgalib_image_depth(struct MxImage *image);

//void mx_svgalib_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
//MxColor mx_svgalib_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_svgalib_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_svgalib_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_svgalib_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_svgalib_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_svgalib_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_svgalib_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_svgalib_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_svgalib_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_svgalib_decorate(const struct MxDecoration *decoration, int x, int y);

struct MxFont *mx_svgalib_font_load(const char *name, int points, MxFontFlag flags);
void mx_svgalib_font_destroy(struct MxFont *f);
void mx_svgalib_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back);
void mx_svgalib_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back);
unsigned int mx_svgalib_font_length(const struct MxFont *font, const char *text);
unsigned int mx_svgalib_font_height(const struct MxFont *font);

int mx_svgalib_kbd_init(void);
void mx_svgalib_kbd_exit(void);

void mx_svgalib_mouse_show(const int show);
void mx_svgalib_mouse(int *x, int *y, int *b);

int mx_svgalib_key_pressed(void);
void mx_svgalib_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_svgalib_yield(void);

#define MxDriverSystemSvgalib  \
	 {mx_svgalib_yield }

#define MxDriverOutputSvgalib                      \
	 {mx_svgalib_gfx_init,                            \
	  mx_svgalib_gfx_exit,                            \
	  mx_svgalib_flush,                               \
                                                    \
	  mx_svgalib_mouse_show,                          \
                                                           \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_svgalib_blend,                               \
     mx_svgalib_encode,                              \
                                                    \
	  mx_svgalib_drawing_area,                        \
	  mx_svgalib_done_drawing_area,                   \
	  mx_svgalib_region,                                \
                                                    \
	  /* The screen vtable */                        \
	  {mx_svgalib_screen_destroy,                     \
		mx_svgalib_screen_aquire,                      \
		mx_svgalib_screen_release,                     \
                                                    \
		mx_svgalib_screen_width,                       \
		mx_svgalib_screen_height,                      \
		mx_svgalib_screen_depth,                       \
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
	  /* The screen vtable */                        \
	  {mx_svgalib_screen_destroy,                     \
		mx_svgalib_screen_aquire,                      \
		mx_svgalib_screen_release,                     \
                                                    \
		mx_svgalib_screen_width,                       \
		mx_svgalib_screen_height,                      \
		mx_svgalib_screen_depth,                       \
                                                    \
		mx_svgalib_screen_pixel,                       \
		mx_svgalib_screen_get_pixel,                   \
                                                    \
		mx_svgalib_screen_hline,                       \
		mx_svgalib_screen_vline,                       \
                                                    \
		mx_svgalib_screen_rectfill}                    \
	  ,                                              \
	  {mx_svgalib_screen_trans_pixel},                \
                                                    \
	  mx_svgalib_image_create,                        \
	  mx_svgalib_image_load,                          \
                                                    \
	  {Mx_ImageDestroy,                              \
		mx_svgalib_image_aquire,                       \
		mx_svgalib_image_release,                      \
                                                    \
		Mx_ImageWidth,                                \
		Mx_ImageHeight,                               \
      Mx_ImageDepth,                                \
                                                    \
		Mx_ImagePixel24Fast,                          \
		Mx_ImageGetPixel24Fast,                       \
                                                    \
		mx_svgalib_image_hline,                        \
		mx_svgalib_image_vline,                        \
                                                    \
		mx_svgalib_image_rectfill},                    \
	  {mx_svgalib_image_trans_pixel},                 \
                                                    \
	  mx_svgalib_blit,                                \
	  mx_svgalib_blit_to_screen,                      \
	  mx_svgalib_blit_from_screen,                    \
	  mx_svgalib_blit_screen,                         \
                                                    \
     mx_svgalib_decorate,                     \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_svgalib_font_load,                           \
	  mx_svgalib_font_destroy,                        \
                                                    \
	  mx_svgalib_font_screen_render,                  \
	  mx_svgalib_font_image_render,                   \
                                                    \
	  mx_svgalib_font_length,                         \
	  mx_svgalib_font_height}

#define MxDriverInputSvgalib                         \
	 {mx_svgalib_kbd_init,                            \
	  mx_svgalib_kbd_exit,                            \
                                                    \
	  mx_svgalib_key_pressed,                         \
	  mx_svgalib_key,                            \
                                                    \
	  mx_svgalib_mouse}

#define MxDriverSystemDefault MxDriverSystemSvgalib
#define MxDriverOutputDefault MxDriverOutputSvgalib
#define MxDriverInputDefault MxDriverInputSvgalib

#endif
