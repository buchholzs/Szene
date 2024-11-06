#ifndef MX_PLATFORM_PORT_H
#define MX_PLATFORM_PORT_H

#include "depui/support/image.h"

int mx_port_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_port_gfx_exit(void);
void mx_port_flush(void);
MxColor mx_port_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_port_encode(int index, int r, int g, int b);
void mx_port_drawing_area(int x1, int y1, int x2, int y2);
void mx_port_done_drawing_area(void);
void mx_port_region(const struct MxRegion *const region);

void mx_port_screen_destroy(struct MxImage *image);
void mx_port_screen_aquire(struct MxImage *image);
void mx_port_screen_release(struct MxImage *image);
int mx_port_screen_width(struct MxImage *image);
int mx_port_screen_height(struct MxImage *image);
int mx_port_screen_depth(struct MxImage *image);

void mx_port_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_port_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_port_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_port_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_port_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_port_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_port_image_create(int w, int h);
struct MxImage *mx_port_image_load(const char *filename);

//void mx_port_image_destroy(struct MxImage *image);
void mx_port_image_aquire(struct MxImage *image);
void mx_port_image_release(struct MxImage *image);

//int mx_port_image_width(struct MxImage *image);
//int mx_port_image_height(struct MxImage *image);
//int mx_port_image_depth(struct MxImage *image);

//void mx_port_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
//MxColor mx_port_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_port_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_port_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_port_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_port_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_port_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_port_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_port_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_port_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_port_decorate(const struct MxDecoration *decoration, int x, int y);

struct MxFont *mx_port_font_load(const char *name, int points, MxFontFlag flags);
void mx_port_font_destroy(struct MxFont *f);
void mx_port_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
										  MxColor back);
void mx_port_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
										 int y, MxColor color, MxColor back);
unsigned int mx_port_font_length(const struct MxFont *font, const char *text);
unsigned int mx_port_font_height(const struct MxFont *font);

int mx_port_kbd_init(void);
void mx_port_kbd_exit(void);

void mx_port_mouse_show(const int show);
void mx_port_mouse(int *x, int *y, int *b);

int mx_port_key_pressed(void);
void mx_port_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_port_yield(void);

#define MxDriverSystemPort  \
	 {mx_port_yield }

#define MxDriverOutputPort                      \
	 {mx_port_gfx_init,                            \
	  mx_port_gfx_exit,                            \
	  mx_port_flush,                               \
                                                    \
	  mx_port_mouse_show,                          \
                                                           \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_port_blend,                               \
     mx_port_encode,                              \
                                                    \
	  mx_port_drawing_area,                        \
	  mx_port_done_drawing_area,                   \
	  mx_port_region,                                \
                                                    \
	  /* The screen vtable */                        \
	  {mx_port_screen_destroy,                     \
		mx_port_screen_aquire,                      \
		mx_port_screen_release,                     \
                                                    \
		mx_port_screen_width,                       \
		mx_port_screen_height,                      \
		mx_port_screen_depth,                       \
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
	  {mx_port_screen_destroy,                     \
		mx_port_screen_aquire,                      \
		mx_port_screen_release,                     \
                                                    \
		mx_port_screen_width,                       \
		mx_port_screen_height,                      \
		mx_port_screen_depth,                       \
                                                    \
		mx_port_screen_pixel,                       \
		mx_port_screen_get_pixel,                   \
                                                    \
		mx_port_screen_hline,                       \
		mx_port_screen_vline,                       \
                                                    \
		mx_port_screen_rectfill}                    \
	  ,                                              \
	  {mx_port_screen_trans_pixel},                \
                                                    \
	  mx_port_image_create,                        \
	  mx_port_image_load,                          \
                                                    \
	  {Mx_ImageDestroy,                              \
		mx_port_image_aquire,                       \
		mx_port_image_release,                      \
                                                    \
		Mx_ImageWidth,                                \
		Mx_ImageHeight,                               \
      Mx_ImageDepth,                                \
                                                    \
		Mx_ImagePixel24Fast,                          \
		Mx_ImageGetPixel24Fast,                       \
                                                    \
		mx_port_image_hline,                        \
		mx_port_image_vline,                        \
                                                    \
		mx_port_image_rectfill},                    \
	  {mx_port_image_trans_pixel},                 \
                                                    \
	  mx_port_blit,                                \
	  mx_port_blit_to_screen,                      \
	  mx_port_blit_from_screen,                    \
	  mx_port_blit_screen,                         \
                                                    \
     mx_port_decorate,                     \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_port_font_load,                           \
	  mx_port_font_destroy,                        \
                                                    \
	  mx_port_font_screen_render,                  \
	  mx_port_font_image_render,                   \
                                                    \
	  mx_port_font_length,                         \
	  mx_port_font_height}

#define MxDriverInputPort                         \
	 {mx_port_kbd_init,                            \
	  mx_port_kbd_exit,                            \
                                                    \
	  mx_port_key_pressed,                         \
	  mx_port_key,                            \
                                                    \
	  mx_port_mouse}

#define MxDriverSystemDefault MxDriverSystemPort
#define MxDriverOutputDefault MxDriverOutputPort
#define MxDriverInputDefault MxDriverInputPort

#endif
