#include "depui/config.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"
#include "depui/draw/draw.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

unsigned int MxGeomSize(MxObject * object, int w, int h)
{
	 int oldx2 = object->position.x2, oldy2 = object->position.y2;

	 /* Handle any default size */
	 if (w == MxDefault)
		  w = MxW(object);

	 if (h == MxDefault)
		  h = MxH(object);

	 object->position.x2 = object->position.x1 + w;
	 object->position.y2 = object->position.y1 + h;

	 /* Tell the user if something has changed */
	 if ((oldx2 != object->position.x2) || (oldy2 != object->position.y2)) {

		  MxRegionInvalidate(object);
		  return MxTrue;
	 }

	 return MxFalse;
}
