#include "depui/config.h"
#include "depui/object/window.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxWindowSet(MxWindow * window, const char *caption, unsigned int owns)
{
	 assert(window);

	 /* Clean up any old caption */
	 if ((window->ownscaption) && (window->caption))
		  MxFree((char *) window->caption);

	 /* Set the new caption */
	 window->caption = caption;
	 window->ownscaption = owns;
}
