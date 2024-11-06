#include "depui/platform/platform.h"
#include "depui/desktop/driver.h"
#include "depui/support/mouse.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/desktop/desktop.h"
#include "depui/geometry/geometry.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>

#include <stdio.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

extern Display *mx_x_display;
extern Window mx_x_window;
extern int mx_x_width;
extern int mx_x_height;

static int lastkey = 0;

static MxRegion region;

int mx_x_kbd_init(void)
{
	 MxRegionConstruct(&region);
	 return 1;
}

void mx_x_kbd_exit(void)
{
	 MxRegionDestruct(&region);
}

static MxRegion region;

void mx_x_mouse(int *x, int *y, int *b)
{
	 XEvent event;
	 const unsigned long mask =

		  ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask | StructureNotifyMask;

	 if (XCheckWindowEvent(mx_x_display, mx_x_window, mask, &event)) {
		  switch (event.type) {

		  case Expose:{
					 MxRect rect;

					 /* Add up the regions to be updated */
					 rect.x1 = event.xexpose.x;
					 rect.y1 = event.xexpose.y;
					 rect.x2 = event.xexpose.x + event.xexpose.width - 1;
					 rect.y2 = event.xexpose.y + event.xexpose.height - 1;
					 MxRegionAddRect(&region, &rect);

					 /* Update all regions at once */
					 if (event.xexpose.count == 0) {
						  MxRefreshRegion(&region);

						  /* Clear the region and make it ready for more */
						  MxRegionDestruct(&region);
						  MxRegionConstruct(&region);
					 }
					 break;
				}

		  case ConfigureNotify:{
					 mx_x_width = event.xconfigure.width;
					 mx_x_height = event.xconfigure.height;

					 /* Actually change the size, redraw is done automatically by
					    X server */
					 MxGeomRequest(MxDesk, 0, 0, mx_x_width, mx_x_height, MxGeomW | MxGeomH);
					 break;
				}

		  case ButtonPress:
				*x = event.xbutton.x;
				*y = event.xbutton.y;
				*b = 0x01;
				break;

		  case ButtonRelease:
				*x = event.xbutton.x;
				*y = event.xbutton.y;
				*b = 0x00;
				break;

		  case MotionNotify:
				*x = event.xbutton.x;
				*y = event.xbutton.y;
				break;

		  case KeyPress:{
					 int charcount;
					 char buffer[20];
					 const int bufsize = 20;
					 XComposeStatus compose;
					 KeySym keysym;

					 charcount = XLookupString(&event.xkey, buffer, bufsize, &keysym, &compose);
					 lastkey = buffer[0];

					 if (charcount == 2)
						  lastkey = (buffer[1] << 8) + buffer[0];

					 if (charcount == 0)
						  lastkey = event.xkey.keycode << 8;

//            printf("lastkey = %i\n", lastkey);
					 break;
				}

		  default:
				break;
		  }
	 }
}

int mx_x_key_pressed(void)
{
	 return lastkey != 0;
}

typedef struct KeyTable {
	 int k;
	 MxKey key;
} KeyTable;

static KeyTable keytable[] = {
	 {25088, MxKeyUp},
	 {26624, MxKeyDown},
	 {25600, MxKeyLeft},
	 {26112, MxKeyRight},

	 {27136, MxKeyInsert},
	 {127, MxKeyDelete},
	 {24832, MxKeyHome},
	 {26368, MxKeyEnd},
	 {25344, MxKeyPageup},
	 {26880, MxKeyPagedown},

	 {0, MxKeyNone}
};

void mx_x_key(unsigned int *raw, MxKey * key, unsigned int *code)
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

//    printf("k = %i raw %li key %i code %li\n", k, *raw, *key, *code);
}
