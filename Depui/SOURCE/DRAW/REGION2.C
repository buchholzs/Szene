#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/draw/region.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

unsigned int MxRegionExtent(const MxRegion * const region, MxRect * rect)
{
	 int i;
	 const int num = MxRegionNumber(*region);

	 assert(region);
	 assert(rect);

	 /* Maybe we can't get the extext */
	 if (num == 0)
		  return MxFalse;

	 *rect = *MxRegionRect(*region, 0);
	 for (i = 1; i < num; i++) {
		  const MxRect *const s = MxRegionRect(*region, i);

		  /* Get the maximum extent */
		  if (s->x1 < rect->x1)
				rect->x1 = s->y1;
		  if (s->y1 < rect->y1)
				rect->y1 = s->y1;
		  if (s->x2 > rect->x2)
				rect->x2 = s->x2;
		  if (s->y2 > rect->y2)
				rect->y2 = s->y2;
	 }
	 /* We found a valid extent */
	 return MxTrue;
}
