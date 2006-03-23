#include "depui/config.h"
#include "depui/macros.h"
#include "depui/types.h"
#include "depui/desktop/driver.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/graphics/draw.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"
#include "depui/platform/platform.h"
#include "depui/event/queue.h"
#include <stdlib.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

unsigned int MxMove(MxObject * const object, int x, int y)
{
	 unsigned int ret;

	 assert(object);

	 /* We cannot do any blitting if we have not been inited */
	 if (!object->init) {
		  MxGeomPosition(object, x, y);
		  return MxTrue;
	 }

	 /* Handle any default size */
	 if (x == MxDefault)
		  x = MxX(object);

	 if (y == MxDefault)
		  y = MxY(object);

	 /* Will we change anything */
	 if ((x == object->position.x1) && (y == object->position.y1))
		  return MxFalse;

	 /* The object must also update it's childrens regions */
	 if ((!object->Fastdraw) && (MxFirstChild(object))) {

		  MxRegion region;

		  MxRegionVisibleConstruct(&region, object, MxFalse);
		  MxEnqueueRefreshRegion(&region);

		  ret = MxGeomRequest(object, x, y, 0, 0, (MxGeomFlags) (MxGeomX | MxGeomY));

		  MxRegionDestruct(&region);
		  MxRegionVisibleConstruct(&region, object, MxFalse);
		  MxEnqueueRefreshRegion(&region);

		  MxRegionDestruct(&region);
		  MxRegionInvalidate(object);

		  /* The object is fastdraw so it's region already contains it's
		     childrens regions */
	 } else {

		  MxVisible(object);
		  MxEnqueueRefreshRegion(&object->region);

		  ret = MxGeomRequest(object, x, y, 0, 0, (MxGeomFlags) (MxGeomX | MxGeomY));

		  MxVisible(object);
		  MxEnqueueRefreshRegion(&object->region);
	 }
	 return ret;
}
