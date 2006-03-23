#ifndef MX_EVENT_FOCUS_H
#define MX_EVENT_FOCUS_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/event/event.h"
//#include "depui/desktop/desktop.h"

#ifdef __cplusplus
extern "C" {
#endif
	 void MxFocusSet(struct MxObject *object);
	 struct MxObject *MxFocus(void);

	 void MxActiveSet(struct MxObject *object, void *lock);
	 struct MxObject *MxActive(void);

#ifdef __cplusplus
}
#endif
#endif
