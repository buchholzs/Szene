#include "depui/config.h"
#include "depui/object/defsize.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxDefaultSize(int *w, int *h, int defw, int defh)
{
	 if ((*w == MxDefault) && (defw != MxDefault))
		  *w = defw;

	 if ((*h == MxDefault) && (defh != MxDefault))
		  *h = defh;
}
