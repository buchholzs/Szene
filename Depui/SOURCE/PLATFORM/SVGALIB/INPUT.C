#include "depui/platform/platform.h"
#include "depui/desktop/driver.h"
#include "depui/support/mouse.h"
#include <vga.h>
#include <vgagl.h>
#include <vgamouse.h>
#include <vgakeyboard.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

extern MxRect mx_mouseclip;

int mx_svgalib_kbd_init(void)
{
	 struct MouseCaps caps;

	 vga_setmousesupport(1);
//    mouse_init("/dev/gpmdata", MOUSE_MOUSESYSTEMS, MOUSE_DEFAULTSAMPLERATE);

	 mouse_getcaps(&caps);

	 return 1;
}

void mx_svgalib_kbd_exit(void)
{
//    vga_setmousesupport(0);
//    mouse_close();
}

void mx_svgalib_mouse(int *x, int *y, int *b)
{
	 int button;

	 /* Poll the mouse */
	 mouse_update();
	 mouse_getposition_6d(x, y, NULL, NULL, NULL, NULL);
	 *x = mouse_getx();
	 *y = mouse_gety();

	 button = mouse_getbutton();

	 *b = 0;
	 if (button & MOUSE_LEFTBUTTON)
		  *b |= 0x01;
	 if (button & MOUSE_RIGHTBUTTON)
		  *b |= 0x02;
	 if (button & MOUSE_MIDDLEBUTTON)
		  *b |= 0x04;

	 Mx_MouseMove(*x, *y, mx_svgalib_screen_pixel, mx_svgalib_screen_get_pixel);
}

static int lastkey;

int mx_svgalib_key_pressed(void)
{
	 /* Poll the keyboard */
	 keyboard_update();

	 lastkey = vga_getkey();
	 return lastkey != 0;
}

static int check_first_byte(int k, MxKey * key, unsigned int *raw)
{
//   printf("first %li\n", k);
	 switch (k) {

	 case 27:
		  return 1;

	 case 127:						  /* For backspace */
		  *key = 0;
		  *raw = 0x08;
		  return 0;

	 default:
		  return 0;
	 }
}

static int check_second_byte(int k, MxKey * key, unsigned int *raw)
{
//   printf("second %li\n", k);
	 switch (k) {

	 case 91:
		  return 1;

	 default:
		  return 0;
	 }
}

static int check_third_byte(int k, MxKey * key, unsigned int *raw)
{
//   printf("third %li\n", k);
	 switch (k) {

	 case 49:
		  *key = MxKeyHome;
		  return 1;

	 case 50:
		  *key = MxKeyInsert;
		  return 1;

	 case 51:
		  *key = MxKeyDelete;
		  return 1;

	 case 52:
		  *key = MxKeyEnd;
		  return 1;

	 case 53:
		  *key = MxKeyPageup;
		  return 1;

	 case 54:
		  *key = MxKeyPagedown;
		  return 1;

	 case 65:
		  *key = MxKeyUp;
		  return 0;

	 case 66:
		  *key = MxKeyDown;
		  return 0;

	 case 67:
		  *key = MxKeyRight;
		  return 0;

	 case 68:
		  *key = MxKeyLeft;
		  return 0;

	 default:
		  return 0;
	 }
}

static int check_fourth_byte(int k, MxKey * key, unsigned int *raw)
{
//   printf("fourth %li\n", k);
	 switch (k) {

	 case 126:
		  *raw = 0;
		  return 0;

	 default:
		  return 0;
	 }
}

void mx_svgalib_key(unsigned int *raw, MxKey * key, unsigned int *code)
{
	 int k = lastkey;

	 *key = 0;
	 *raw = k;
	 *code = 0;

	 if (check_first_byte(k, key, raw)) {
		  *raw = k;

		  k = vga_getkey();
		  if (check_second_byte(k, key, raw)) {
				*raw <<= 8;
				*raw += k;

				k = vga_getkey();
				if (check_third_byte(k, key, raw)) {
					 *raw <<= 8;
					 *raw += k;

					 k = vga_getkey();
					 if (check_fourth_byte(k, key, raw)) {
						  *raw <<= 8;
						  *raw += k;
					 }
				}
		  }
	 }

	 /* Get the code value */
	 if (*key == 0)
		  *code = (*raw) & 0xff;

//    printf("k = %i raw %li key %i code %li\n", k, *raw, *key, *code);
}
