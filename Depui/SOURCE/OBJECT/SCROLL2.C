#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Ask our parent to scroll us if possible */
void MxScrollRequest(const MxObject * const object, const MxGeomData * const geom)
{
	 MxEvent scroll;

	 scroll.type = MxEventScrollRect;

	 /* What changes are really being asked of us */
	 scroll.rect.rect = object->position;

	 if (geom->flags & MxGeomX) {
		  const int change = geom->x - MxX(object);

		  scroll.rect.rect.x1 += change;
		  scroll.rect.rect.x2 += change;
	 }

	 if (geom->flags & MxGeomY) {
		  const int change = geom->y - MxY(object);

		  scroll.rect.rect.y1 += change;
		  scroll.rect.rect.y2 += change;
	 }

	 if (geom->flags & MxGeomW)
		  scroll.rect.rect.x2 = scroll.rect.rect.x1 + geom->w;

	 if (geom->flags & MxGeomH)
		  scroll.rect.rect.y2 = scroll.rect.rect.y1 + geom->h;

	 /* Now ask the parent to scroll us */
	 MxEventSend(MxParent(object), &scroll);
}
