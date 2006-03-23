#include "depui/platform/platform.h"
#include "depui/platform/empty.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_empty_yield(void)
{
}
