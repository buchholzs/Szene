#include "depui/config.h"
#include "depui/object/text.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Break a line at the return characters */
int mx_line_end_return(const char *text)
{
	 /* If we get a hard return, skip over it and end the line */
	 if (*text == 0x0d) {

		  /* Is it a DOS line ending */
		  if (text[1] == 0x0a)
				return 2;

		  /* It is a unix lne end */
		  return 1;
	 }

	 /* Some keyboards return this as a line ending */
	 if (*text == 0x0a)
		  return 1;

	 return -1;
}
