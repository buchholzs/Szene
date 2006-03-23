#include "depui/config.h"
#include "depui/graphics/frame.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxFrameGroove(int *x1, int *y1, int *x2, int *y2, int effect)
{
	 MxFrameRaised(x1, y1, x2, y2, -effect);
	 MxFrameRaised(x1, y1, x2, y2, effect);
}
