#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/draw/draw.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxHide(MxObject * object, const unsigned int hide)
{
	 assert(object);

	 object->hidden = hide;
	 MxRegionInvalidate(object);
}
