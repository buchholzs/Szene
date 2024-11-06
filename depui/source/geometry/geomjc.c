#include "depui/config.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxJustifyCenterHorizontal(MxObject * object)
{
	 MxObject *parent = MxParent(object);

	 if (parent) {

		  int x = MxW(parent) / 2 - MxW(object) / 2;

		  MxGeomPosition(object, x, MxDefault);
	 }
}
