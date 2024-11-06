#ifndef MX_OBJECT_RADIOGRP_H
#define MX_OBJECT_RADIOGRP_H

#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/object/statict.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef MxStatictext MxRadioGroup;
	 typedef MxStatictextArgs MxRadioGroupArgs;

	 void *MxRadioGroupHandler(MxObject * object, const MxEvent * const event);

	 void MxRadioGroupConstruct(MxRadioGroup * rgroup, MxObject * parent, int x, int y, int w, int h, MxRadioGroupArgs * args);

	 MxRadioGroup *MxRadioGroupNew(MxObject * parent, int x, int y, int w, int h, MxRadioGroupArgs * args);

#ifdef __cplusplus
}
#endif
#endif
