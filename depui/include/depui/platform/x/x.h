#ifndef MX_PLATFORM_X_H
#define MX_PLATFORM_X_H

int mx_x_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_x_gfx_exit(void);
void mx_x_flush(void);
MxColor mx_x_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_x_encode(int index, int r, int g, int b);
void mx_x_drawing_area(int x1, int y1, int x2, int y2);
void mx_x_done_drawing_area(void);
void mx_x_region(const struct MxRegion *const region);

void mx_x_screen_destroy(struct MxImage *image);
void mx_x_screen_aquire(struct MxImage *image);
void mx_x_screen_release(struct MxImage *image);
int mx_x_screen_width(struct MxImage *image);
int mx_x_screen_height(struct MxImage *image);
int mx_x_screen_depth(struct MxImage *image);

void mx_x_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_x_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_x_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_x_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_x_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_x_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_x_image_create(int w, int h);
struct MxImage *mx_x_image_load(const char *filename);
void mx_x_image_destroy(struct MxImage *image);
void mx_x_image_aquire(struct MxImage *image);
void mx_x_image_release(struct MxImage *image);
int mx_x_image_width(struct MxImage *image);
int mx_x_image_height(struct MxImage *image);
int mx_x_image_depth(struct MxImage *image);

void mx_x_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_x_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_x_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_x_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_x_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_x_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_x_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_x_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_x_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_x_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_x_decorate(const struct MxDecoration *decoration, int x, int y);

struct MxFont *mx_x_font_load(const char *name, int points, MxFontFlag flags);
void mx_x_font_destroy(struct MxFont *f);
void mx_x_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,

									  MxColor back);
void mx_x_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
									 int y, MxColor color, MxColor back);
unsigned int mx_x_font_length(const struct MxFont *font, const char *text);
unsigned int mx_x_font_height(const struct MxFont *font);

int mx_x_kbd_init(void);
void mx_x_kbd_exit(void);

void mx_x_mouse_show(const int show);
void mx_x_mouse(int *x, int *y, int *b);

int mx_x_key_pressed(void);
void mx_x_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_x_yield(void);

#define MxDriverSystemX  \
	 {mx_x_yield }

#define MxDriverOutputX                      \
	 {mx_x_gfx_init,                            \
	  mx_x_gfx_exit,                            \
	  mx_x_flush,                               \
                                                    \
	  mx_x_mouse_show,                          \
                                                           \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_x_blend,                               \
     mx_x_encode,                              \
                                                    \
	  mx_x_drawing_area,                        \
	  mx_x_done_drawing_area,                   \
	  mx_x_region,                                \
                                                    \
	  /* The screen vtable */                        \
	  {mx_x_screen_destroy,                     \
		mx_x_screen_aquire,                      \
		mx_x_screen_release,                     \
                                                    \
		mx_x_screen_width,                       \
		mx_x_screen_height,                      \
		mx_x_screen_depth,                       \
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
	  {mx_x_screen_destroy,                     \
		mx_x_screen_aquire,                      \
		mx_x_screen_release,                     \
                                                    \
		mx_x_screen_width,                       \
		mx_x_screen_height,                      \
		mx_x_screen_depth,                       \
                                                    \
		mx_x_screen_pixel,                       \
		mx_x_screen_get_pixel,                   \
                                                    \
		mx_x_screen_hline,                       \
		mx_x_screen_vline,                       \
                                                    \
		mx_x_screen_rectfill}                    \
	  ,                                              \
	  {mx_x_screen_trans_pixel},                \
                                                    \
	  mx_x_image_create,                        \
	  mx_x_image_load,                          \
                                                    \
	  {mx_x_image_destroy,                      \
		mx_x_image_aquire,                       \
		mx_x_image_release,                      \
                                                    \
		mx_x_image_width,                        \
		mx_x_image_height,                       \
		mx_x_image_depth,                        \
                                                    \
		mx_x_image_pixel,                        \
		mx_x_image_get_pixel,                    \
                                                    \
		mx_x_image_hline,                        \
		mx_x_image_vline,                        \
                                                    \
		mx_x_image_rectfill},                    \
	  {mx_x_image_trans_pixel},                 \
                                                    \
	  mx_x_blit,                                \
	  mx_x_blit_to_screen,                      \
	  mx_x_blit_from_screen,                    \
	  mx_x_blit_screen,                         \
                                                    \
     mx_x_decorate,                     \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_x_font_load,                           \
	  mx_x_font_destroy,                        \
                                                    \
	  mx_x_font_screen_render,                  \
	  mx_x_font_image_render,                   \
                                                    \
	  mx_x_font_length,                         \
	  mx_x_font_height}

#define MxDriverInputX                             \
	 {mx_x_kbd_init,                            \
	  mx_x_kbd_exit,                            \
                                                    \
	  mx_x_key_pressed,                         \
	  mx_x_key,                            \
                                                    \
	  mx_x_mouse}

#define MxDriverSystemDefault MxDriverSystemX
#define MxDriverOutputDefault MxDriverOutputX
#define MxDriverInputDefault MxDriverInputX

#endif
