#include "depui/config.h"
#include "depui/macros.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int mx_list_geometry(MxObject * object, int default_width, int theborder)
{
	 int basic_width = 0;
	 const int border = abs(theborder);
	 int h = border;

	 MxObject *child = MxLastChild(object);

	 MX_TRACE("");

	 /* Find out if the children will accept the width */
	 while (child) {

		  int w = default_width;

		  MxGeomQuery(child, 0, 0, &w, 0, MxGeomW);
		  basic_width = MX_MAX(basic_width, w);

		  child = MxPrev(child);
	 }

	 /* Position the children on top of each other with the correct width */
	 child = MxLastChild(object);
	 while (child) {

		  MxGeomRequest(child, border, h, basic_width, 0, (MxGeomFlags) (MxGeomX | MxGeomY | MxGeomW));
		  h += MxH(child) + 1;
		  child = MxPrev(child);
	 }

	 /* Fit ourselves to the children */
	 MxGeomSize(object, basic_width + 2 * border, h + border - 1);
	 return basic_width;
}
