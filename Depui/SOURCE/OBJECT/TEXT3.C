#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/desktop/driver.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* How many characters do we have in a line */
unsigned int MxLineEndCharwrap(const char *start, int *offset, int *skip, int width)
{
	 /* Inform that we can fit any width */
	 if (!start)
		  return MxTrue;

	 /* Find the line ends */
	 else {
		  int count = 0;
		  const char *text = &start[*offset];

		  while ((text) && (*text)) {

				/* Are we at the end of a line */
				*skip = mx_line_end_charwrap(text, &count, width);
				if (*skip >= 0)
					 return MxFalse;

				/* Check the next character */
				++text;
				++(*offset);
		  }
	 }
	 return MxTrue;
}
