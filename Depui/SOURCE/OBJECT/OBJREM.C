#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/object/object.h"
#include "depui/event/queue.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void _mark_init(MxObject * object, const unsigned int val)
{
	 MxObject *ptr;

	 assert(object);

	 if (object->init == val)
		  return;

	 object->init = val;

	 ptr = MxFirstChild(object);
	 while (ptr) {
		  _mark_init(ptr, val);
		  ptr = MxNext(ptr);
	 }
}

static void _remove_window(MxObject * const object)
{
	 MxObject *parent = MxParent(object);

	 assert(object);

	 MX_TRACE("");

	 if (parent) {

		  MxRect *position = &parent->position;

		  mx_remove(object);
		  mx_adjust_geometry(object, position, MxFalse);
	 }
}

void MxRemove(MxObject * object)
{
	 MxObject *parent = MxParent(object);

	 /* Remember the old position so we can update the screen where the object 
	    was */
	 MxRegion oldregion;
	 const unsigned int wasvisible = MxVisible(object);
	 const unsigned int wasinit = object->init;
	 const unsigned int washidden = object->hidden;

	 if (!parent)
		  return;

	 /* Find out the region that we need to update */
	 if ((wasvisible) && (wasinit) && (!washidden))
		  MxRegionVisibleConstruct(&oldregion, object, MxFalse);

	 /* Remove any regions associated with a removed object.  This must happen 
	    before we unlink it, since we also have to invalidate the regions of
	    parents/siblings. */
	 MxRegionInvalidate(object);

	 _remove_window(object);

	 if (wasinit) {
		  _mark_init(object, MxFalse);

		  /* Make sure the desktop has forgotten us */
		  mx_forget_object(object);
	 }

	 /* Update the screen if the object removed was visible */
	 if ((wasvisible) && (wasinit) && (!washidden)) {
		  MxEnqueueRefreshRegion(&oldregion);
		  MxRegionDestruct(&oldregion);
	 }
}
