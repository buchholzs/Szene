#ifndef MX_OBJECT_BAR_H
#define MX_OBJECT_BAR_H

#include "depui/config.h"
#include "depui/object/object.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxBar {
		  union {
				MxObject object;
		  } base;

		  unsigned int raised:1;

	 } MxBar;

	 typedef struct MxBarArgs {

		  MxObjectArgs object;	  /* Must be first */

		  unsigned int raised:1;

	 } MxBarArgs;

	 void *MxBarHandler(MxObject * object, const MxEvent * const event);

	 void MxBarConstruct(MxBar * Bar, MxObject * parent, int x, int y, int w, int h, MxBarArgs * args);

	 MxBar *MxBarNew(MxObject * parent, int x, int y, int w, int h, MxBarArgs * args);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxBarArgs > MxpBarArgs;

class MxpBar:public MxBar {
	 public:MxpBar(MxObject * parent, int x, int y, int width, int height, MxBarArgs * userargs) {
		  MxBarConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpBar();
	 MxpBar(const MxpBar & other);
};

#endif

#endif
