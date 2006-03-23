#include "depui/config.h"
#include "depui/macros.h"
#include "depui/args/args.h"
#include "depui/desktop/driver.h"
#include "depui/draw/draw.h"
#include "depui/draw/region.h"
#include "depui/event/queue.h"
#include "depui/graphics/draw.h"
#include "depui/object/animate.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static MxEventType MxEventAnimateX = MxEventUserType;
static MxEventType MxEventAnimateY = MxEventUserType;

static void draw_animate(MxAnimate * animate, int x1, int y1, int x2, int y2)
{
	 MxScreenRectFill(0, x1, y1, x2, y2, MxColorDesktop);
	 MxScreenVLine(0, animate->x, y1, y2, MxColorFore);
	 MxScreenHLine(0, x1, animate->y, x2, MxColorFore);
}

void *MxAnimateHandler(MxObject * object, const MxEvent * const event)
{
	 MxAnimate *animate = (MxAnimate *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 /* Handle animation events */
	 if (event->type == MxEventAnimateX) {

		  MxRect rect;
		  MxRegion region;

		  const int xmax = MX_MAX(animate->x, animate->x + animate->dx);
		  const int xmin = MX_MIN(animate->x, animate->x + animate->dx);

		  rect.x1 = xmin, rect.y1 = object->position.y1, rect.x2 = xmax, rect.y2 = object->position.y2;

		  animate->x += animate->dx;
		  if ((animate->x >= object->position.x2)
				|| (animate->x <= object->position.x1))
				animate->dx *= -1;

		  /* Update and restart then do the next frame */
		  MxVisible(object);
		  MxRegionCopyConstruct(&region, &object->region);
		  MxRegionIntersectRect(&region, &rect);
		  MxEnqueueRefreshRegion(&region);
		  MxRegionDestruct(&region);

		  MxEnqueueSimple(object, MxEventAnimateX, 1);

	 } else if (event->type == MxEventAnimateY) {

		  MxRect rect;
		  MxRegion region;

		  const int ymax = MX_MAX(animate->y, animate->y + animate->dy);
		  const int ymin = MX_MIN(animate->y, animate->y + animate->dy);

		  rect.x1 = object->position.x1, rect.y1 = ymin, rect.x2 = object->position.x2, rect.y2 = ymax;

		  animate->y += animate->dy;
		  if ((animate->y >= object->position.y2)
				|| (animate->y <= object->position.y1))
				animate->dy *= -1;

		  /* Update and restart then do the next frame */
		  MxVisible(object);
		  MxRegionCopyConstruct(&region, &object->region);
		  MxRegionIntersectRect(&region, &rect);
		  MxEnqueueRefreshRegion(&region);
		  MxRegionDestruct(&region);

		  MxEnqueueSimple(object, MxEventAnimateY, 1);
	 }

	 /* Handle normal events */
	 switch (event->type) {

	 case MxEventExpose:
		  draw_animate(animate, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

		  /* On initialization, start the animation events */
	 case MxEventPostInit:
		  MxEnqueueSimple(object, MxEventAnimateX, 1);
		  MxEnqueueSimple(object, MxEventAnimateY, 1);

		  animate->x = object->position.x1, animate->y = object->position.y1, animate->dx = 1, animate->dy = 1;
		  break;

	 default:
		  break;
	 }
	 return 0;
}

void MxAnimateConstruct(MxAnimate * animate, MxObject * parent, int x, int y, int w, int h, MxAnimateArgs * userargs)
{
	 MxAnimateArgs args;

	 /* Reserve animation events */
	 MxEventReserve(&MxEventAnimateX);
	 MxEventReserve(&MxEventAnimateY);

	 assert(animate);
	 MxUserArgsInit(args, userargs);

	 memset(animate, 0, sizeof(MxAnimate));
	 MxObjectConstruct(&animate->base.object, parent, x, y, w, h, &args.object);
	 animate->base.object.handler = MxAnimateHandler;

#ifdef MX_WINDOW_NAMES
	 animate->base.object.name = "MxAnimate";
#endif
}

MxAnimate *MxAnimateNew(MxObject * parent, int x, int y, int w, int h, MxAnimateArgs * args)
{
	 return (MxAnimate *) MxNewObject(sizeof(MxAnimate), (MxVoidFunc) MxAnimateConstruct, parent, x, y, w, h, &args->object);
}
