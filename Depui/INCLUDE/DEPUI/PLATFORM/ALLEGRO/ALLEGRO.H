#ifndef MX_PLATFORM_ALLEGRO_H
#define MX_PLATFORM_ALLEGRO_H

int mx_allegro_gfx_init(MxDriverOutput * driver, int x, int y, int c, const char *title);
void mx_allegro_gfx_exit(void);
void mx_allegro_flush(void);
MxColor mx_allegro_blend(MxColor x, MxColor y, unsigned int n);
MxColor mx_allegro_encode(int index, int r, int g, int b);
void mx_allegro_drawing_area(int x1, int y1, int x2, int y2);
void mx_allegro_done_drawing_area(void);
void mx_allegro_region(const struct MxRegion *const region);

void mx_allegro_screen_destroy(struct MxImage *image);
void mx_allegro_screen_aquire(struct MxImage *image);
void mx_allegro_screen_release(struct MxImage *image);
int mx_allegro_screen_width(struct MxImage *image);
int mx_allegro_screen_height(struct MxImage *image);
int mx_allegro_screen_depth(struct MxImage *image);

void mx_allegro_screen_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_allegro_screen_get_pixel(struct MxImage *image, int x1, int y1);
void mx_allegro_screen_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_allegro_screen_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_allegro_screen_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_allegro_screen_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

struct MxImage *mx_allegro_image_create(int w, int h);
struct MxImage *mx_allegro_image_load(const char *filename);
void mx_allegro_image_destroy(struct MxImage *image);
void mx_allegro_image_aquire(struct MxImage *image);
void mx_allegro_image_release(struct MxImage *image);
int mx_allegro_image_width(struct MxImage *image);
int mx_allegro_image_height(struct MxImage *image);
int mx_allegro_image_depth(struct MxImage *image);

void mx_allegro_image_pixel(struct MxImage *image, int x1, int y1, MxColor color);
MxColor mx_allegro_image_get_pixel(struct MxImage *image, int x1, int y1);
void mx_allegro_image_hline(struct MxImage *image, int x1, int y1, int x2, MxColor color);
void mx_allegro_image_vline(struct MxImage *image, int x1, int y1, int y2, MxColor color);
void mx_allegro_image_rectfill(struct MxImage *image, int x1, int y1, int x2, int y2, MxColor color);
void mx_allegro_image_trans_pixel(struct MxImage *image, int x1, int y1, MxColor color, int alpha);

void mx_allegro_blit(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_allegro_blit_to_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_allegro_blit_from_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);
void mx_allegro_blit_screen(struct MxImage *src, struct MxImage *dest, int sx, int sy, int dx, int dy, int w, int h);

void mx_allegro_decorate(const struct MxDecoration *decoration, int x, int y);

struct MxFont *mx_allegro_font_load(const char *name, int points, MxFontFlag flags);
void mx_allegro_font_destroy(struct MxFont *f);
void mx_allegro_font_screen_render(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											  MxColor back);
void mx_allegro_font_image_render(struct MxImage *image, const char *text, const MxRect * const clip, const struct MxFont *font, int x,
											 int y, MxColor color, MxColor back);
unsigned int mx_allegro_font_length(const struct MxFont *font, const char *text);
unsigned int mx_allegro_font_height(const struct MxFont *font);

int mx_allegro_kbd_init(void);
void mx_allegro_kbd_exit(void);

void mx_allegro_mouse_show(const int show);
void mx_allegro_mouse(int *x, int *y, int *b);

int mx_allegro_key_pressed(void);
void mx_allegro_key(unsigned int *raw, MxKey * key, unsigned int *code);

void mx_allegro_yield(void);

#define MxDriverSystemAllegro  \
	 {mx_allegro_yield }

#define MxDriverOutputAllegro                      \
	 {mx_allegro_gfx_init,                            \
	  mx_allegro_gfx_exit,                            \
	  mx_allegro_flush,                               \
                                                    \
	  mx_allegro_mouse_show,                          \
                                                           \
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* Colours set in GfxInit */ \
     mx_allegro_blend,                               \
     mx_allegro_encode,                              \
                                                    \
	  mx_allegro_drawing_area,                        \
	  mx_allegro_done_drawing_area,                   \
	  mx_allegro_region,                                \
                                                    \
	  /* The screen vtable */                        \
	  {mx_allegro_screen_destroy,                     \
		mx_allegro_screen_aquire,                      \
		mx_allegro_screen_release,                     \
                                                    \
		mx_allegro_screen_width,                       \
		mx_allegro_screen_height,                      \
		mx_allegro_screen_depth,                       \
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
	  {mx_allegro_screen_destroy,                     \
		mx_allegro_screen_aquire,                      \
		mx_allegro_screen_release,                     \
                                                    \
		mx_allegro_screen_width,                       \
		mx_allegro_screen_height,                      \
		mx_allegro_screen_depth,                       \
                                                    \
		mx_allegro_screen_pixel,                       \
		mx_allegro_screen_get_pixel,                   \
                                                    \
		mx_allegro_screen_hline,                       \
		mx_allegro_screen_vline,                       \
                                                    \
		mx_allegro_screen_rectfill}                    \
	  ,                                              \
	  {mx_allegro_screen_trans_pixel},                \
                                                    \
	  mx_allegro_image_create,                        \
	  mx_allegro_image_load,                          \
                                                    \
	  {mx_allegro_image_destroy,                      \
		mx_allegro_image_aquire,                       \
		mx_allegro_image_release,                      \
                                                    \
		mx_allegro_image_width,                        \
		mx_allegro_image_height,                       \
		mx_allegro_image_depth,                        \
                                                    \
		mx_allegro_image_pixel,                        \
		mx_allegro_image_get_pixel,                    \
                                                    \
		mx_allegro_image_hline,                        \
		mx_allegro_image_vline,                        \
                                                    \
		mx_allegro_image_rectfill},                    \
	  {mx_allegro_image_trans_pixel},                 \
                                                    \
	  mx_allegro_blit,                                \
	  mx_allegro_blit_to_screen,                      \
	  mx_allegro_blit_from_screen,                    \
	  mx_allegro_blit_screen,                         \
                                                    \
     mx_allegro_decorate,                     \
                                                    \
	  0,	 							   /* Default font */ \
	  mx_allegro_font_load,                           \
	  mx_allegro_font_destroy,                        \
                                                    \
	  mx_allegro_font_screen_render,                  \
	  mx_allegro_font_image_render,                   \
                                                    \
	  mx_allegro_font_length,                         \
	  mx_allegro_font_height}

#define MxDriverInputAllegro                         \
	 {mx_allegro_kbd_init,                            \
	  mx_allegro_kbd_exit,                            \
                                                    \
	  mx_allegro_key_pressed,                         \
	  mx_allegro_key,                            \
                                                    \
	  mx_allegro_mouse}

#define MxDriverSystemDefault MxDriverSystemAllegro
#define MxDriverOutputDefault MxDriverOutputAllegro
#define MxDriverInputDefault MxDriverInputAllegro

#endif
