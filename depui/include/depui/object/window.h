#ifndef MX_OBJECT_WINDOW_H
#define MX_OBJECT_WINDOW_H

#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/object/menu.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxWindow {
		  union {
				MxObject object;
		  } base;

		  MxObject *client;
		  MxObject *blocked;
		  MxMenu *menu;

		  int border;

		  const char *caption;
		  unsigned int ownscaption:1;

		  unsigned int modal:1;
		  unsigned int unmovable:1;
		  unsigned int unresizeable:1;
		  unsigned int uncloseable:1;
		  unsigned int centered:1;

		  unsigned int moving:1;
		  unsigned int resizeing:1;

	 } MxWindow;

	 typedef struct MxWindowArgs {

		  MxObjectArgs object;	  /* Must be first */

		  int border;

		  const char *caption;
		  unsigned int ownscaption;

		  MxMenu *menu;

		  MxObject *client;
		  unsigned int noclient;

		  unsigned int modal;
		  MxObject *blocked;

		  unsigned int unmovable;
		  unsigned int unresizeable;
		  unsigned int uncloseable;
		  unsigned int centered;

		  unsigned int barheight;

	 } MxWindowArgs;

	 void *MxWindowClientPanelHandler(MxObject * object, const MxEvent * const event);
	 void *MxWindowHandler(MxObject * object, const MxEvent * const event);

	 void MxWindowConstruct(MxWindow * window, MxObject * parent, int x, int y, int w, int h, MxWindowArgs * args);

	 MxWindow *MxWindowNew(MxObject * parent, int x, int y, int w, int h, MxWindowArgs * args);

	 /* Make a window modal or not */
	 void MxWindowModal(MxWindow * window, unsigned int makemodal, MxObject * blocked);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxWindowArgs > MxpWindowArgs;

class MxpWindow:public MxWindow {
	 public:MxpWindow(MxObject * parent, int x, int y, int width, int height, MxWindowArgs * userargs) {
		  MxWindowConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpWindow();
	 MxpWindow(const MxpWindow & other);
};

#endif

#endif
