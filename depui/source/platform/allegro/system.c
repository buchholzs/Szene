#include "depui/platform/platform.h"

#ifdef __DOS__
#include <dpmi.h>
#endif

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Allegro does a strange macro thing with main so we have to compensate <sigh> */
#undef main
#include <allegro.h>

void mx_allegro_yield(void)
{
#ifdef __DOS__
	 __dpmi_yield();
#endif
}
