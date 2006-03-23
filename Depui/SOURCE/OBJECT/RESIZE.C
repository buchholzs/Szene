#include "depui/config.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/event/queue.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

unsigned int MxResize(MxObject * object, int w, int h)
{
	 unsigned int ret;

	 assert(object);

	 if (!object->init) {
		  MxGeomSize(object, w, h);
		  return MxTrue;
	 }

	 /* Handle any default size */
	 if (w == MxDefault)
		  w = MxW(object);

	 if (h == MxDefault)
		  h = MxH(object);

	 /* Will we change anything */
	 if ((w == MxW(object)) && (h == MxH(object)))
		  return MxFalse;

	 MxVisible(object);
	 MxEnqueueRefreshRegion(&object->region);

	 ret = MxGeomRequest(object, 0, 0, w, h, (MxGeomFlags) (MxGeomW | MxGeomH));

	 MxVisible(object);
	 MxEnqueueRefresh(object, MxFalse);

	 return ret;
}
