#include "depui/config.h"
#include "depui/object/text.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* How many characters do we have in a line */
unsigned int MxLineEndReturn(const char *start, int *offset, int *skip, int width)
{
	 /* Inform that we cannot fit any width */
	 if (!start)
		  return MxFalse;

	 /* Find the line ends */
	 else {
		  const char *text = &start[*offset];

		  (void) width;

		  while ((text) && (*text)) {

				/* Are we at the end of a line */
				*skip = mx_line_end_return(text);
				if (*skip >= 0)
					 return MxFalse;

				/* Check the next character */
				++text;
				++(*offset);
		  }
	 }
	 return MxTrue;
}

char *mx_text_copy(const char *start, int len)
{
	 char *ret = (char *) MxMalloc(len + 1);

	 strncpy(ret, start, len);
	 ret[len] = '\0';

	 return ret;
}
