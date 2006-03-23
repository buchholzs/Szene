/* This code has been taken from Allegro with minor modifications */
#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/support/findfirs.h"

#ifdef __DJGPP__
#include <dpmi.h>
#define REGS     __dpmi_regs
#define CALLINT  __dpmi_int
#endif

/* drive_exists:
 *  Checks whether the specified drive is valid.
 */
int mx_drive_exists(int x)
{
	 /* DJGPP handling of drive recognition taken from Allegro */
#ifdef __DJGPP__

	 /* DOS implementation */
	 unsigned int old;
	 int ret = MxFalse;
	 REGS r;

	 /* get actual drive */
	 r.h.ah = 0x19;
	 __dpmi_int(0x21, &r);
	 old = r.h.al;

	 /* see if drive x is assigned as a valid drive */
	 r.h.ah = 0x0E;
	 r.h.dl = x;
	 CALLINT(0x21, &r);

	 r.h.ah = 0x19;
	 CALLINT(0x21, &r);

	 if (r.h.al == x) {

		  /* ok, now check if it is a logical drive or not... */
		  r.x.ax = 0x440E;
		  r.h.bl = x + 1;
		  CALLINT(0x21, &r);

		  if ((r.x.flags & 1) ||  /* call failed */
				(r.h.al == 0) ||	  /* has no logical drives */
				(r.h.al == (x + 1)))	/* not a logical drive */
				ret = MxTrue;
	 }

	 /* now we set the old drive */
	 r.h.ah = 0x0E;
	 r.h.dl = old;
	 CALLINT(0x21, &r);

	 return ret;

#else
	 (void) x;

	 /* unknown platform */
	 return MxTrue;
#endif
}
