#include "depui/config.h"
#include "depui/pointer/pointer.h"
#include "depui/desktop/desktop.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

MxObject *MxPointer(void)
{
	 return Mx.pointer;
}
