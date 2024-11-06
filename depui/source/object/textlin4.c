#include "depui/config.h"
#include "depui/object/text.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxTextlineDelete(MxTextline * textline, const int len, const int offset)
{
	 /* Produce the correct string */
	 char *newtext = (char *) MxMalloc(strlen(textline->base.stext.caption) - len + 1);

	 MX_TRACE("");

	 strncpy(newtext, textline->base.stext.caption, offset);
	 newtext[offset] = '\0';
	 strcat(newtext, &textline->base.stext.caption[offset + len]);

	 /* Set the new string */
	 MxStatictextSet(&textline->base.stext, newtext, MxTrue);
}
