#include "depui/config.h"
#include "depui/macros.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_child_width(MxObject * object, int width)
{
	 int maxw = 0;

	 MxObject *child = MxLastChild(object);

	 MX_TRACE("");

	 while (child) {

		  if (MxW(child) != width)
				MxGeomRequest(child, 0, 0, width, 0, MxGeomW);

		  maxw = MX_MAX(maxw, MxW(child));
		  child = MxPrev(child);
	 }
	 return maxw;
}
