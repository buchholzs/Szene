#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Allegro does some magic of main function via a macro, but since
   we can't include <allegro.h> in our <depui.h> we have to workaround */
#if defined(MX_DRIVER_ALLEGRO) || defined(MX_DRIVER_GENERIC)

#undef main

int main(int argc, char *argv[])
{
	 return MxMain(argc, argv);
}

void *_mangled_main_address = 0;

#endif
