#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/object.h"
#include "depui/draw/region.h"
#include "depui/desktop/desktop.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#if defined(MX_DEBUG_MEM) || defined (MX_DEBUG_EVENT)
#include <stdlib.h>
#endif

void *MxObjectHandler(MxObject * object, const MxEvent * const event)
{
	 (void) object;
	 (void) event;
	 return 0;
}

void MxObjectConstruct(MxObject * object, MxObject * parent, int x, int y, int width, int height, MxObjectArgs * userargs)
{
	 (void) userargs;

	 assert(object);

	 MX_TRACE("");

	 memset(object, 0, sizeof(MxObject));

	 object->handler = MxObjectHandler;
	 object->position.x1 = x;
	 object->position.y1 = y;
	 object->position.x2 = object->position.x1 + width;
	 object->position.y2 = object->position.y1 + height;
	 object->constructed = MxTrue;

	 MxRegionConstruct(&object->region);

#ifdef MX_WINDOW_NAMES
	 object->name = "MxObject";
#endif

	 if (parent)
		  MxInsert(object, parent, MxFalse);
}

MxObject *MxObjectNew(MxObject * parent, int x, int y, int w, int h, MxObjectArgs * args)
{
	 return (MxObject *) MxNewObject(sizeof(MxObject), (MxVoidFunc) MxObjectConstruct, parent, x, y, w, h, args);
}

static void _destroy_object(MxObject * object, const int mustremove)
{
	 MxObject *ptr;
	 const int wasallocated = object->allocated;

	 assert(object);

	 MX_TRACE("");

	 /* Only destruct if the object was actually constructed */
	 if (object->constructed)
		  object->constructed = MxFalse;
	 else
		  return;

	 /* Make sure the object has been removed first */
	 if (mustremove)
		  MxRemove(object);

	 /* If it wasn't removed, we may still have to purge any messages queued
	    to this object */
	 else
		  mx_forget_object(object);

	 /* Tell the objects and it's children that it's bieng destroyed */
	 MxEventSendSimple(object, MxEventDestroy);

	 /* Destroy the children also */
	 ptr = MxFirstChild(object);
	 while (ptr) {

		  MxObject *next = MxNext(ptr);

		  _destroy_object(ptr, 0);

		  ptr = next;
	 }
	 /* Free the children array */
	 mx_free_child(object);

	 /* Free the region */
	 if (object->regionvalid)
		  MxRegionDestruct(&object->region);

	 /* Really destroy the memory */
#if defined(MX_DEBUG_MEM) || defined (MX_DEBUG_EVENT)
	 memset(object, 0, sizeof(MxObject));
#endif

	 /* Destroy the object except if necessary but not if it is from the
	    Desktop */
	 if (wasallocated)
		  MxFree(object);
}

void MxDestroy(MxObject * object)
{
	 MX_TRACE("");

	 _destroy_object(object, MxTrue);

	 if (object == mx_desk) {
		  MxEventQueueDestruct();
		  MxRegionDestruct(&mx_region);

		  Mx.desktop = 0;
		  mx_desk = 0;

		  mx_input->Exit();
		  mx_output->Exit();
	 }
}
