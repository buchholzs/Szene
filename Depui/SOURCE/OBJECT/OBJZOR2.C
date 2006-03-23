#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/event/queue.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

unsigned int MxZOrderDraw(MxObject * const object, const int neworder)
{
	 unsigned int ret;
	 MxRegion oldregion;

	 assert(object);

	 MX_TRACE("");

	 if (!object->init)
		  return MxZOrder(object, neworder);

	 MxRegionVisibleConstruct(&oldregion, object, MxFalse);

	 ret = MxZOrder(object, neworder);
	 if (ret) {

		  MxRegion newregion;

		  MxRegionVisibleConstruct(&newregion, object, MxFalse);

		  MxRegionClipRegion(&newregion, &oldregion);
		  MxEnqueueRefreshRegion(&newregion);

		  MxRegionDestruct(&newregion);
	 }
	 MxRegionDestruct(&oldregion);

	 return ret;
}
