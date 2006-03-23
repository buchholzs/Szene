#ifndef MX_OBJECT_ANIMATE_H
#define MX_OBJECT_ANIMATE_H

#include "depui/config.h"
#include "depui/object/object.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxAnimate {
		  union {
				MxObject object;
		  } base;

		  int x, y;
		  int dx, dy;

	 } MxAnimate;

	 typedef struct MxAnimateArgs {

		  MxObjectArgs object;	  /* Must be first */

	 } MxAnimateArgs;

	 void *MxAnimateHandler(MxObject * object, const MxEvent * const event);

	 void MxAnimateConstruct(MxAnimate * access, MxObject * parent, int x, int y, int w, int h, MxAnimateArgs * args);

	 MxAnimate *MxAnimateNew(MxObject * parent, int x, int y, int w, int h, MxAnimateArgs * args);

#ifdef __cplusplus
}
#endif
#endif
