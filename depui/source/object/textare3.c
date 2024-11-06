#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/event/queue.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxTextareaDelete(MxTextarea * textarea, const int len, const int offset)
{
	 /* We can just copy the data over without reallocating, but we must force 
	    the destination because MxTextbox has a const caption */
	 strcpy((char *) &textarea->caption[offset], &textarea->caption[offset + len]);

	 /* Split up the text into lines, try to use our current width */
	 textarea_parse(textarea, MxW(&textarea->base.object), MxTrue);
	 MxEnqueueRefresh(&textarea->base.object, MxFalse);
}
