#ifndef MX_PLATFORM_GRX_H
#define MX_PLATFORM_GRX_H

int mx_grx_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_grx_gfx_exit(void);
void mx_grx_flush(void);
MxColor mx_grx_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_grx_encode(int index, int r, int g, int b);
void mx_grx_drawing_area(int x1, int y1, int x2, int y2);
void mx_grx_done_drawing_area(void);
void mx_grx_region(const struct MxRegion *const region);

void mx_grx_screen_destroy(struct MxImage *image);
void mx_grx_screen_aquire(struct MxImage *image);
void mx_grx_screen_release(struct MxImage *image);
int mx_grx_screen_width(struct MxImage *image);
int mx_grx_screen_height(struct MxImage *image);
int mx_grx_screen_depth(struct MxImage *image);

void mx_grx_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_grx_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_grx_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_grx_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_grx_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_grx_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_grx_image_create(int w, int h);
struct MxImage *mx_grx_image_load(const char *filename);
void mx_grx_image_destroy(struct MxImage *image);
void mx_grx_image_aquire(struct MxImage *image);
void mx_grx_image_release(struct MxImage *image);
int mx_grx_image_width(struct MxImage *image);
int mx_grx_image_height(struct MxImage *image);
int mx_grx_image_depth(struct MxImage *image);

void mx_grx_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_grx_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_grx_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_grx_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_grx_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_grx_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_grx_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_grx_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_grx_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_grx_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_grx_decorate(const struct MxDecoration *decoration, int x, int y);

struct MxFont *mx_grx_font_load(const char *name, int points, MxFontFlag flags);
void mx_grx_font_destroy(struct MxFont *f);
void mx_grx_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,

										 MxColor back);
void mx_grx_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
										int y, MxColor color, MxColor back);
unsigned int mx_grx_font_length(const struct MxFont *font, const char *text);
unsigned int mx_grx_font_height(const struct MxFont *font);

int mx_grx_kbd_init(void);
void mx_grx_kbd_exit(void);

void mx_grx_mouse_show(const int show);
void mx_grx_mouse(int *x, int *y, int *b, int *key);

int mx_grx_key_pressed(void);
void mx_grx_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_grx_yield(void);

#define MxDriverSystemGRX  \
	 {mx_grx_yield }

#define MxDriverOutputGRX                      \
	 {mx_grx_gfx_init,                            \
	  mx_grx_gfx_exit,                            \
	  mx_grx_flush,                               \
                                                    \
	  mx_grx_mouse_show,                          \
                                                           \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_grx_blend,                               \
     mx_grx_encode,                              \
                                                    \
	  mx_grx_drawing_area,                        \
	  mx_grx_done_drawing_area,                   \
	  mx_grx_region,                                \
                                                    \
	  /* The screen vtable */                        \
	  {mx_grx_screen_destroy,                     \
		mx_grx_screen_aquire,                      \
		mx_grx_screen_release,                     \
                                                    \
		mx_grx_screen_width,                       \
		mx_grx_screen_height,                      \
		mx_grx_screen_depth,                       \
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
	  {mx_grx_screen_destroy,                     \
		mx_grx_screen_aquire,                      \
		mx_grx_screen_release,                     \
                                                    \
		mx_grx_screen_width,                       \
		mx_grx_screen_height,                      \
		mx_grx_screen_depth,                       \
                                                    \
		mx_grx_screen_pixel,                       \
		mx_grx_screen_get_pixel,                   \
                                                    \
		mx_grx_screen_hline,                       \
		mx_grx_screen_vline,                       \
                                                    \
		mx_grx_screen_rectfill}                    \
	  ,                                              \
	  {mx_grx_screen_trans_pixel},                \
                                                    \
	  mx_grx_image_create,                        \
	  mx_grx_image_load,                          \
                                                    \
	  {mx_grx_image_destroy,                      \
		mx_grx_image_aquire,                       \
		mx_grx_image_release,                      \
                                                    \
		mx_grx_image_width,                        \
		mx_grx_image_height,                       \
		mx_grx_image_depth,                        \
                                                    \
		mx_grx_image_pixel,                        \
		mx_grx_image_get_pixel,                    \
                                                    \
		mx_grx_image_hline,                        \
		mx_grx_image_vline,                        \
                                                    \
		mx_grx_image_rectfill},                    \
	  {mx_grx_image_trans_pixel},                 \
                                                    \
	  mx_grx_blit,                                \
	  mx_grx_blit_to_screen,                      \
	  mx_grx_blit_from_screen,                    \
	  mx_grx_blit_screen,                         \
                                                    \
     mx_grx_decorate,                     \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_grx_font_load,                           \
	  mx_grx_font_destroy,                        \
                                                    \
	  mx_grx_font_screen_render,                  \
	  mx_grx_font_image_render,                   \
                                                    \
	  mx_grx_font_length,                         \
	  mx_grx_font_height}

#define MxDriverInputGRX                         \
	 {mx_grx_kbd_init,                            \
	  mx_grx_kbd_exit,                            \
                                                    \
	  mx_grx_key_pressed,                         \
	  mx_grx_key,                            \
                                                    \
	  mx_grx_mouse}

#define MxDriverSystemDefault MxDriverSystemGRX
#define MxDriverOutputDefault MxDriverOutputGRX
#define MxDriverInputDefault MxDriverInputGRX

#endif
