#include "depui/platform/platform.h"
#include "depui\platform/borland/bgi\bgi.h"
#include <dos.h>
#include <conio.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_borland_bgi_kbd_init(void)
{
	 union REGS regs;

	 regs.x.ax = 0x0000;
	 int86(0x33, &regs, &regs);

	 if (regs.x.ax)
		  mx_borland_bgi_mouse_show(1);

	 return 1;
}

void mx_borland_bgi_kbd_exit(void)
{
}

void mx_borland_bgi_mouse(int *x, int *y, int *b)
{
	 union REGS regs;

	 regs.x.ax = 0x0003;
	 int86(0x33, &regs, &regs);

	 *x = regs.x.cx;
	 *y = regs.x.dx;
	 *b = regs.x.bx;
}

int mx_borland_bgi_key_pressed(void)
{
	 return kbhit();
}

typedef struct KeyTable {
	 int k;
	 MxKey key;
} KeyTable;

static KeyTable keytable[] = {
	 {18432, MxKeyUp},
	 {20480, MxKeyDown},
	 {19200, MxKeyLeft},
	 {19712, MxKeyRight},

	 {20992, MxKeyInsert},
	 {21248, MxKeyDelete},
	 {18176, MxKeyHome},
	 {20224, MxKeyEnd},
	 {18688, MxKeyPageup},
	 {20736, MxKeyPagedown},

	 {0, MxKeyNone}
};

void mx_borland_bgi_key(unsigned int *raw, MxKey * key, unsigned int *code)
{
	 KeyTable *ptr = keytable;

	 /* Get the whole key out */
	 int k = getch();

	 if (k == 0)
		  k = getch() << 8;
	 *raw = k;

	 /* Get code value */
	 *code = k & 0xff;

	 /* Look through the table looking for matches */
	 while ((ptr->k) && (ptr->k != k)) {
		  ++ptr;
	 }

	 /* Return the best match */
	 *key = ptr->key;

//  fprintf(stderr, "k %i code %i\n", k, *code);
}
