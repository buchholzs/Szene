#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/desktop/driver.h"
#include <ctype.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* How many characters do we have in a line */
unsigned int MxLineEndWordwrap(const char *start, int *offset, int *skip, int width)
{
	 /* Inform that we can fit any width */
	 if (!start)
		  return MxTrue;

	 /* Find the line ends */
	 else {

		  int count = 0;
		  const char *text = &start[*offset];
		  const char *linestart = text;

		  while ((text) && (*text)) {

				/* Are we at the end of a line */
				*skip = mx_line_end_charwrap(text, &count, width);

				/* we are truly skipping a hard return or something like that */
				if (*skip > 0)
					 return MxFalse;

				/* We probably ran into the char width problem */
				else if (*skip == 0) {

					 /* Walk backwards to the last space */
					 int backoffset = *offset;

					 while ((*text != ' ') && (text != linestart)) {
						  --text;
						  --backoffset;
					 }

					 /* Did the space just happen to be in the right place, so
					    skip it so it will wrap the line just fine */
					 if (backoffset == *offset) {
						  ++(*skip);
						  return MxFalse;

						  /* We hit a space before the line start, so this is the
						     line break */
					 } else if ((text != linestart) && (*text == ' '))
						  *offset = backoffset + 1;

					 /* Otherwise we hit the start, the word is too long to word
					    wrap, so then force it to wrap at this char */
					 return MxFalse;
				}

				/* Check the next character */
				++text;
				++(*offset);
		  }
	 }
	 return MxTrue;
}
