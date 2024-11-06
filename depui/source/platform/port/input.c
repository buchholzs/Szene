#include "depui/platform/platform.h"
#include "depui/desktop/driver.h"
#include "depui/support/mouse.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

extern MxRect mx_mouseclip;

int mx_port_kbd_init(void)
{
	 /* ^^^ Initialize any keyboard handlers here ^^^ */
	 return 1;
}

void mx_port_kbd_exit(void)
{
	 /* ^^^ Exit any keyboard handlers here ^^^ */
}

void mx_port_mouse(int *x, int *y, int *b)
{
	 /* ^^^ Get mouse position and button info here ^^^ */
	 *x = 0;
	 *y = 0;
	 *b = 0;

	 Mx_MouseMove(*x, *y, mx_port_screen_pixel, mx_port_screen_get_pixel);
}

int mx_port_key_pressed(void)
{
	 /* ^^^ Has any key been pressed ^^^ */
	 return 0;
}

typedef struct KeyTable {
	 int k;
	 MxKey key;
} KeyTable;

static KeyTable keytable[] = {

	 {0, MxKeyNone}
};

void mx_port_key(unsigned int *raw, MxKey * key, unsigned int *code)
{
	 KeyTable *ptr = keytable;

	 /* ^^^ What was the last key pressed ^^^ */
	 int k = 0;

	 /* Get the code value */
	 *raw = k;
	 *code = k & 0xff;

	 /* Look through the table looking for matches */
	 while ((ptr->k) && (k != ptr->k)) {
		  ++ptr;
	 }

	 /* Return the best match */
	 *key = ptr->key;
}
