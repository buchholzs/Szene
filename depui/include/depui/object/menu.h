#ifndef MX_OBJECT_MENU_H
#define MX_OBJECT_MENU_H

#include "depui/config.h"
#include "depui/object/list.h"

#ifdef __cplusplus
extern "C" {
#endif
	 struct MxMenu2;

	 typedef MxListDef MxMenuDef;
#define MxMenuDefAppend MxListDefAppend
#define MxMenuDefRemove MxListDefRemove

	 typedef struct MxMenupulldown {
		  union {
				MxObject object;
				MxListarea listarea;
		  } base;

		  struct MxMenu *top;
		  struct MxMenupulldown *child;

	 } MxMenupulldown;

	 typedef struct MxMenupopArgs {

		  MxObjectArgs object;	  /* Must be first */
		  MxListareaArgs listarea;

	 } MxMenupulldownArgs;

	 void *MxMenupulldownHandler(MxObject * object, const MxEvent * const event);
	 MxMenupulldown *MxMenupulldownStart(int x, int y, MxMenupulldownArgs * userargs);

	 typedef struct MxMenu {
		  union {
				MxObject object;
				MxListarea listarea;
		  } base;

		  unsigned int active:1;
		  unsigned int waiting:1;

	 } MxMenu;

	 typedef struct MxMenuArgs {

		  MxObjectArgs object;	  /* Must be first */
		  MxListareaArgs listarea;

	 } MxMenuArgs;

	 void *MxMenuHandler(MxObject * object, const MxEvent * const event);
	 void MxMenuConstruct(MxMenu * access, MxObject * parent, int x, int y, int w, int h, MxMenuArgs * args);
	 MxMenu *MxMenuNew(MxObject * parent, int x, int y, int w, int h, MxMenuArgs * args);

	 void mx_menu_execute(MxMenu * menu, MxMenupulldown * menupd, MxListDef * def);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxMenuArgs > MxpMenuArgs;

class MxpMenu:public MxMenu {
	 public:MxpMenu(MxObject * parent, int x, int y, int width, int height, MxMenuArgs * userargs) {
		  MxMenuConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpMenu();
	 MxpMenu(const MxpMenu & other);
};

#endif

#endif
