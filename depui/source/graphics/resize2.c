#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/graphics/decorate.h"

/*
MxDecoration_6_6 Mx_DecorationResize = {
	 6,
	 6,
	 {0, 0, 0, 0, 9, 9,
	  0, 0, 0, 9, 0, 7,
	  0, 0, 9, 0, 0, 7,
	  0, 9, 0, 0, 0, 7,
	  9, 0, 0, 0, 0, 7,
	  7, 7, 7, 7, 7, 7}
};
*/

MxDecoration_6_6 Mx_DecorationResize = {
	 6,
	 6,
	 {0, 0, 0, 0, 0, 9,
	  0, 0, 0, 0, 9, 7,
	  0, 0, 0, 9, 7, 0,
	  0, 0, 9, 7, 0, 9,
	  0, 9, 7, 0, 9, 7,
	  9, 7, 0, 9, 7, 0}
};
