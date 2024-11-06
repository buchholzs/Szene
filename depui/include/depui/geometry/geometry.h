#ifndef MX_GEOMETRY_GEOMETRY_H
#define MX_GEOMETRY_GEOMETRY_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 unsigned int MxGeomPosition(struct MxObject *object, int x, int y);
	 unsigned int MxGeomSize(struct MxObject *object, int x, int y);

	 unsigned int MxMove(struct MxObject *const object, int x, int y);
	 unsigned int MxResize(struct MxObject *const object, int w, int h);

	 int MxMaxChildW(const struct MxObject *const object);
	 int MxMaxChildH(const struct MxObject *const object);

	 int MxMaxChildX2(const struct MxObject *const object);
	 int MxMaxChildY2(const struct MxObject *const object);

	 typedef enum MxGeomFlags {
		  MxGeomNone = 0,
		  MxGeomX = (1 << 0),
		  MxGeomY = (1 << 1),
		  MxGeomW = (1 << 2),
		  MxGeomH = (1 << 3)
	 } MxGeomFlags;

	 typedef struct MxGeomData {
		  int x;
		  int y;
		  int w;
		  int h;
		  enum MxGeomFlags flags;
	 } MxGeomData;

	 unsigned int MxGeomQuery(struct MxObject *const dest, int *x, int *y, int *w, int *h, MxGeomFlags flags);
	 unsigned int MxGeomRequest(struct MxObject *const dest, int x, int y, int w, int h, MxGeomFlags flags);

	 void MxScrollRequest(const struct MxObject *const object, const MxGeomData * const geom);

	 void MxEncloseChildren(struct MxObject *object, int x, int y);

	 void MxJustifyCenterVertical(struct MxObject *object);
	 void MxJustifyCenterHorizontal(struct MxObject *object);

	 int mx_child_width(struct MxObject *blist, int width);
	 int mx_list_geometry(struct MxObject *object, int default_width, int theborder);

#ifdef __cplusplus
}
#endif
#endif
