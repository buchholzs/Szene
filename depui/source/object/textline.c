#include "depui/config.h"
#include "depui/macros.h"
#include "depui/args/args.h"
#include "depui/object/text.h"
#include "depui/object/defsize.h"
#include "depui/desktop/driver.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static int mx_textline_default_width(const char *caption)
{
	 const unsigned int len = strlen(caption);
	 const char *temp = mx_text_copy(caption, len);
	 const int defw = MxFontLength(MxFontDefault, temp) + 2;

	 assert(temp);

	 MxFree((char *) temp);
	 return defw;
}

void *MxTextlineHandler(MxObject * object, const MxEvent * const event)
{
	 MxTextline *stext = (MxTextline *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  mx_draw_statictext(&stext->base.stext, 0, 0, object->position.x1, object->position.y1, object->position.x2,
									object->position.y2, MxColorObjectFore, MxColorObjectBack);
		  break;

		  /* Pass the drop event to the textbox */
	 case MxEventDropTarget:
		  return MxEventSend(MxParent(object), event);

		  /* Don't let us be set to narrower than we really need */
	 case MxEventGeomRequest:

		  /* Are they trying to change our width */
		  if (event->geom.data->flags & MxGeomW) {

				/* Don't let the width get too small */
				const int defw = mx_textline_default_width(stext->base.stext.caption);

				event->geom.data->w = MX_MAX(event->geom.data->w, defw);
		  }
		  /* Fall through */

	 default:
		  return MxStatictextHandler(object, event);
	 }
	 return 0;
}

void MxTextlineConstruct(MxTextline * stext, MxObject * parent, int x, int y, int w, int h, MxTextlineArgs * userargs)
{
	 MxTextlineArgs args;

	 assert(stext);
	 MxUserArgsInit(args, userargs);

	 memset(stext, 0, sizeof(MxTextline));
	 MxStatictextConstruct(&stext->base.stext, parent, x, y, w, h, &args.stext);
	 stext->base.object.handler = MxTextlineHandler;

#ifdef MX_WINDOW_NAMES
	 stext->base.object.name = "MxTextline";
#endif
}

MxTextline *MxTextlineNew(MxObject * parent, int x, int y, int w, int h, MxTextlineArgs * args)
{
	 return (MxTextline *) MxNewObject(sizeof(MxTextline), (MxVoidFunc) MxTextlineConstruct, parent, x, y, w, h, &args->object);
}
