#ifndef MX_DRAW_REGION_H
#define MX_DRAW_REGION_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxRegionData {
		  unsigned int num;
		  MxRect r[1];
	 } MxRegionData;

	 typedef struct MxRegion {
		  MxRegionData *reg;

#ifdef MX_DEBUG_REGION_CONSTRUCT
		  unsigned int constructed:1;
#endif
	 } MxRegion;

#define MxRegionNumber(region)  (((region).reg) ? ((region).reg->num) : 0)
#define MxRegionRect(region, i) (&(region).reg->r[i])

#define Mx_RegionMem(i)         (sizeof(MxRegionData) + (i - 1) * sizeof(MxRect))

/* If we are not debugging the regions, we use a macro */
#ifdef MX_DEBUG_REGION_CONSTRUCT
	 unsigned int MxRegionEmpty(const MxRegion * const region);
#else
#define MxRegionEmpty(regionp)  ((regionp)->reg ? MxFalse : MxTrue)
#endif

	 void MxRegionAddRect(MxRegion * region, const MxRect * const rect);
	 void MxRegionRemoveRect(MxRegion * region, const int regionindex);

	 void MxRegionClipRect(MxRegion * region, const MxRect * const rect);
	 void MxRegionClipRegion(MxRegion * region, const MxRegion * const reg);
	 void MxRegionIntersectRect(MxRegion * region, const MxRect * const rect);

	 unsigned int MxRegionVisibleConstruct(MxRegion * region, struct MxObject *const object, const unsigned int children);
	 unsigned int MxRegionExtent(const MxRegion * const region, MxRect * rect);

	 void MxRegionConstruct(MxRegion * region);
	 void MxRegionDestruct(MxRegion * region);
	 void MxRegionOptimize(MxRegion * region);
	 void MxRegionSort(MxRegion * region);

	 void MxRegionCopyConstruct(MxRegion * const region, const MxRegion * const other);

	 unsigned int MxRegionContainsPoint(const MxRegion * const region, const int x, const int y);

#ifdef __cplusplus
}
#endif
#endif
