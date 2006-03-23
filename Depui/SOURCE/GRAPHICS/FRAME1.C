#include "depui/config.h"
#include "depui/graphics/frame.h"
#include "depui/desktop/driver.h"
#include <stdlib.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxFrameRaised(int *x1, int *y1, int *x2, int *y2, int effect)
{
	 MxFrameEmpty(*x1, *y1, *x2, *y2, effect, MxColorLight, MxColorDark);
	 *x1 += abs(effect);
	 *y1 += abs(effect);
	 *x2 -= abs(effect);
	 *y2 -= abs(effect);
}
