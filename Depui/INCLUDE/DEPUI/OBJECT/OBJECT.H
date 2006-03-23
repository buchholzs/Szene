#ifndef MX_OBJECT_OBJECT_H
#define MX_OBJECT_OBJECT_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/debug/alloc.h"
#include "depui/event/event.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef void *(*MxHandler) (struct MxObject * object, const MxEvent * const event);

	 typedef struct MxChildData {	/* Only used in RELATION.C */
		  int num;
		  struct MxObject *child[1];
	 } MxChildData;

	 typedef struct MxChildren { /* Only used in RELATION.C */
		  MxChildData *data;
	 } MxChildren;

	 typedef struct MxObject {
		  MxHandler handler;

		  struct MxObject *parent;	/* Only used in RELATION.C */

#ifdef MX_WINDOW_NAMES
		  const char *name;
#endif
		  MxRegion region;
		  MxRect position;

		  MxChildren children;	  /* Only used in RELATION.C */

		  unsigned int index:16;  /* Only used in RELATION.C */

		  unsigned int allocated:1;
		  unsigned int constructed:1;
		  unsigned int init:1;

		  unsigned int hidden:1;  /* Should the object not de drawn */
		  unsigned int Transparent:1;	/* Should background also be drawn */
		  unsigned int Fastdraw:1;	/* The object won't draw over it's children */
		  unsigned int Hasmask:1; /* The object wants to mask it's region */
		  unsigned int KeyProp:1; /* The object wants to propagate keypresses
										     to children */

		  unsigned int regionvalid:1;
		  unsigned int clicked:1;

		  unsigned int blocked:1; /* Blocked from recieving any input i.e. when 
										     a modal window opens for it */

		  unsigned int popup:1;	  /* Object is a special popup object */

	 } MxObject;

	 typedef struct MxObjectArgs {
//#ifdef MX_NO_EMPTY_STRUCTS
		  char mx_ignore_this;
//#endif
	 } MxObjectArgs;

	 void *MxObjectHandler(MxObject * object, const MxEvent * const event);

	 void MxObjectConstruct(MxObject * object, MxObject * parent, int x, int y, int width, int height, MxObjectArgs * userargs);
	 MxObject *MxObjectNew(MxObject * parent, int x, int y, int w, int h, MxObjectArgs * args);

	 /* Object functions for use by/on derived objects */
	 void MxDestroy(MxObject * object);

	 /* Generic derived object creation function */
	 MxObject *MxNewObject(unsigned int size, MxVoidFunc construct, MxObject * parent, int x, int y, int w, int h, MxObjectArgs * args);

	 unsigned int MxInsert(MxObject * object, MxObject * parent, unsigned int redraw);
	 void MxRemove(MxObject * object);

	 unsigned int MxIndex(const MxObject * const object);
	 unsigned int MxZOrder(MxObject * const object, int neworder);
	 unsigned int MxZOrderDraw(MxObject * const object, const int neworder);

	 void MxChildSort(MxObject * const object, MxChildSortFunc sort);

	 void MxHide(MxObject * object, const unsigned int hide);

	 MxObject *MxParent(const MxObject * const object);
	 MxObject *MxLastChild(const MxObject * const object);
	 MxObject *MxFirstChild(const MxObject * const object);
	 MxObject *MxNext(const MxObject * const object);
	 MxObject *MxPrev(const MxObject * const object);

	 MxObject *MxFirst(const MxObject * const object);
	 MxObject *MxLast(const MxObject * const object);

	 unsigned int MxNumChild(const MxObject * const object);

/* Basic information functions */
#define MxX(object) ((MxParent(object))                                         \
                      ? ((object)->position.x1 - MxParent(object)->position.x1) \
                      : (object)->position.x1)

#define MxY(object) ((MxParent(object))                                         \
                      ? ((object)->position.y1 - MxParent(object)->position.y1) \
                      : (object)->position.y1)

#define MxW(object) ((object)->position.x2 - (object)->position.x1)
#define MxH(object) ((object)->position.y2 - (object)->position.y1)

#define MxX2(object) (MxX(object) + MxW(object))
#define MxY2(object) (MxY(object) + MxH(object))

	 void mx_add(MxObject * object, MxObject * parent);
	 void mx_remove(MxObject * const object);
	 void mx_free_child(MxObject * object);
	 unsigned int mx_zorder(MxObject * const object, int *neworder);
	 void mx_child_sort(MxObject * const object, MxChildSortFunc sort);

	 void mx_object_init(struct MxObject *const object);

	 void mx_adjust_geometry(struct MxObject *const object, MxRect * rect, const unsigned int add);

	 /* For object removal and destruction */
	 void mx_forget_object(struct MxObject *object);
	 unsigned int mx_object_exists(const struct MxObject *base, const struct MxObject *const object);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
template < class T > class MxpArgs:public T {

  public:
	 MxpArgs() {
		  Reset();
	 };
	 MxpArgs(const MxpArgs & other) {
		  *this = other;
	 };
	 operator T *() {
		  return this;
	 };
	 void Reset() {
		  T *args = this;
		   memset(args, 0, sizeof(T));
	 };
};

#endif

#endif
