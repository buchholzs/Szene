#ifndef MX_OBJECT_DIRECT_H
#define MX_OBJECT_DIRECT_H

#include "depui/config.h"
#include "depui/object/object.h"

#ifdef __cplusplus
extern "C" {
#endif
/* This object must be on top of the root object, otherwise it won't
   work as expected */ typedef MxObject MxDirectAccess;
	 typedef MxObjectArgs MxDirectAccessArgs;

	 void *MxDirectAccessHandler(MxObject * object, const MxEvent * const event);

	 void MxDirectAccessConstruct(MxDirectAccess * access, MxObject * parent, int x, int y, int w, int h, MxDirectAccessArgs * args);

	 MxDirectAccess *MxDirectAccessNew(MxObject * parent, int x, int y, int w, int h, MxDirectAccessArgs * args);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxDirectAccessArgs > MxpDirectAccessArgs;

class MxpDirectAccess:public MxDirectAccess {
	 public:MxpDirectAccess(MxObject * myparent, int x, int y, int width, int height, MxDirectAccessArgs * userargs) {
		  MxDirectAccessConstruct(this, myparent, x, y, width, height, userargs);
	 };

	 /* Unimplemented functions */
  private:
	 MxpDirectAccess();
	 MxpDirectAccess(const MxpDirectAccess & other);
};

#endif

#endif
