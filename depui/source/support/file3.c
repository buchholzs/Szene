#include "depui/config.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/support/findfirs.h"
#include <stdlib.h>
#include <string.h>

/* Fixup the pathname by removing "/DIR/../" and "/./" path portions */
void mx_fixpath(char *path)
{
	 char *next;
	 char *ptr;

	 assert(path);

#ifdef __MSDOS__
	 /* Ignore leading drive specs   */
	 if ((*path) && (path[1] == ':')) {
		  path += 2;
		  if (*path == '/')
				++path;
	 }
#endif

	 /* Find slashes */
	 ptr = path;
	 next = strchr(ptr, '/');
	 if (next)
		  ++next;

	 /* Look for updirs */
	 while ((ptr) && (next)) {

		  /* Is the following dir an updir, and the previous one not  */
		  if ((next[0] == '.') && (next[1] == '.') && (ptr[0] != '.') && (ptr[1] != '.'))
				strcpy(ptr, next + 3);

		  /* Remove /./ combinations */
		  else if ((ptr[0] == '.') && (ptr[1] == '/') && (ptr + 2 == next))
				strcpy(ptr, ptr + 2);

		  /* Look at the next slashes */
		  else
				ptr = next;

		  next = strchr(ptr, '/');
		  if (next)
				++next;
	 }
}
