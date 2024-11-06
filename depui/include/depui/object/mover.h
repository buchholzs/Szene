#ifndef MX_OBJECT_MOVER_H
#define MX_OBJECT_MOVER_H

#include "depui/config.h"
#include "depui/object/object.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxMover {
		  union {
				MxObject object;
		  } base;

		  MxObject *source;
		  int offset_x;
		  int offset_y;

		  unsigned int resize:1;
		  unsigned int opaque:1;

	 } MxMover;

	 typedef struct MxMoverArgs {

		  MxObjectArgs object;	  /* Must be first */

		  unsigned int opaque;

	 } MxMoverArgs;

	 void *MxMoverHandler(MxObject * object, const MxEvent * const event);

	 void MxMoverStart(MxObject * const source, const unsigned int resize, int x, int y);

#ifdef __cplusplus
}
#endif
#endif
