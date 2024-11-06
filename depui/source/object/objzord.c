#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/draw/draw.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

unsigned int MxZOrder(MxObject * const object, int neworder)
{
	 MxObject *const oldobject = object;

	 /* Try to change the Zorder of the object */
	 unsigned int changed = mx_zorder(object, &neworder);

	 assert(object);

	 MX_TRACE("");

	 /* Inform siblings that Z order has changed */
	 if ((changed) && (object->init)) {

		  MxObject *ptr;

		  MxEvent event;

		  event.type = MxEventZOrderInform;
		  event.zorder.target = object;
		  event.zorder.newz = neworder;

		  for (ptr = MxLast(object); ptr; ptr = MxPrev(ptr))
				if (ptr != object)
					 MxEventSend(ptr, &event);

		  /* We need to update the screen areas again */
		  MxRegionInvalidate(oldobject);
		  MxRegionInvalidate(object);
	 }
	 return changed;
}
