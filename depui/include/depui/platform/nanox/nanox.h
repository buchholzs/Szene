#ifndef MX_PLATFORM_NANOX_H
#define MX_PLATFORM_NANOX_H

int mx_nanox_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_nanox_gfx_exit(void);
void mx_nanox_flush(void);
MxColor mx_nanox_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_nanox_encode(int index, int r, int g, int b);
void mx_nanox_drawing_area(int x1, int y1, int x2, int y2);
void mx_nanox_done_drawing_area(void);
void mx_nanox_region(const struct MxRegion *const region);

void mx_nanox_screen_destroy(struct MxImage *image);
void mx_nanox_screen_aquire(struct MxImage *image);
void mx_nanox_screen_release(struct MxImage *image);
int mx_nanox_screen_width(struct MxImage *image);
int mx_nanox_screen_height(struct MxImage *image);
int mx_nanox_screen_depth(struct MxImage *image);

void mx_nanox_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_nanox_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_nanox_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_nanox_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_nanox_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_nanox_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_nanox_image_create(int w, int h);
struct MxImage *mx_nanox_image_load(const char *filename);
void mx_nanox_image_destroy(struct MxImage *image);
void mx_nanox_image_aquire(struct MxImage *image);
void mx_nanox_image_release(struct MxImage *image);
int mx_nanox_image_width(struct MxImage *image);
int mx_nanox_image_height(struct MxImage *image);
int mx_nanox_image_depth(struct MxImage *image);

void mx_nanox_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_nanox_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_nanox_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_nanox_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_nanox_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_nanox_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_nanox_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_nanox_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_nanox_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_nanox_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_nanox_decorate(const struct MxDecoration *decoration, int x, int y);

struct MxFont *mx_nanox_font_load(const char *name, int points, MxFontFlag flags);
void mx_nanox_font_destroy(struct MxFont *f);
void mx_nanox_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											MxColor back);
void mx_nanox_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
										  int y, MxColor color, MxColor back);
unsigned int mx_nanox_font_length(const struct MxFont *font, const char *text);
unsigned int mx_nanox_font_height(const struct MxFont *font);

int mx_nanox_kbd_init(void);
void mx_nanox_kbd_exit(void);

void mx_nanox_mouse_show(const int show);
void mx_nanox_mouse(int *x, int *y, int *b);

int mx_nanox_key_pressed(void);
void mx_nanox_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_nanox_yield(void);

#define MxDriverSystemNanox  \
	 {mx_nanox_yield }

#define MxDriverOutputNanox                      \
	 {mx_nanox_gfx_init,                            \
	  mx_nanox_gfx_exit,                            \
	  mx_nanox_flush,                               \
                                                    \
	  mx_nanox_mouse_show,                          \
                                                           \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_nanox_blend,                               \
     mx_nanox_encode,                              \
                                                    \
	  mx_nanox_drawing_area,                        \
	  mx_nanox_done_drawing_area,                   \
	  mx_nanox_region,                                \
                                                    \
	  /* The screen vtable */                        \
	  {mx_nanox_screen_destroy,                     \
		mx_nanox_screen_aquire,                      \
		mx_nanox_screen_release,                     \
                                                    \
		mx_nanox_screen_width,                       \
		mx_nanox_screen_height,                      \
		mx_nanox_screen_depth,                       \
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
	  {mx_nanox_screen_destroy,                     \
		mx_nanox_screen_aquire,                      \
		mx_nanox_screen_release,                     \
                                                    \
		mx_nanox_screen_width,                       \
		mx_nanox_screen_height,                      \
		mx_nanox_screen_depth,                       \
                                                    \
		mx_nanox_screen_pixel,                       \
		mx_nanox_screen_get_pixel,                   \
                                                    \
		mx_nanox_screen_hline,                       \
		mx_nanox_screen_vline,                       \
                                                    \
		mx_nanox_screen_rectfill}                    \
	  ,                                              \
	  {mx_nanox_screen_trans_pixel},                \
                                                    \
	  mx_nanox_image_create,                        \
	  mx_nanox_image_load,                          \
                                                    \
	  {mx_nanox_image_destroy,                      \
		mx_nanox_image_aquire,                       \
		mx_nanox_image_release,                      \
                                                    \
		mx_nanox_image_width,                        \
		mx_nanox_image_height,                       \
		mx_nanox_image_depth,                        \
                                                    \
		mx_nanox_image_pixel,                        \
		mx_nanox_image_get_pixel,                    \
                                                    \
		mx_nanox_image_hline,                        \
		mx_nanox_image_vline,                        \
                                                    \
		mx_nanox_image_rectfill},                    \
	  {mx_nanox_image_trans_pixel},                 \
                                                    \
	  mx_nanox_blit,                                \
	  mx_nanox_blit_to_screen,                      \
	  mx_nanox_blit_from_screen,                    \
	  mx_nanox_blit_screen,                         \
                                                    \
     mx_nanox_decorate,                     \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_nanox_font_load,                           \
	  mx_nanox_font_destroy,                        \
                                                    \
	  mx_nanox_font_screen_render,                  \
	  mx_nanox_font_image_render,                   \
                                                    \
	  mx_nanox_font_length,                         \
	  mx_nanox_font_height}

#define MxDriverInputNanox                         \
	 {mx_nanox_kbd_init,                            \
	  mx_nanox_kbd_exit,                            \
                                                    \
	  mx_nanox_key_pressed,                         \
	  mx_nanox_key,                            \
                                                    \
	  mx_nanox_mouse}

#define MxDriverSystemDefault MxDriverSystemNanox
#define MxDriverOutputDefault MxDriverOutputNanox
#define MxDriverInputDefault MxDriverInputNanox

#endif
