#include "depui/config.h"
#include "depui/object/defsize.h"
#include "depui/object/text.h"
#include "depui/object/statict.h"
#include "depui/graphics/draw.h"
#include "depui/desktop/driver.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_draw_statictext(MxStatictext * stext, int x, int y, int x1, int y1, int x2, int y2, MxColor fore, MxColor back)
{
	 unsigned int i;
	 MxRect rect;
	 MxRegion blank;
	 const int border = abs(stext->border);

	 const char *temp = stext->caption;

	 /* Find the rectangles where the background is, so we don't overdraw */
	 MxRegionConstruct(&blank);
	 rect.x1 = x1 + border;
	 rect.y1 = y1 + border;
	 rect.x2 = x2 - border;
	 rect.y2 = y2 - border;
	 MxRegionAddRect(&blank, &rect);

	 if (temp[0]) {
		  rect.x1 = x1 + stext->tx + x;
		  rect.y1 = y1 + stext->ty + y;
		  rect.x2 = rect.x1 + stext->tw - 1;
		  rect.y2 = rect.y1 + stext->th - 1;
		  MxRegionClipRect(&blank, &rect);
	 }

	 /* Dear the empty areas */
	 for (i = 0; i < MxRegionNumber(blank); i++) {
		  const MxRect *s = MxRegionRect(blank, i);

		  MxScreenRectFill(0, s->x1, s->y1, s->x2, s->y2, back);
	 }

	 /* Draw the caption */
	 if ((temp) && (temp[0]))
		  MxFontScreenRender(0, temp, MxFontDefault, x1 + stext->tx + x, y1 + stext->ty + y, fore, back);

	 /* Draw the outside area */
	 MxFrameEmpty(x1, y1, x2, y2, stext->border, MxColorLight, MxColorDark);

	 /* Cleanup */
	 MxRegionDestruct(&blank);
}

void mx_statictext_justify(MxStatictext * stext, int x1, int y1, int x2, int y2)
{
	 const int border = abs(stext->border);
	 const char *temp = stext->caption;
	 const int w = x2 - x1 + 1 - 2 * border;
	 const int h = y2 - y1 + 1 - 2 * border;

	 stext->th = MxFontHeight(MxFontDefault);

	 stext->tw = -1;
	 if (temp)
		  stext->tw = MxFontLength(MxFontDefault, temp);

	 if (stext->just & MxJustifyHLeft)
		  stext->tx = border;

	 if (stext->just & MxJustifyHRight)
		  stext->tx = border + w - stext->tw;

	 if (stext->just & MxJustifyHCenter)
		  stext->tx = border + (w - stext->tw) / 2;

	 if (stext->just & MxJustifyVTop)
		  stext->ty = border;

	 if (stext->just & MxJustifyVBot)
		  stext->ty = border + h - stext->th;

	 if (stext->just & MxJustifyVCenter)
		  stext->ty = border + (h - stext->th) / 2;

	 stext->justified = MxTrue;
}

void *MxStatictextHandler(MxObject * object, const MxEvent * const event)
{
	 MxStatictext *stext = (MxStatictext *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  /* Justify everything at the last minute */
		  if (!stext->justified)
				mx_statictext_justify(stext, object->position.x1, object->position.y1, object->position.x2, object->position.y2);

		  /* Now we can continue with the drawing */
		  mx_draw_statictext(stext, 0, 0, object->position.x1, object->position.y1, object->position.x2, object->position.y2,
									MxColorFore, MxColorBack);
		  break;

	 case MxEventDestroy:
		  if ((stext->ownscaption) && (stext->caption))
				MxFree((char *) stext->caption);
		  break;

	 case MxEventPostInit:
		  stext->justified = MxFalse;
		  break;

	 case MxEventGeomChanged:
		  stext->justified = MxFalse;
		  break;

	 case MxEventGetCaption:
		  return (void *) stext->caption;

	 default:
		  break;
	 }
	 return 0;
}

void MxStatictextConstruct(MxStatictext * stext, MxObject * parent, int x, int y, int w, int h, MxStatictextArgs * userargs)
{
	 int defw, defh;

	 MxStatictextArgs args;

	 assert(stext);
	 MxUserArgsInit(args, userargs);

	 if (args.caption) {
		  const char *temp = mx_text_copy(args.caption, args.len);

		  defw = MxFontLength(MxFontDefault, args.caption) + 1;

		  MxFree((char *) temp);
	 } else
		  defw = 10;
	 defh = MxFontHeight(MxFontDefault) + 1;
	 MxDefaultSize(&w, &h, defw, defh);

	 memset(stext, 0, sizeof(MxStatictext));
	 MxObjectConstruct(&stext->base.object, 0, x, y, w, h, &args.object);
	 stext->base.object.handler = MxStatictextHandler;

	 stext->caption = args.caption;
	 stext->ownscaption = args.ownscaption;
	 stext->just = args.just;
	 stext->border = args.border;

	 stext->tx = 1 + abs(args.border);
	 stext->ty = 1 + abs(args.border);

	 stext->justified = MxFalse;

#ifdef MX_WINDOW_NAMES
	 stext->base.object.name = "MxStatictext";
#endif

	 if (parent)
		  MxInsert(&stext->base.object, parent, MxFalse);
}

MxStatictext *MxStatictextNew(MxObject * parent, int x, int y, int w, int h, MxStatictextArgs * args)
{
	 return (MxStatictext *) MxNewObject(sizeof(MxStatictext), (MxVoidFunc) MxStatictextConstruct, parent, x, y, w, h, &args->object);
}
