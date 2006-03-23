#include "depui/platform/platform.h"
#include "depui/support/mouse.h"
#include "depui/desktop/desktop.h"
#include <conio.h>
#include <dpmi.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))
#define MID(x,y,z)   MAX((x), MIN((y), (z)))

static int mouse_mx = 0;		  /* internal position, in mickeys */
static int mouse_my = 0;
static int mouse_sx = 2;		  /* mickey -> pixel scaling factor */
static int mouse_sy = 2;

#define MICKEY_TO_COORD_X(n)        ((n) / mouse_sx)
#define MICKEY_TO_COORD_Y(n)        ((n) / mouse_sy)

#define COORD_TO_MICKEY_X(n)        ((n) * mouse_sx)
#define COORD_TO_MICKEY_Y(n)        ((n) * mouse_sy)

static int mouse_valid = 0;

int mx_djvesa2_kbd_init(void)
{
	 __dpmi_regs regs;

	 /* Reset the mouse driver */
	 regs.x.ax = 0x0000;
	 __dpmi_int(0x33, &regs);
	 if (regs.x.ax) {

		  /* Center the mouse */
		  const int w = MxDesk->position.x2 - MxDesk->position.x1;
		  const int h = MxDesk->position.y2 - MxDesk->position.y1;

		  mouse_mx = w / 2;
		  mouse_my = h / 2;

		  /* Mouse is valid */
		  mouse_valid = 1;
	 }
	 return mouse_valid;
}

void mx_djvesa2_kbd_exit(void)
{
}

void mx_djvesa2_mouse(int *mx, int *my, int *mb)
{
	 if (mouse_valid) {
		  int x, y;
		  __dpmi_regs regs;

		  /* Get mouse button data */
		  regs.x.ax = 0x0003;
		  __dpmi_int(0x33, &regs);
		  *mb = regs.x.bx;

		  /* Get mouse mickey data */
		  regs.x.ax = 0x000b;
		  __dpmi_int(0x33, &regs);

		  x = (signed short) regs.x.cx;
		  y = (signed short) regs.x.dx;

		  /* Has the mouse position changed */
		  if ((x != 0) || (y != 0)) {

				/* Get the mouse coordinates */
				*mx = MICKEY_TO_COORD_X(mouse_mx + x);
				*my = MICKEY_TO_COORD_Y(mouse_my + y);

				/* Limit the mouse coordinates to on screen */
				*mx = MID(0, *mx, MxDesk->position.x2);
				*my = MID(0, *my, MxDesk->position.y2);
				mouse_mx = COORD_TO_MICKEY_X(*mx);
				mouse_my = COORD_TO_MICKEY_Y(*my);

				/* Move the mouse on the screen */
				Mx_MouseMove(*mx, *my, mx_djvesa2_screen_pixel, mx_djvesa2_screen_get_pixel);
		  }
	 }
}

int mx_djvesa2_key_pressed(void)
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

void mx_djvesa2_key(unsigned int *raw, MxKey * key, unsigned int *code)
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
