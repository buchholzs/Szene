#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/draw/region.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxRegionCopyConstruct(MxRegion * const ret, const MxRegion * const region)
{
	 const int num = MxRegionNumber(*region);

	 assert(ret);
	 assert(region);

	 /* Copy the region data */
	 if (num) {
		  const unsigned int bytes = Mx_RegionMem(num);

		  ret->reg = (MxRegionData *) MxMalloc(bytes);
		  memcpy(ret->reg, region->reg, bytes);

		  /* We are copying a empty region */
	 } else
		  ret->reg = 0;

//  ret->num = region->num;

#ifdef MX_DEBUG_REGION_CONSTRUCT
	 ret->constructed = MxTrue;
#endif
}
