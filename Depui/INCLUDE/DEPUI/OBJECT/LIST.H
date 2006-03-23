#ifndef MX_OBJECT_LIST_H
#define MX_OBJECT_LIST_H

#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/object/scroll.h"
#include "depui/object/listdef.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxListarea {
		  union {
				MxObject object;
		  } base;

		  MxListDef *def;
		  unsigned int ownsdef;

		  MxListDef *clicked;
		  MxListDef *pointed;

		  int border;

		  unsigned int maxw, maxh;

		  MxTabstopFunc tabstop;

		  unsigned int multiple:1;

	 } MxListarea;

	 typedef struct MxListareaArgs {

		  MxObjectArgs object;

		  MxListDef *def;
		  unsigned int ownsdef:1;

		  int border;

		  MxTabstopFunc tabstop;

		  unsigned int multiple:1;

	 } MxListareaArgs;

	 void *MxListareaHandler(MxObject * object, const MxEvent * const event);
	 void MxListareaConstruct(MxListarea * list, MxObject * parent, int x, int y, int w, int h, MxListareaArgs * args);
	 MxListarea *MxListareaNew(MxObject * parent, int x, int y, int w, int h, MxListareaArgs * args);

	 void MxListDefSet(MxListarea * list, MxListDef * def, unsigned int owns);
	 void MxListareaAppend(MxListarea * list, const MxListDef * const def);
	 void MxListareaRemove(MxListarea * list, const MxListDef * const def);

	 void MxListareaSelect(MxListarea * list, MxListDef * hit, MxObject * object);
	 void mx_listarea_draw(MxListarea * list, int x1, int y1, int x2, int y2, const MxRegion * const region, MxColor fore,
								  MxColor back);
	 void mx_listarea_press(MxListarea * list, int y, unsigned int focus);

	 typedef struct MxList {
		  union {
				MxObject object;
				MxScroll scroll;
		  } base;

		  MxListarea listarea;

	 } MxList;

	 typedef struct MxListArgs {

		  MxObjectArgs object;

		  MxScrollArgs scroll;
		  MxListareaArgs listarea;

	 } MxListArgs;

	 void *MxListHandler(MxObject * object, const MxEvent * const event);
	 void MxListConstruct(MxList * list, MxObject * parent, int x, int y, int w, int h, MxListArgs * args);
	 MxList *MxListNew(MxObject * parent, int x, int y, int w, int h, MxListArgs * args);

/* Get the first element in a list definition */
#define MxListDefGet(list)    ((list)->listarea.def)

/* Make the list accept multiple selected objects ot not */
#define MxListMultiple(list, mult)  do { (list)->listarea.multiple = (mult); } while (0)

	 void mx_listarea_inform(MxListarea * list, MxEventType type, MxListDef * hit);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxListArgs > MxpListArgs;

class MxpList:public MxList {
	 public:MxpList(MxObject * parent, int x, int y, int width, int height, MxListArgs * userargs = 0) {
		  MxListConstruct(this, parent, x, y, width, height, userargs);
	 };

	 void DefSet(MxListDef * def, unsigned int owns) {
		  MxListDefSet(&this->listarea, def, owns);
	 };

	 void Append(const MxListDef * const def) {
		  MxListareaAppend(&this->listarea, def);
	 };

	 void Remove(const MxListDef * const def) {
		  MxListareaRemove(&this->listarea, def);
	 };

	 MxListDef *Def() {
		  return MxListDefGet(this);
	 };

	 void Multiple(unsigned int mult) {
		  MxListMultiple(this, mult);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpList();
	 MxpList(const MxpList & other);
};

#endif

#endif
