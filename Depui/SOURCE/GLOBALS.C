#include "depui/config.h"
#include "depui/desktop/desktop.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

MxGlobal Mx;

MxObject *mx_desk;
MxRegion mx_region;

MxDriverSystem *mx_system = 0;
MxDriverOutput *mx_output = 0;
MxDriverInput *mx_input = 0;
