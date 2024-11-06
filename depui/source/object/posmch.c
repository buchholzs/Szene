#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* returns a object value related to its geometry */
int MxMaxChildH(const MxObject * const object)
{
	 int h;
	 int max = 0;

	 MxObject *ptr = MxFirstChild(object);

	 while (ptr) {

		  h = MxH(ptr);

		  if (h > max)
				max = h;
		  ptr = MxNext(ptr);
	 }
	 return max;
}
