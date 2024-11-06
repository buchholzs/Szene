#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/debug/alloc.h"
#include "depui/event/queue.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxTextareaInsert(MxTextarea * textarea, const char *text, const unsigned int offset)
{
	 /* Find out the string lengths */
	 const int inslen = strlen(text);
	 const int caplen = strlen(textarea->caption);
	 const int newlen = caplen + inslen + 1;

	 assert(textarea);
	 assert(textarea->caption);

	 if (!textarea->ownscaption) {

		  /* Make a buffer and fill it with the correct text */
		  char *newtext = (char *) MxMalloc(newlen);

		  strncpy(newtext, textarea->caption, offset);
		  newtext[offset] = '\0';
		  strcat(newtext, text);
		  strcat(newtext, &textarea->caption[offset]);

		  /* We own the caption now and must delete when we are destroyed */
		  textarea->caption = newtext;
		  textarea->ownscaption = MxTrue;

	 } else {
		  /* Make more room for the new text.  We can cast away const here
		     because we know that we own the caption buffer */
		  textarea->caption = (const char *) MxRealloc((char *) textarea->caption, newlen);

		  /* Copy the data over fast, but carefully */
		  memmove((char *) &textarea->caption[offset + inslen], &textarea->caption[offset], caplen - offset + 1);
		  memcpy((char *) &textarea->caption[offset], text, inslen);

	 }
	 /* Split up the text into lines, try to use our current width */
	 textarea_parse(textarea, MxW(&textarea->base.object), MxTrue);
	 MxEnqueueRefresh(&textarea->base.object, MxFalse);
}
