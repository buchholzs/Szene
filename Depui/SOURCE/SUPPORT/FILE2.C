/* This code has been taken from Allegro with minor modifications */
#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/support/findfirs.h"

/* ff_put_backslash:
 *  If the last character of the filename is not a /, this routine will
 *  concatenate a / on to it.
 */
void mx_put_backslash(char *filename, int size)
{
	 int len = strlen(filename);

	 if ((len > 0) && (len < (size - 1)) && (filename[len - 1] != '/')) {
		  filename[len] = '/';
		  filename[len + 1] = 0;
	 }
}
