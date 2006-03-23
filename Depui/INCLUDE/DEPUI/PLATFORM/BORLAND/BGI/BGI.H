#ifndef MX_PLATFORM_BORLAND3_BGI_H
#define MX_PLATFORM_BORLAND3_BGI_H

#include "depui/support/font.h"
#include "depui/support/image.h"

int mx_borland_bgi_gfx_init(MxDriverOutput * platform, int x, int y, int c, const char *title);
void mx_borland_bgi_gfx_exit(void);
void mx_borland_bgi_flush(void);
MxColor mx_borland_bgi_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_borland_bgi_encode(int index, int r, int g, int b);
void mx_borland_bgi_drawing_area(int x1, int y1, int x2, int y2);
void mx_borland_bgi_done_drawing_area(void);
void mx_borland_bgi_region(const struct MxRegion *const region);

void mx_borland_bgi_screen_destroy(struct MxImage *image);
void mx_borland_bgi_screen_aquire(struct MxImage *image);
void mx_borland_bgi_screen_release(struct MxImage *image);
int mx_borland_bgi_screen_width(struct MxImage *image);
int mx_borland_bgi_screen_height(struct MxImage *image);
int mx_borland_bgi_screen_depth(struct MxImage *image);

void mx_borland_bgi_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_borland_bgi_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_borland_bgi_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_borland_bgi_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_borland_bgi_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_borland_bgi_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_borland_bgi_image_create(int w, int h);
struct MxImage *mx_borland_bgi_image_load(const char *filename);
void mx_borland_bgi_image_destroy(struct MxImage *image);
void mx_borland_bgi_image_aquire(struct MxImage *image);
void mx_borland_bgi_image_release(struct MxImage *image);
int mx_borland_bgi_image_width(struct MxImage *image);
int mx_borland_bgi_image_height(struct MxImage *image);
int mx_borland_bgi_image_depth(struct MxImage *image);

void mx_borland_bgi_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_borland_bgi_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_borland_bgi_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_borland_bgi_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_borland_bgi_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_borland_bgi_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_borland_bgi_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_borland_bgi_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_borland_bgi_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_borland_bgi_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_borland_bgi_decorate(const struct MxDecoration *decoration, int x, int y);

struct MxFont *mx_borland_bgi_font_load(const char *name, int points, MxFontFlag flags);
void mx_borland_bgi_font_destroy(struct MxFont *f);
void mx_borland_bgi_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
													MxColor back);
void mx_borland_bgi_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font,
												  int x, int y, MxColor color, MxColor back);
unsigned int mx_borland_bgi_font_length(const struct MxFont *font, const char *text);
unsigned int mx_borland_bgi_font_height(const struct MxFont *font);

int mx_borland_bgi_kbd_init(void);
void mx_borland_bgi_kbd_exit(void);

void mx_borland_bgi_mouse_show(const int show);
void mx_borland_bgi_mouse(int *x, int *y, int *b);

int mx_borland_bgi_key_pressed(void);
void mx_borland_bgi_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_borland_bgi_yield(void);

#define MxDriverSystemBorlandBGI                        \
	 {mx_borland_bgi_yield }

#define MxDriverOutputBorlandBGI												\
	 { mx_borland_bgi_gfx_init,                            \
		mx_borland_bgi_gfx_exit,                            \
		mx_borland_bgi_flush,                               \
																										\
		mx_borland_bgi_mouse_show,                          \
																													\
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },						\
      mx_borland_bgi_blend,                               \
      mx_borland_bgi_encode,                              \
																										\
		mx_borland_bgi_drawing_area,                        \
		mx_borland_bgi_done_drawing_area,                   \
		mx_borland_bgi_region,                               \
																										\
		{mx_borland_bgi_screen_destroy,                     \
		mx_borland_bgi_screen_aquire,                      \
		mx_borland_bgi_screen_release,                     \
																										\
		mx_borland_bgi_screen_width,                       \
		mx_borland_bgi_screen_height,                      \
		mx_borland_bgi_screen_depth,                       \
																										\
		Mx_ScreenPixel,                                \
		Mx_ScreenGetPixel,                             \
																										\
		Mx_ScreenHLine,                               \
		Mx_ScreenVLine,                               \
																										\
		Mx_ScreenRectFill}                            \
		,                                              \
		{Mx_ScreenPixelTrans},                          \
																										\
		{mx_borland_bgi_screen_destroy,                     \
		mx_borland_bgi_screen_aquire,                      \
		mx_borland_bgi_screen_release,                     \
                                                    \
		mx_borland_bgi_screen_width,                       \
		mx_borland_bgi_screen_height,                      \
		mx_borland_bgi_screen_depth,                       \
                                                    \
		mx_borland_bgi_screen_pixel,                       \
		mx_borland_bgi_screen_get_pixel,                   \
																										\
		mx_borland_bgi_screen_hline,                       \
		mx_borland_bgi_screen_vline,                       \
                                                    \
		mx_borland_bgi_screen_rectfill}                    \
	  ,                                              \
		{mx_borland_bgi_screen_trans_pixel},                \
																										\
		mx_borland_bgi_image_create,                        \
		mx_borland_bgi_image_load,                          \
                                                    \
	  {Mx_ImageDestroy,                              \
		mx_borland_bgi_image_aquire,                        \
		mx_borland_bgi_image_release,                       \
                                                          \
		Mx_ImageWidth,                                      \
		Mx_ImageHeight,                                     \
      Mx_ImageDepth,                                      \
																			 \
		Mx_ImagePixel4Fast,                                 \
		Mx_ImageGetPixel4Fast,                              \
																			 \
		mx_borland_bgi_image_hline,                         \
		mx_borland_bgi_image_vline,                         \
																			 \
		mx_borland_bgi_image_rectfill},                     \
		{mx_borland_bgi_image_trans_pixel},                 \
																			 \
		mx_borland_bgi_blit,                                \
		mx_borland_bgi_blit_to_screen,                      \
		mx_borland_bgi_blit_from_screen,                    \
		mx_borland_bgi_blit_screen,                         \
																													\
			mx_borland_bgi_decorate,                            \
																													\
		0,	 							   												       \
		mx_borland_bgi_font_load,                           \
		mx_borland_bgi_font_destroy,                        \
																			 \
		mx_borland_bgi_font_screen_render,                  \
		mx_borland_bgi_font_image_render,                   \
																			 \
		mx_borland_bgi_font_length,                         \
		mx_borland_bgi_font_height}

#define MxDriverInputBorlandBGI                        \
																										\
	 {mx_borland_bgi_kbd_init,                            \
		mx_borland_bgi_kbd_exit,                            \
																										\
		mx_borland_bgi_key_pressed,                         \
		mx_borland_bgi_key,                                 \
																										\
		mx_borland_bgi_mouse}

#define MxDriverSystemDefault MxDriverSystemBorlandBGI
#define MxDriverOutputDefault MxDriverOutputBorlandBGI
#define MxDriverInputDefault MxDriverInputBorlandBGI

#endif
