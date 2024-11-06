#include "depui/platform/platform.h"
#include <grx20.h>
#include <grxkeys.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_grx_yield(void)
{
#ifdef __DOS__
	 __dpmi_yield();
#endif
}
