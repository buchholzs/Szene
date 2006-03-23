#include "depui/config.h"
#include "depui/object/statict.h"
#include "depui/event/event.h"
#include "depui/event/queue.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxStatictextSet(MxStatictext * stext, const char *caption, unsigned int owns)
{
	 assert(stext);

	 /* Clean up any old caption */
	 if ((stext->ownscaption) && (stext->caption))
		  MxFree((char *) stext->caption);

	 /* Set the new caption */
	 stext->caption = caption;
	 stext->ownscaption = owns;

	 /* We need to update our justification and display stuff now */
	 stext->justified = MxFalse;
}
