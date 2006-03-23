#include "depui/platform/platform.h"
#include "depui/desktop/driver.h"
#include "depui/support/mouse.h"
#include <microwin/nano-X.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include <stdio.h>

extern MxRect mx_mouseclip;

int mx_nanox_kbd_init(void)
{
	 return 1;
}

void mx_nanox_kbd_exit(void)
{
}

static int lastkey = 0;

void mx_nanox_mouse(int *x, int *y, int *b)
{
	 GR_EVENT e;

	 GrGetNextEvent(&e);

	 switch (e.type) {

	 case GR_EVENT_TYPE_MOUSE_MOTION:
	 case GR_EVENT_TYPE_MOUSE_POSITION:
		  *x = e.mouse.x;
		  *y = e.mouse.y;
		  break;

	 case GR_EVENT_TYPE_BUTTON_DOWN:
		  if (e.button.changebuttons & GR_BUTTON_L)
				*b |= 0x01;
		  if (e.button.changebuttons & GR_BUTTON_R)
				*b |= 0x02;
		  if (e.button.changebuttons & GR_BUTTON_M)
				*b |= 0x04;
		  *x = e.mouse.x;
		  *y = e.mouse.y;
		  break;
	 case GR_EVENT_TYPE_BUTTON_UP:
		  if (e.button.changebuttons & GR_BUTTON_L)
				*b = 0x0;
		  if (e.button.changebuttons & GR_BUTTON_R)
				*b = 0x0;
		  if (e.button.changebuttons & GR_BUTTON_M)
				*b = 0x0;
		  *x = e.mouse.x;
		  *y = e.mouse.y;
		  break;
	 case GR_EVENT_TYPE_KEY_DOWN:
		  lastkey = e.keystroke.ch;
		  break;

	 default:
		  break;
	 }
}

int mx_nanox_key_pressed(void)
{
	 return lastkey != 0;
}

typedef struct KeyTable {
	 int k;
	 MxKey key;
} KeyTable;

static KeyTable keytable[] = {
	 {GR_SPECIAL_KEY_ARROW_UP, MxKeyUp},
	 {GR_SPECIAL_KEY_ARROW_DOWN, MxKeyDown},
	 {GR_SPECIAL_KEY_ARROW_LEFT, MxKeyLeft},
	 {GR_SPECIAL_KEY_ARROW_RIGHT, MxKeyRight},
	 {GR_SPECIAL_KEY_INSERT, MxKeyInsert},
	 {GR_SPECIAL_KEY_DELETE, MxKeyDelete},
	 {GR_SPECIAL_KEY_HOME, MxKeyHome},
	 {GR_SPECIAL_KEY_END, MxKeyEnd},
	 {GR_SPECIAL_KEY_PAGEUP, MxKeyPageup},
	 {GR_SPECIAL_KEY_PAGEDOWN, MxKeyPagedown},
	 {0, MxKeyNone}
};

void mx_nanox_key(unsigned int *raw, MxKey * key, unsigned int *code)
{
	 KeyTable *ptr = keytable;
	 int k = lastkey;

	 *raw = k;

	 lastkey = 0;

	 /* Get the code value */
	 *code = k & 0xff;

	 /* Look through the table looking for matches */
	 while ((ptr->k) && (k != ptr->k)) {
		  ++ptr;
	 }

	 /* Return the best match */
	 *key = ptr->key;

//  fprintf(stderr, "k = %i\n", k);
}
