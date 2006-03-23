#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/graphics/decorate.h"

MxDecoration_9_9 Mx_DecorationRadioon = {
	 9,
	 9,
	 {0, 0, 0, 0, 1, 0, 0, 0, 0,
	  0, 0, 0, 1, 1, 1, 0, 0, 0,
	  0, 0, 1, 1, 6, 1, 1, 0, 0,
	  0, 1, 1, 6, 6, 6, 1, 1, 0,
	  1, 1, 6, 6, 6, 6, 6, 1, 1,
	  0, 1, 1, 6, 6, 6, 1, 1, 0,
	  0, 0, 1, 1, 6, 1, 1, 0, 0,
	  0, 0, 0, 1, 1, 1, 0, 0, 0,
	  0, 0, 0, 0, 1, 0, 0, 0, 0}
};

MxDecoration_9_9 Mx_DecorationRadiooff = {
	 9,
	 9,
	 {0, 0, 0, 0, 9, 0, 0, 0, 0,
	  0, 0, 0, 9, 0, 7, 0, 0, 0,
	  0, 0, 9, 0, 0, 0, 7, 0, 0,
	  0, 9, 0, 0, 0, 0, 0, 7, 0,
	  9, 0, 0, 0, 0, 0, 0, 0, 7,
	  0, 9, 0, 0, 0, 0, 0, 7, 0,
	  0, 0, 9, 0, 0, 0, 7, 0, 0,
	  0, 0, 0, 9, 0, 7, 0, 0, 0,
	  0, 0, 0, 0, 7, 0, 0, 0, 0}
};
