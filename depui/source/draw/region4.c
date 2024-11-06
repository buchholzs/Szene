#include "depui/config.h"
#include "depui/macros.h"
#include "depui/draw/region.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxRegionIntersectRect(MxRegion * region, const MxRect * const rect)
{
	 unsigned int i;
	 MxRegion copy;

	 MX_TRACE("");

	 MxRegionCopyConstruct(&copy, region);
	 MxRegionDestruct(region);
	 MxRegionConstruct(region);

	 for (i = 0; i < MxRegionNumber(copy); i++) {
		  MxRect intersect;

		  MX_INTERSECT_RECTS(*MxRegionRect(copy, i), *rect, intersect);
		  MxRegionAddRect(region, &intersect);
	 }
	 MxRegionDestruct(&copy);
}
