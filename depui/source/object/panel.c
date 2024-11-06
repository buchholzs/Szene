#include "depui/config.h"
#include "depui/args/args.h"
#include "depui/desktop/driver.h"
#include "depui/object/panel.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void draw_panel(MxPanel * panel, int x1, int y1, int x2, int y2)
{
	 if ((panel->frame) && (panel->effect))
		  panel->frame(&x1, &y1, &x2, &y2, panel->effect);

	 MxScreenRectFill(0, x1, y1, x2, y2, panel->color);
}

void *MxPanelHandler(MxObject * object, const MxEvent * const event)
{
	 MxPanel *panel = (MxPanel *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 /* Handle normal events */
	 switch (event->type) {

	 case MxEventExpose:
		  draw_panel(panel, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

		  /* Possibly pass geometry changed evets down.  This is useful for
		     panels that are window clients */
	 case MxEventGeomParentChanged:
		  if (panel->PassGeometry)
				MxEventSendSimpleToChildren(object, MxEventGeomParentChanged, 0);
		  break;

	 default:
		  break;
	 }
	 return 0;
}

void MxPanelConstruct(MxPanel * panel, MxObject * parent, int x, int y, int w, int h, MxPanelArgs * userargs)
{
	 MxPanelArgs args;

	 assert(panel);
	 MxUserArgsInit(args, userargs);

	 memset(panel, 0, sizeof(MxPanel));
	 MxObjectConstruct(&panel->base.object, parent, x, y, w, h, &args.object);
	 panel->base.object.handler = MxPanelHandler;

	 /* Possibly set the objects color */
	 if (args.hascolor)
		  panel->color = args.color;
	 else
		  panel->color = MxColorBack;

	 /* What kind of panel does the user want */
	 panel->frame = args.frame;
	 panel->effect = args.effect;

#ifdef MX_WINDOW_NAMES
	 panel->base.object.name = "MxPanel";
#endif
}

MxPanel *MxPanelNew(MxObject * parent, int x, int y, int w, int h, MxPanelArgs * args)
{
	 return (MxPanel *) MxNewObject(sizeof(MxPanel), (MxVoidFunc) MxPanelConstruct, parent, x, y, w, h, &args->object);
}
