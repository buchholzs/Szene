#include "depui/config.h"
#include "depui/geometry/geometry.h"
#include "depui/event/event.h"
#include "depui/object/object.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Ask the object parent for a certain geometry */
unsigned int MxGeomQuery(MxObject * const dest, int *x, int *y, int *w, int *h, MxGeomFlags flags)
{
	 MxEvent event;
	 MxGeomData geom;
	 MxObject *ret = 0;

	 assert(dest);
	 assert(flags);

	 /* If we have no object, then do nothing */
	 if ((!dest) || (!flags))
		  return MxFalse;

	 /* Start witha empty geometry */
	 memset(&geom, 0, sizeof(geom));

	 /* Construct the geometry data and the event */
	 event.type = MxEventGeomRequest;
	 event.geom.dest = dest;
	 event.geom.data = &geom;

	 if (x)
		  geom.x = *x;
	 if (y)
		  geom.y = *y;
	 if (w)
		  geom.w = *w;
	 if (h)
		  geom.h = *h;

	 geom.flags = flags;

#ifdef MX_DEBUG_EVENT
	 fprintf(mx_stream, "GeomQuery: %s to (%i, %i, %i, %i)\n", dest->name, x ? *x : 0, y ? *y : 0, w ? *w : 0, h ? *h : 0);
	 fflush(mx_stream);
#endif

	 /* Ask if they have any problems with this size */
	 if (dest->init)
		  ret = (MxObject *) MxEventSend(dest, &event);

	 /* Make any changes as suggested */
	 if (x)
		  *x = geom.x;
	 if (y)
		  *y = geom.y;
	 if (w)
		  *w = geom.w;
	 if (h)
		  *h = geom.h;

	 /* Return if they agree to the geometry */
	 if (!ret)
		  return MxTrue;
	 return MxFalse;
}

/* Ask the object parent for a certain geometry */
unsigned int MxGeomRequest(MxObject * const dest, int x, int y, int w, int h, MxGeomFlags flags)
{
	 unsigned int changed = MxFalse;

	 assert(dest);
	 assert(flags);

	 /* If we have no object, then do nothing */
	 if ((!dest) || (!flags))
		  return MxFalse;

	 /* Ask the object what they think about this geometry */
	 if (MxGeomQuery(dest, &x, &y, &w, &h, flags)) {

		  if (flags & MxGeomX)
				changed |= MxGeomPosition(dest, x, MxY(dest));

		  if (flags & MxGeomY)
				changed |= MxGeomPosition(dest, MxX(dest), y);

		  if (flags & MxGeomW)
				changed |= MxGeomSize(dest, w, MxH(dest));

		  if (flags & MxGeomH)
				changed |= MxGeomSize(dest, MxW(dest), h);

		  /* Tell ourselves how we have changed */
		  if ((changed) && (dest->init)) {

				MxEvent event;
				MxGeomData geom;

				event.type = MxEventGeomChanged;
				event.geom.dest = dest;
				event.geom.data = &geom;

				geom.x = x;
				geom.y = y;
				geom.w = w;
				geom.h = h;
				geom.flags = flags;

				MxEventSend(dest, &event);
		  }
	 }
#ifdef MX_DEBUG_EVENT
	 fprintf(mx_stream, "GeomResult: %s to (%i, %i, %i, %i)\n", dest->name, x, y, w, h);
	 fflush(mx_stream);
#endif

	 return changed;
}
