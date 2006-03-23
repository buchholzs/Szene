#ifndef MX_PLATFORM_DOUBLE_BUFFER_H
#define MX_PLATFORM_DOUBLE_BUFFER_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/platform/platform.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxDriverOutputBuffer {

		  MxDriverOutput output;
		  MxDriverOutput *tobuffer;

	 } MxDriverOutputBuffer;

	 void MxDriverOutputBufferInit(MxDriverOutputBuffer * buff, MxDriverOutput * other);

	 int mx_double_buffer_gfx_init(MxDriverOutput * platform, int x, int y, int c, const char *title);
	 void mx_double_buffer_gfx_exit(void);
	 void mx_double_buffer_flush(void);
	 void mx_double_buffer_mouse_show(const int show);
	 MxColor mx_double_buffer_blend(MxColor x, MxColor y, unsigned int n);
	 MxColor mx_double_buffer_encode(int cindex, int r, int g, int b);

	 void mx_double_buffer_drawing_area(int x1, int y1, int x2, int y2);
	 void mx_double_buffer_done_drawing_area(void);
	 void mx_double_buffer_clip(int x1, int y1, int x2, int y2);
	 void mx_double_buffer_region(const struct MxRegion *const region);

	 void mx_double_buffer_screen_destroy(struct MxImage *image);
	 void mx_double_buffer_screen_aquire(struct MxImage *image);
	 void mx_double_buffer_screen_release(struct MxImage *image);
	 int mx_double_buffer_screen_width(struct MxImage *image);
	 int mx_double_buffer_screen_height(struct MxImage *image);
	 int mx_double_buffer_screen_depth(struct MxImage *image);

	 void mx_double_buffer_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
	 MxColor mx_double_buffer_screen_get_pixel(struct MxImage *image, int x1, int y1);
	 void mx_double_buffer_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
	 void mx_double_buffer_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
	 void mx_double_buffer_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
	 void mx_double_buffer_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

	 void mx_double_buffer_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
	 void mx_double_buffer_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
	 void mx_double_buffer_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
	 void mx_double_buffer_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

	 void mx_double_buffer_decorate(const struct MxDecoration *decoration, int x, int y);

	 struct MxFont *mx_double_buffer_font_load(const char *name, int points, MxFontFlag flags);
	 void mx_double_buffer_font_destroy(struct MxFont *f);
	 void mx_double_buffer_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y,
															MxColor color, MxColor back);
	 unsigned int mx_double_buffer_font_length(const struct MxFont *font, const char *text);
	 unsigned int mx_double_buffer_font_height(const struct MxFont *font);

#define MxDriverOutputDoublebuffer                          \
  { {mx_double_buffer_gfx_init,                            \
	  mx_double_buffer_gfx_exit,                            \
	  mx_double_buffer_flush,                               \
                                                    \
	  mx_double_buffer_mouse_show,                          \
                                                     \
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
     mx_double_buffer_blend,                               \
     mx_double_buffer_encode,                              \
																										\
		mx_double_buffer_drawing_area,                        \
		mx_double_buffer_done_drawing_area,                   \
		mx_double_buffer_region,                               \
																										\
		{mx_double_buffer_screen_destroy,                     \
		mx_double_buffer_screen_aquire,                      \
		mx_double_buffer_screen_release,                     \
                                                    \
		mx_double_buffer_screen_width,                       \
		mx_double_buffer_screen_height,                      \
		mx_double_buffer_screen_depth,                       \
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
		{mx_double_buffer_screen_destroy,                     \
		mx_double_buffer_screen_aquire,                      \
		mx_double_buffer_screen_release,                     \
																										\
		mx_double_buffer_screen_width,                       \
		mx_double_buffer_screen_height,                      \
		mx_double_buffer_screen_depth,                       \
																										\
		mx_double_buffer_screen_pixel,                       \
		mx_double_buffer_screen_get_pixel,                   \
																										\
		mx_double_buffer_screen_hline,                       \
		mx_double_buffer_screen_vline,                       \
																										\
		mx_double_buffer_screen_rectfill}                    \
		,                                              \
		{mx_double_buffer_screen_trans_pixel},                \
																											\
		0,                     \
	  0,                     \
                                                    \
		{0,                     \
		0,                      \
		0,                     \
																										\
		0,                       \
		0,                      \
		0,                       \
																										\
		0,                       \
		0,                   \
																										\
		0,                       \
		0,                       \
																										\
		0}                    \
		,                                              \
		{0},                \
                                                    \
	  mx_double_buffer_blit,                                \
	  mx_double_buffer_blit_to_screen,                      \
	  mx_double_buffer_blit_from_screen,                    \
	  mx_double_buffer_blit_screen,                         \
                                                     \
     mx_double_buffer_decorate,                            \
																										\
		0,																						  \
		mx_double_buffer_font_load,                           \
		mx_double_buffer_font_destroy,                        \
																										\
		mx_double_buffer_font_screen_render,                  \
		0,                   \
																										\
		mx_double_buffer_font_length,                         \
		mx_double_buffer_font_height },                       \
																										\
		0                                   \
		}

#ifdef __cplusplus
}
#endif
#endif
