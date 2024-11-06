#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/object.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/event/queue.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* inserts the given object under the given parent */
static unsigned int _insert_window(MxObject * const object, MxObject * const parent)
{
	 MX_TRACE("");

	 if ((parent) &&				  /* There really is a parent */
		  (!MxParent(object))) {  /* MxObject does not already have a parent */

		  mx_add(object, parent);
		  mx_adjust_geometry(object, &parent->position, MxTrue);

		  return MxTrue;
	 }
	 return MxFalse;
}

/* inserts a object under the given parent */
unsigned int MxInsert(MxObject * object, MxObject * parent, unsigned int redraw)
{
	 unsigned int retval;

	 /* Actually do the insertion */
	 retval = _insert_window(object, parent);

	 assert(object);
	 assert(parent);

	 MX_TRACE("");

	 if ((retval) && (parent->init)) {

		  /* Tell the object to get it's geometry right */
		  mx_object_init(object);

		  /* It may be visible, so update it */
		  MxRegionInvalidate(object);
		  if (redraw)
				MxEnqueueRefresh(object, MxFalse);
	 }
	 return retval;
}
