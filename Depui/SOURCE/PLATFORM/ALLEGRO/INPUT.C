#include "depui/platform/platform.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Allegro does a strange macro thing with main so we have to compensate <sigh> */
#undef main
#include <allegro.h>

int mx_allegro_kbd_init(void)
{
	 install_keyboard();
	 install_mouse();

	 show_mouse(screen);
	 return 1;
}

void mx_allegro_kbd_exit(void)
{
	 remove_mouse();
	 remove_keyboard();
}

void mx_allegro_mouse(int *x, int *y, int *b)
{
	 *x = mouse_x;
	 *y = mouse_y;
	 *b = mouse_b;
}

int mx_allegro_key_pressed(void)
{
	 return keypressed();
}

typedef struct KeyTable {
	 int k;
	 MxKey key;
} KeyTable;

static KeyTable keytable[] = {
	 {21504, MxKeyUp},
	 {21760, MxKeyDown},
	 {20992, MxKeyLeft},
	 {21248, MxKeyRight},

	 {19456, MxKeyInsert},
	 {19712, MxKeyDelete},
	 {19968, MxKeyHome},
	 {20224, MxKeyEnd},
	 {20480, MxKeyPageup},
	 {20736, MxKeyPagedown},

	 {0, MxKeyNone}
};

void mx_allegro_key(unsigned int *raw, MxKey * key, unsigned int *code)
{
	 KeyTable *ptr = keytable;
	 int k = readkey();

	 *raw = k;

	 /* Get the code value */
	 *code = k & 0xff;

	 /* Look through the table looking for matches */
	 while ((ptr->k) && (k != ptr->k)) {
		  ++ptr;
	 }

	 /* Return the best match */
	 *key = ptr->key;

	 /* handle some special cases */
	 if (*raw == 17165)
		  *code = 13;
	 if (*raw == 19232)
		  *code = 32;
	 if (*raw == 16136)
		  *code = 8;
	 if (*raw == 16393)
		  *code = 9;
}
