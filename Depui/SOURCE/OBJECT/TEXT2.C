#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/desktop/driver.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_line_end_charwrap(const char *text, int *count, int width)
{
	 int len;
	 char string[4] = " ";

	 /* Check for hard returns also */
	 len = mx_line_end_return(text);
	 if (len >= 0)
		  return len;

	 /* Track how wide we are right now */
	 string[0] = *text;
	 len = MxFontLength(MxFontDefault, string);

	 /* Are we wide enough yet */
	 *count += len;
	 if (*count >= (width - 1))
		  return 0;

	 /* We are not wide enough yet */
	 return -1;
}
