#include "depui/config.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#define MX_MAX(x,y)     (((x) > (y)) ? (x) : (y))

void MxEncloseChildren(MxObject * object, int x, int y)
{
	 MxObject *ptr;
	 int mx = 0, my = 0;

	 assert(object);

	 ptr = MxFirstChild(object);

	 while (ptr) {

		  int cx = MxX2(ptr);
		  int cy = MxY2(ptr);

		  mx = MX_MAX(cx, mx);
		  my = MX_MAX(cy, my);

		  ptr = MxNext(ptr);
	 }

	 MxGeomSize(object, mx + x, my + y);
}
