#include "depui/config.h"

#ifdef MX_NEED_MOUSE
#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/support/mouse.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"
#include "depui/desktop/desktop.h"
#include "depui/draw/draw.h"

#define MOUSE_H  16
#define MOUSE_W  10

static unsigned char mouse_pointer[MOUSE_H][MOUSE_W] = {
	 {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	 {1, 7, 1, 0, 0, 0, 0, 0, 0, 0},
	 {1, 7, 7, 1, 0, 0, 0, 0, 0, 0},
	 {1, 7, 7, 7, 1, 0, 0, 0, 0, 0},
	 {1, 7, 7, 7, 7, 1, 0, 0, 0, 0},
	 {1, 7, 7, 7, 7, 7, 1, 0, 0, 0},
	 {1, 7, 7, 7, 7, 7, 7, 1, 0, 0},
	 {1, 7, 7, 7, 7, 7, 7, 7, 1, 0},
	 {1, 7, 7, 7, 7, 7, 7, 7, 7, 1},
	 {1, 7, 7, 7, 7, 7, 1, 1, 1, 0},
	 {1, 7, 7, 1, 7, 7, 1, 0, 0, 0},
	 {1, 7, 1, 0, 1, 7, 7, 1, 0, 0},
	 {0, 1, 0, 0, 1, 7, 7, 1, 0, 0},
	 {0, 0, 0, 0, 0, 1, 7, 7, 1, 0},
	 {0, 0, 0, 0, 0, 1, 7, 7, 1, 0},
	 {0, 0, 0, 0, 0, 0, 1, 1, 0, 0}
};

static MxColor buffer1[MOUSE_H][MOUSE_W];
static MxColor buffer2[MOUSE_H][MOUSE_W];

static int mouse_x, mouse_y;

static unsigned char active_buffer = 0;
static unsigned char mouse_visible = 0;

#define ACTIVE        (active_buffer ? buffer1 : buffer2)
#define PASSIVE       (active_buffer ? buffer2 : buffer1)

static void _draw_background(MxColor active[][MOUSE_W], MxColor passive[][MOUSE_W], int mx, int my, int x, int y,
									  MxImagePixelFunc pixel)
{
	 int i, j;
	 MxPixelClipFunc dopixel = mx_pixel;
	 const MxRect *const clip = &mx_desk->position;

	 if (!MxRectClipped(clip->x1, clip->y1, clip->x2, clip->y2, mx, my, mx + MOUSE_W, my + MOUSE_H))
		  dopixel = mx_pixel_fast;

	 for (j = 0; j < MOUSE_H; j++) {
		  const int jy = j + y;

		  for (i = 0; i < MOUSE_W; i++) {

				if (mouse_pointer[j][i]) {
					 const int ix = i + x;

					 /* We are overlapping with the old mouse */
					 if ((passive) && ((ix) >= 0) && ((ix) < MOUSE_W)
						  && ((jy) >= 0) && ((jy) < MOUSE_H)) {

						  /* Correct the background behind the cursor */
						  if (mouse_pointer[jy][ix])
								passive[jy][ix] = active[j][i];

						  /* Draw the background where the new mouse is not */
						  else
								dopixel(0, mx + i, my + j, active[j][i], clip, pixel);

						  /* We don't overlap with the old mouse, just draw the
						     background */
					 } else
						  dopixel(0, mx + i, my + j, active[j][i], clip, pixel);
				}
		  }
	 }
}

static void _draw_mouse(MxColor buffer[][MOUSE_W], int mx, int my, MxImagePixelFunc pixel, MxImageGetPixelFunc getpixel)
{
	 int i, j;

	 MxPixelClipFunc dopixel = mx_pixel;
	 MxGetPixelClipFunc dogetpixel = mx_get_pixel;
	 const MxRect *const clip = &mx_desk->position;

	 if (!MxRectClipped(clip->x1, clip->y1, clip->x2, clip->y2, mx, my, mx + MOUSE_W, my + MOUSE_H)) {
		  dopixel = mx_pixel_fast, dogetpixel = mx_get_pixel_fast;
	 }

	 for (j = 0; j < MOUSE_H; j++) {
		  for (i = 0; i < MOUSE_W; i++) {

				const int col = mouse_pointer[j][i];

				if (col) {

					 buffer[j][i] = dogetpixel(0, mx + i, my + j, getpixel);
					 dopixel(0, mx + i, my + j, mx_output->colors[col - 1], clip, pixel);
				}
		  }
	 }
}

void Mx_MouseShow(int show, MxImagePixelFunc pixel, MxImageGetPixelFunc getpixel)
{
	 /* Do nothing if what we are asking for is already true */
	 if (show == mouse_visible)
		  return;

	 mx_output->screen_vtable.Aquire(0);

	 /* The mouse is hidden, we must show it */
	 if (show)
		  _draw_mouse(ACTIVE, mouse_x, mouse_y, pixel, getpixel);

	 /* The mouse is visible, hide it */
	 else
		  _draw_background(ACTIVE, 0, mouse_x, mouse_y, 0, 0, pixel);

	 mx_output->screen_vtable.Release(0);

	 mouse_visible = show;
}

void Mx_MouseMove(int x, int y, MxImagePixelFunc pixel, MxImageGetPixelFunc getpixel)
{
	 /* If nothing has changed, do nothing */
	 if ((x == mouse_x) && (y == mouse_y))
		  return;

	 /* If the mouse is not visible, do nothing */
	 if (mouse_visible) {

		  const int mx1 = mouse_x, my1 = mouse_y, mx2 = mouse_x + MOUSE_H, my2 = mouse_y + MOUSE_W;

		  int nx1 = x, ny1 = y, nx2 = x + MOUSE_H, ny2 = y + MOUSE_W;

		  mx_output->screen_vtable.Aquire(0);

		  /* If the two positions don't overlap, just draw on the screen */
#ifndef GRX_BUG256C
		  if (MxClipRect(mx1, my1, mx2, my2, nx1, ny1, nx2, ny2)) {

				_draw_background(ACTIVE, 0, mouse_x, mouse_y, 0, 0, pixel);
				_draw_mouse(ACTIVE, x, y, pixel, getpixel);

				/* The mouse positions do overlap, so double buffer them */
		  } else {

				_draw_mouse(PASSIVE, x, y, pixel, getpixel);
				_draw_background(ACTIVE, PASSIVE, mouse_x, mouse_y, mouse_x - x, mouse_y - y, pixel);

				active_buffer = active_buffer ? 0 : 1;
		  }

		  mx_output->screen_vtable.Release(0);
	 }
#else
		 MxRect rect = {mouse_x - 5, mouse_y - 5, mouse_x + MOUSE_W + 5, mouse_y + MOUSE_H + 5};
		 /* Remember where we put the mouse */	 
		 int n_mouse_x = x, n_mouse_y = y;
		 mouse_x = x, mouse_y = y;
		 MxRefreshRect(&rect);
		 _draw_mouse(ACTIVE, n_mouse_x, n_mouse_y, pixel, getpixel);
	 }
#endif
	 /* Remember where we put the mouse */
	 mouse_x = x, mouse_y = y;
}

#else
extern int mx_ignore_this;

#endif
