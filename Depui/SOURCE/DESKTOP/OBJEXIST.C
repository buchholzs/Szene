#include "depui/config.h"
#include "depui/object/object.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

unsigned int mx_object_exists(const MxObject * base, const MxObject * const object)
{
	 /* Have we found the object */
	 if (base == object) {
		  return MxTrue;

		  /* Look through the children for the object */
	 } else {
		  base = MxFirstChild(base);
		  while (base) {

				/* Found the object, we are done */
				if (mx_object_exists(base, object))
					 return MxTrue;

				/* Check the next object */
				base = MxNext(base);
		  }
	 }
	 /* We could not find the object */
	 return MxFalse;
}
