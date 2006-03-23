#include "depui/config.h"
#include "depui/graphics/clip.h"
#include "depui/desktop/driver.h"
#include "depui/draw/region.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxClipRegion(const MxRegion * const region)
{
	 MxRegionDestruct(&mx_region);
	 MxRegionCopyConstruct(&mx_region, region);

	 /* Tell the platform that we are clipped too */
	 mx_output->Region(&mx_region);
}
