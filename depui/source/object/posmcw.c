#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* returns a object value related to its geometry */
int MxMaxChildW(const MxObject * const object)
{
	 int w;
	 int max = 0;

	 MxObject *ptr = MxFirstChild(object);

	 while (ptr) {

		  w = MxW(ptr);

		  if (w > max)
				max = w;

		  ptr = MxNext(ptr);
	 }
	 return max;
}
