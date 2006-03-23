#ifndef MX_DIALOG_DRAGDROP_H
#define MX_DIALOG_DRAGDROP_H

#include "depui/config.h"
#include "depui/object/object.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef void (*MxDragdropDataDestruct) (void *data);

	 typedef enum MxDragdropType {
		  MxDragdropIgnore,

		  MxDragdropVoid,
		  MxDragdropString,

		  MxDragdropUser,

		  MxDragdropLast = 0x7fff /* Force the enum to at least 16 bits */
	 } MxDragdropType;

	 typedef struct MxDragdrop {
		  union {
				MxObject object;
		  } base;

		  void *data;
		  MxDragdropType type;

		  MxDragdropDataDestruct destruct;

		  const MxObject *source; /* The target that we avoid, i.e. the object
										     that started the drag in the first place */
		  const char *caption;
		  unsigned int ownscaption:1;

	 } MxDragdrop;

	 void *MxDragdropHandler(MxObject * object, const MxEvent * const event);

	 void MxDragdropStart(const MxObject * const badtarget, void *data, MxDragdropType type, MxDragdropDataDestruct destruct,
								 const char *caption, const unsigned int ownscaption);

	 unsigned int MxDragdropReserve(MxDragdropType * type);

#ifdef __cplusplus
}
#endif
#endif
