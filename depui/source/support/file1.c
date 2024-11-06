/* This code has been taken from Allegro with minor modifications */
#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/debug/alloc.h"
#include "depui/support/findfirs.h"
#include <string.h>

/* ff_get_filename:
 *  When passed a completely specified file path, this returns a pointer
 *  to the filename portion.
 */
char *mx_get_filename(char *path)
{
	 char *p;

	 /* Don't interfere with the drive */
#ifdef __MSDOS__
	 if (path[1] == ':') {
		  path += 2;
		  if (*path == '/')
				++path;
	 }
#endif
	 p = path + strlen(path);

	 while ((p > path) && (*(p - 1) != '/'))
		  p--;

	 return p;
}

char *mx_get_extension(char *path)
{
	 char *p = path + strlen(path);

	 while ((p > path) && (*(p - 1) != '.'))
		  p--;

	 if (p == path)
		  return path + strlen(path);

	 return p;
}
