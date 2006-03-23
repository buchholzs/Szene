#ifndef MX_POINTER_POINTER_H
#define MX_POINTER_POINTER_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 struct MxObject *MxPointer(void);

	 /* Stop the pointer object from changing, useful for click-drag */
	 void MxPointerGrab(struct MxObject *const object);
	 void MxPointerRelease(void);

	 void MxPointerWantMove(const struct MxObject *const object, const unsigned int want);

	 void MxPointerBase(const struct MxObject *const object, struct MxObject *const base);

#ifdef __cplusplus
}
#endif
#endif
