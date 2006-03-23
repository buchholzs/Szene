#ifndef MX_OBJECT_CURSOR_H
#define MX_OBJECT_CURSOR_H

#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/geometry/geometry.h"

#ifdef __cplusplus
extern "C" {
#endif
#define MxCursorBlinkTime (CLOCKS_PER_SEC/4)
#define MxCursorWidth     2
	 typedef struct MxCursor {
		  union {
				MxObject object;
		  } base;

		  unsigned int on:1;
		  unsigned int blinking:1;
		  unsigned int waiting:1;
		  unsigned int firstblink:1;

	 } MxCursor;

	 typedef struct MxCursorArgs {

		  MxObjectArgs args;		  /* Must be first */

	 } MxCursorArgs;

	 void *MxCursorHandler(MxObject * object, const MxEvent * const event);

	 void MxCursorConstruct(MxCursor * cursor, MxObject * parent, int x, int y, int w, int h, MxCursorArgs * args);

	 MxCursor *MxCursorNew(MxObject * parent, int x, int y, int w, int h, MxCursorArgs * args);

	 void MxCursorBlink(MxCursor * cursor, int blink);
	 void MxMoveCursor(MxCursor * cursor, int x, int y);

#ifdef __cplusplus
}
#endif
#endif
