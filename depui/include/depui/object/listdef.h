#ifndef MX_OBJECT_LISTDEF_H
#define MX_OBJECT_LISTDEF_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxListDef {

		  const char *caption;

		  MxCallback callback;
		  void *data;

		  unsigned int y;
		  unsigned int w;
		  unsigned int h;

		  unsigned int selected:1;
		  unsigned int disabled:1;

	 } MxListDef;

	 MxListDef *MxListDefAppend(MxListDef * list, const MxListDef * const def);
	 unsigned int MxListDefRemove(MxListDef * list, const MxListDef * const def);

#ifdef __cplusplus
}
#endif
#endif
