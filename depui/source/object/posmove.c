#include "depui/config.h"
#include "depui/geometry/geometry.h"
#include "depui/object/object.h"
#include "depui/object/defsize.h"
#include "depui/draw/draw.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void _move_object(MxObject * object, int x, int y)
{
	 MxObject *ptr = MxFirstChild(object);

	 while (ptr) {

		  _move_object(ptr, x, y);
		  ptr = MxNext(ptr);
	 }

	 object->position.x1 += x;
	 object->position.x2 += x;
	 object->position.y1 += y;
	 object->position.y2 += y;
}

/* sets the object's y position */
unsigned int MxGeomPosition(MxObject * object, int x, int y)
{
	 const int oldx = object->position.x1;
	 const int oldy = object->position.y1;
	 const int oldh = object->position.y2 - object->position.y1;
	 const int oldw = object->position.x2 - object->position.x1;

	 const MxObject *const parent = MxParent(object);

	 /* Handle any default size */
	 if (x == MxDefault)
		  x = object->position.x1;

	 if (y == MxDefault)
		  y = object->position.y1;

	 if (parent) {

		  object->position.x1 = parent->position.x1 + x;
		  object->position.x2 = object->position.x1 + oldw;
		  object->position.y1 = parent->position.y1 + y;
		  object->position.y2 = object->position.y1 + oldh;

	 } else {

		  object->position.x1 = x;
		  object->position.x2 = object->position.x1 + oldw;
		  object->position.y1 = y;
		  object->position.y2 = object->position.y1 + oldh;
	 }

	 /* Move the children over also if we changed anything */
	 if ((oldx != object->position.x1) || (oldy != object->position.y1)) {

		  MxObject *ptr = MxFirstChild(object);

		  while (ptr) {

				_move_object(ptr, object->position.x1 - oldx, object->position.y1 - oldy);
				ptr = MxNext(ptr);
		  }

		  MxRegionInvalidate(object);
		  return MxTrue;
	 }
	 return MxFalse;
}
