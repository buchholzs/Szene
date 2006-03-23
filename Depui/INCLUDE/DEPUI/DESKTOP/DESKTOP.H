#ifndef MX_DESKTOP_DESKTOP_H
#define MX_DESKTOP_DESKTOP_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/event/event.h"
#include "depui/event/queue.h"
#include "depui/object/object.h"
#include "depui/object/window.h"
#include "depui/desktop/driver.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxDesktop {
		  union {
				MxObject object;
		  } base;

		  unsigned int ok;

	 } MxDesktop;

	 typedef struct MxDesktopArgs {
		  MxObjectArgs object;	  /* Must be first */

		  MxWindowArgs window;

		  int desktop_w;
		  int desktop_h;
		  int desktop_c;

		  MxDriverSystem *system;
		  MxDriverOutput *output;
		  MxDriverInput *input;
	 } MxDesktopArgs;

	 void *MxDesktopHandler(MxObject * object, const MxEvent * const event);
	 void MxDesktopConstruct(MxDesktop * desktop, int x, int y, int w, int h, MxDesktopArgs * args);

	 typedef struct MxGlobal {
		  struct MxDesktop *desktop;

		  MxEventQueue queue;
		  MxObject *pointer;
		  MxObject *focus;
		  MxObject *droptarget;

		  MxObject *active;
		  void *activelock;

		  MxObject *exiting;

		  int running;
		  int idle_count;

		  int mouse_x, mouse_y, mouse_b;
		  int old_mouse_x, old_mouse_y, old_mouse_b;

		  unsigned int hold_pointer:1;
		  unsigned int wantmove:1;
		  unsigned int needflush:1;

		  unsigned int OpaqueMove:1;
	 } MxGlobal;

	 /* Global variables */
	 extern MxGlobal Mx;
	 extern MxRegion mx_region;
	 extern struct MxObject *mx_desk;

	 unsigned int MxDesktopRun(MxDesktop * desktop);

	 void MxPopupClean(void);

	 MxObject *MxObjectXY(int x, int y);

	 void mx_handle_pointer(void);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxDesktopArgs > MxpDesktopArgs;

class MxpDesktop:public MxDesktop { public:MxpDesktop(int x, int y, int width, int height, MxDesktopArgs * userargs) {
		  MxDesktopConstruct(this, x, y, width, height, userargs);
};

	 ~MxpDesktop() {
		  if (&this->base.object == mx_desk)
				MxDestroy(&this->base.object);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpDesktop();
	 MxpDesktop(const MxpDesktop & other);
};

#endif

#endif
