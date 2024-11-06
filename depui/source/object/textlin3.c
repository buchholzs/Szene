#include "depui/config.h"
#include "depui/object/text.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxTextlineInsert(MxTextline * textline, const char *text, const int offset)
{
	 const int newlen = strlen(text);
	 const int caplen = strlen(textline->base.stext.caption);

	 char *newtext = (char *) MxMalloc(caplen + newlen + 1);

	 MX_TRACE("");

	 /* Create the new text */
	 strncpy(newtext, textline->base.stext.caption, offset);
	 newtext[offset] = '\0';
	 strcat(newtext, text);
	 strcat(newtext, &textline->base.stext.caption[offset]);

	 /* Set the new string */
	 MxStatictextSet(&textline->base.stext, newtext, MxTrue);
}
