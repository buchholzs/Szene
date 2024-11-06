#include "depui/config.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxJustifyCenterVertical(MxObject * object)
{
	 MxObject *parent = MxParent(object);

	 if (parent) {

		  int y = MxH(parent) / 2 - MxH(object) / 2;

		  MxGeomPosition(object, MxDefault, y);
	 }
}
