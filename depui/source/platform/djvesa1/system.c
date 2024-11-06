#include "depui/platform/platform.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Defining these function make DJGPP executables smaller */
void __crt0_load_environment_file(char *a)
{
	 (void) a;
}

char **__crt0_glob_function(char *a)
{
	 (void) a;
	 return 0;
}

void mx_djvesa1_yield(void)
{
#ifdef __DOS__
	 __dpmi_yield();
#endif
}
