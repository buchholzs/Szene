#ifndef MX_DRAW_DRAW_H
#define MX_DRAW_DRAW_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 void MxRefreshRect(const MxRect * const rect);
	 void MxRefresh(struct MxObject *const object);
	 void MxRefreshRegion(const struct MxRegion *const region);

	 unsigned int MxVisible(struct MxObject *const object);

	 void MxRegionInvalidate(struct MxObject *const object);

#ifdef __cplusplus
}
#endif
#endif
