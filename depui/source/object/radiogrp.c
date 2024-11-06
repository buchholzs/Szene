#include "depui/config.h"
#include "depui/object/radiogrp.h"
#include "depui/graphics/frame.h"
#include "depui/desktop/driver.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void draw_radiogroup(MxRadioGroup * rgroup, int x1, int y1, int x2, int y2)
{
	 int h = MxFontHeight(MxFontDefault);
	 int y = y1 + h / 2;

	 MxFrameGroove(&x1, &y, &x2, &y2, 1);

	 if (rgroup->caption)
		  MxFontScreenRender(0, rgroup->caption, MxFontDefault, x1 + 4, y1, MxColorFore, MxColorBack);
}

void *MxRadioGroupHandler(MxObject * object, const MxEvent * const event)
{
	 MxRadioGroup *rgroup = (MxRadioGroup *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw_radiogroup(rgroup, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

		  /* Treat it like a static text object to handle the internal text */
	 default:
		  return MxStatictextHandler(object, event);
	 }
	 return 0;
}

void MxRadioGroupConstruct(MxRadioGroup * rgroup, MxObject * parent, int x, int y, int w, int h, MxRadioGroupArgs * userargs)
{
	 memset(rgroup, 0, sizeof(MxRadioGroup));

	 MxStatictextConstruct(rgroup, parent, x, y, w, h, userargs);
	 rgroup->base.object.handler = MxRadioGroupHandler;
	 rgroup->base.object.Transparent = MxTrue;

#ifdef MX_WINDOW_NAMES
	 rgroup->base.object.name = "MxRadioGroup";
#endif
}

MxRadioGroup *MxRadioGroupNew(MxObject * parent, int x, int y, int w, int h, MxRadioGroupArgs * args)
{
	 return (MxRadioGroup *) MxNewObject(sizeof(MxRadioGroup), (MxVoidFunc) MxRadioGroupConstruct, parent, x, y, w, h, &args->object);
}
