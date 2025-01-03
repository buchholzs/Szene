#include "depui/platform/platform.h"
#include "depui/support/mouse.h"
#include <grx20.h>
#include <grxkeys.h>

#include <stdio.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_grx_kbd_init(void)
{
	 return 1;
}

void mx_grx_kbd_exit(void)
{
}

void mx_grx_mouse(int *x, int *y, int *b, int *key)
{
	 GrMouseEvent evt;

#ifdef GRX_NATIVE_POINTER
	 int flags = GR_M_EVENT;
	 if (!GrMouseCursorIsDisplayed()) {
		 flags |= GR_M_NOPAINT;
	 }
	 GrMouseGetEventT(flags, &evt, 0L);
#else
	 GrMouseGetEventT(GR_M_NOPAINT | GR_M_EVENT, &evt, 0L);
#endif	 
	 *x = evt.x;
	 *y = evt.y;
	 *b = evt.buttons;
	 if (evt.flags & GR_M_KEYPRESS) {
		 *key = evt.key;
	 }
	 else {
		 *key = 0;
	 }
#ifndef GRX_NATIVE_POINTER
	 Mx_MouseMove(*x, *y, mx_grx_screen_pixel, mx_grx_screen_get_pixel);
#endif	 
}

int mx_grx_key_pressed(void)
{
	 return GrKeyPressed();
}

typedef struct KeyTable {
	 int k;
	 MxKey key;
} KeyTable;

static KeyTable keytable[] = {
	 {328, MxKeyUp},
	 {336, MxKeyDown},
	 {331, MxKeyLeft},
	 {333, MxKeyRight},

	 {338, MxKeyInsert},
	 {339, MxKeyDelete},
	 {327, MxKeyHome},
	 {335, MxKeyEnd},
	 {329, MxKeyPageup},
	 {337, MxKeyPagedown},

	 {0, MxKeyNone}
};

void mx_grx_key(unsigned int *raw, MxKey * key, unsigned int *code)
{
	 KeyTable *ptr = keytable;
	 int k = *raw;

	 /* Get the code value */
	 *code = k & 0xff;

	 /* Look through the table looking for matches */
	 while ((ptr->k) && (k != ptr->k)) {
		  ++ptr;
	 }

	 /* Return the best match */
	 *key = ptr->key;

	 /* If key matched, send no ascii */
	 if (*key)
		  *code = 0;

//    fprintf(stderr, "key %i code %i\n", k, *code);
}
