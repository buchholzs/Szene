#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/draw/draw.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxChildSort(MxObject * const object, MxChildSortFunc sort)
{
	 /* Don't sort if there are no children */
	 if (MxNumChild(object) == 0)
		  return;

	 MxRegionInvalidate(object);
	 mx_child_sort(object, sort);
}
