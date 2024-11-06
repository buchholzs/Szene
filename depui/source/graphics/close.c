#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/graphics/decorate.h"

MxDecoration_7_7 Mx_DecorationClose = {
	 7,
	 7,
	 {1, 1, 0, 0, 0, 1, 1,
	  1, 1, 1, 0, 1, 1, 1,
	  0, 1, 1, 1, 1, 1, 0,
	  0, 0, 1, 1, 1, 0, 0,
	  0, 1, 1, 1, 1, 1, 0,
	  1, 1, 1, 0, 1, 1, 1,
	  1, 1, 0, 0, 0, 1, 1}
};
