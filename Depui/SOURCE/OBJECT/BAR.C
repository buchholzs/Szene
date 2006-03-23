#include "depui/config.h"
#include "depui/args/args.h"
#include "depui/desktop/driver.h"
#include "depui/object/bar.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void draw_bar(MxBar * bar, int x1, int y1, int x2, int y2)
{
	 const int w = x2 - x1;
	 const int h = y2 - y1;

	 const MxColor first = bar->raised ? MxColorLight : MxColorDark;
	 const MxColor second = bar->raised ? MxColorDark : MxColorLight;

	 /* Is the bar horizontal */
	 if (w > h) {
		  MxScreenHLine(0, x1, y1, x2 - 1, first);
		  MxScreenHLine(0, x1 + 1, y1 + 1, x2, second);

		  /* or is it vertical */
	 } else {
		  MxScreenVLine(0, x1, y1, y2 - 1, first);
		  MxScreenVLine(0, x1 + 1, y1 + 1, y2, second);
	 }
}

void *MxBarHandler(MxObject * object, const MxEvent * const event)
{
	 MxBar *bar = (MxBar *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 /* Handle normal events */
	 switch (event->type) {

	 case MxEventExpose:
		  draw_bar(bar, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

	 default:
		  break;
	 }
	 return 0;
}

void MxBarConstruct(MxBar * bar, MxObject * parent, int x, int y, int w, int h, MxBarArgs * userargs)
{
	 MxBarArgs args;

	 assert(bar);
	 MxUserArgsInit(args, userargs);

	 /* Make the object narrow, or thin */
	 if (w > h)
		  h = 2;
	 else
		  w = 2;

	 /* Force them to use some sensible width */
	 memset(bar, 0, sizeof(MxBar));
	 MxObjectConstruct(&bar->base.object, parent, x, y, w, h, &args.object);
	 bar->base.object.handler = MxBarHandler;

	 /* The object is transparent to miminize the number of rectanges */
	 bar->base.object.Transparent = MxTrue;

	 /* What kind of bar does the user want */
	 bar->raised = args.raised;

#ifdef MX_WINDOW_NAMES
	 bar->base.object.name = "MxBar";
#endif
}

MxBar *MxBarNew(MxObject * parent, int x, int y, int w, int h, MxBarArgs * args)
{
	 return (MxBar *) MxNewObject(sizeof(MxBar), (MxVoidFunc) MxBarConstruct, parent, x, y, w, h, &args->object);
}
