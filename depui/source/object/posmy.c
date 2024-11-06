#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* returns a object value related to its geometry */
int MxMaxChildY2(const MxObject * const object)
{
	 int w;
	 int max = 0;

	 MxObject *ptr = MxFirstChild(object);

	 while (ptr) {

		  w = ptr->position.y2;

		  if (w > max)
				max = w;

		  ptr = MxNext(ptr);
	 }
	 /* Return result relative to parent */
	 return max - object->position.y1;
}
