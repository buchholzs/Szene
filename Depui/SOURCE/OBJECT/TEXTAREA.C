#include "depui/config.h"
#include "depui/macros.h"
#include "depui/args/args.h"
#include "depui/object/text.h"
#include "depui/object/defsize.h"
#include "depui/event/queue.h"
#include "depui/desktop/driver.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void textarea_parse(MxTextarea * textarea, const int width, unsigned int inform)
{
	 int i = 0;
	 unsigned int done = 0;
	 int offset = 0;
	 const int lineheight = MxFontHeight(MxFontDefault) + 1;
	 int allocated;

	 assert(textarea);
	 assert(textarea->caption);

	 MX_TRACE("");

	 /* Inform later classes that we are being reparsed */
	 MxEventSendSimple(&textarea->base.object, MxEventTextareaPreparse);

	 /* Clean up old parsed lines */
	 if (textarea->parse)
		  textarea->parse = (MxTextareaParse *) MxRealloc(textarea->parse, sizeof(MxTextareaParse));
	 else
		  textarea->parse = (MxTextareaParse *) MxMalloc(sizeof(MxTextareaParse));
	 textarea->parsenum = 1;
	 allocated = 1;

	 memset(&textarea->parse[0], 0, sizeof(MxTextareaParse));

	 textarea->maxw = 0;
	 textarea->maxh = 0;

	 /* Update if necessary before AND after to make sure we handle resizing
	    properly */
	 if ((textarea->base.object.init) && (inform))
		  MxEnqueueRefresh(&textarea->base.object, MxFalse);

	 /* Parse each line of the textarea */
	 while (!done) {

		  /* Parse one line and stop parsing when we are done */
		  char *temp;
		  unsigned int linewidth = 0;
		  int oldoffset = offset, skip = 0;
		  int len;

		  /* Find the end of the line */
		  done = textarea->endtest(textarea->caption, &offset, &skip, width);
		  len = offset - oldoffset;

		  /* Make sure we stop if we ran out of text */
		  if (!textarea->caption[offset])
				done = MxTrue;

		  /* Do we need to make more array room */
		  if (i >= allocated) {
				allocated = allocated * 2;
				textarea->parse = (MxTextareaParse *) MxRealloc(textarea->parse, allocated * sizeof(MxTextareaParse));
		  }

		  /* Set the parsed line info */
		  textarea->parse[i].linenum = i;
		  textarea->parse[i].offset = oldoffset;
		  textarea->parse[i].len = len;
		  textarea->parse[i].skip = skip;

		  /* Find out the text position and size */
		  temp = mx_text_copy(&textarea->caption[oldoffset], len);
		  if (temp) {
				linewidth = MxFontLength(MxFontDefault, temp) + 1;
				MxFree(temp);
		  }
		  textarea->parse[i].y = textarea->maxh;
		  textarea->parse[i].w = linewidth;
		  textarea->parse[i].h = lineheight;

		  /* Keep track of our max size */
		  if (linewidth > textarea->maxw)
				textarea->maxw = linewidth;
		  textarea->maxh += lineheight;

		  /* Skip some bytes if asked to, but if we skipped some chars at the
		     end, we have to add another blank line */
		  if (skip > 0) {
				offset += skip;
				done = MxFalse;
		  }

		  /* Goto the next line */
		  ++i;
	 }

	 /* Make sure we give up any memory that we didn't need and find out
	    exactly how much memory we really need */
	 if (allocated != i)
		  textarea->parse = (MxTextareaParse *) MxRealloc(textarea->parse, i * sizeof(MxTextareaParse));
	 textarea->parsenum = i;

	 /* Inform later classes that we are being reparsed */
	 MxEventSendSimple(&textarea->base.object, MxEventTextareaPostparse);

	 /* Update if necessary */
	 if ((textarea->base.object.init) && (inform)) {
		  MxResize(&textarea->base.object, textarea->maxw, textarea->maxh);
		  MxEventSendSimple(MxParent(&textarea->base.object), MxEventGeomChildChanged);
	 }
}

static void drawline(MxTextarea * textarea, const MxTextareaParse * parse, int x1, int y1, int x2, MxColor fore, MxColor back)
{
	 const char *caption = &textarea->caption[parse->offset];
	 char *temp = mx_text_copy(caption, parse->len);
	 const int y = y1 + parse->y;
	 int lhs = x1;

	 /* Draw the text */
	 if (temp) {
		  MxFontScreenRender(0, temp, MxFontDefault, x1 + 1, y + 1, fore, back);
		  lhs += parse->w;
		  MxScreenHLine(0, x1, y, lhs, back);
		  MxScreenVLine(0, x1, y + 1, y + parse->h - 1, back);
		  MxFree(temp);
	 }
	 /* Draw the empty rhs of the text */
	 if (lhs <= x2) {
		  const int liney2 = y + parse->h - 1;

		  MxScreenRectFill(0, lhs, y, x2, liney2, back);
	 }
}

static void draw(MxTextarea * textarea, int x1, int y1, int x2, int y2, const MxRegion * const region)
{
	 int bot;
	 unsigned int i;
	 const MxTextareaParse *parse;

	 /* Get the extent of the region so we can maybe skip some lines */
	 MxRect rect;
	 const unsigned int regionvalid = MxRegionExtent(region, &rect);

	 /* Figure out what colors should be */
	 const MxColor fore = (textarea->basecolor) ? MxColorFore : MxColorObjectFore;
	 const MxColor back = (textarea->basecolor) ? MxColorBack : MxColorObjectBack;

	 for (i = 0; i < textarea->parsenum; i++) {

		  /* Assume we have to draw the line */
		  unsigned int mustdraw = MxTrue;

		  /* Can we skip the line */
		  parse = &textarea->parse[i];
		  if (regionvalid) {
				if ((y1 + (int) parse->y > rect.y2) || (y1 + (int) parse->y + (int) parse->h < rect.y1))
					 mustdraw = MxFalse;
		  }

		  /* Draw the line if we have to */
		  if (mustdraw)
				drawline(textarea, parse, x1, y1, x2, fore, back);
	 }

	 /* Possibly fill in the blank area underneath */
	 parse = &textarea->parse[textarea->parsenum - 1];
	 bot = y1 + (int) parse->y + (int) parse->h;

	 if (bot <= y2)
		  MxScreenRectFill(0, x1, bot, x2, y2, back);
}

void *MxTextareaHandler(MxObject * object, const MxEvent * const event)
{
	 MxTextarea *textarea = (MxTextarea *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw(textarea, object->position.x1, object->position.y1, object->position.x2, object->position.y2, event->region.region);
		  break;

	 case MxEventGeomRequest:

		  /* Can we reparse the object to fit that width */
		  if (event->geom.data->flags & MxGeomW) {

				/* Maybe our parser won't allow any width */
				if (!textarea->endtest(0, 0, 0, 0))
					 event->geom.data->w = MX_MAX(event->geom.data->w, (int) textarea->maxw);

		  }
		  /* Set our minimum height */
		  if (event->geom.data->flags & MxGeomH)
				event->geom.data->h = MX_MAX(event->geom.data->h, (int) textarea->maxh);
		  break;

	 case MxEventGeomChanged:
		  if ((event->geom.data->flags & MxGeomH) || (event->geom.data->flags & MxGeomW))

				/* Only reparse if we have to */
				if (textarea->endtest(0, 0, 0, 0))
					 textarea_parse(textarea, MxW(&textarea->base.object), MxFalse);
		  break;

	 case MxEventDestroy:

		  /* Cleanup our caption */
		  if ((textarea->ownscaption) && (textarea->caption))
				MxFree((char *) textarea->caption);

		  /* Cleanup our parsing info also */
		  if (textarea->parse)
				MxFree(textarea->parse);

		  break;

	 default:
		  return 0;
	 }
	 return 0;
}

void MxTextareaConstruct(MxTextarea * textarea, MxObject * parent, int x, int y, int w, int h, MxTextareaArgs * userargs)
{
	 MxTextareaArgs args;

	 assert(textarea);
	 MxUserArgsInit(args, userargs);

	 memset(textarea, 0, sizeof(MxTextarea));
	 MxObjectConstruct(&textarea->base.object, parent, x, y, w, h, &args.object);
	 textarea->base.object.handler = MxTextareaHandler;

	 if (args.endtest)
		  textarea->endtest = args.endtest;
	 else
		  textarea->endtest = MxLineEndReturn;

	 textarea->basecolor = args.basecolor;

	 /* Set the caption */
	 if (args.caption)
		  MxTextareaSet(textarea, args.caption, args.ownscaption, MxFalse);
	 else
		  MxTextareaSet(textarea, "", MxFalse, MxFalse);

	 /* Start with the correct size */
	 if (w == MxDefault)
		  w = textarea->maxw;
	 if (h == MxDefault)
		  h = textarea->maxh;
	 MxGeomSize(&textarea->base.object, w, h);

#ifdef MX_WINDOW_NAMES
	 textarea->base.object.name = "MxTextarea";
#endif
}

MxTextarea *MxTextareaNew(MxObject * parent, int x, int y, int w, int h, MxTextareaArgs * args)
{
	 return (MxTextarea *) MxNewObject(sizeof(MxTextarea), (MxVoidFunc) MxTextareaConstruct, parent, x, y, w, h, &args->object);
}

void MxTextareaSet(MxTextarea * textarea, const char *text, unsigned int owns, unsigned int refresh)
{
	 assert(textarea);

	 MX_TRACE("");

	 /* Clean up any old caption */
	 if ((textarea->ownscaption) && (text != textarea->caption))
		  MxFree((char *) textarea->caption);

	 /* Set the new caption */
	 if (text) {
		  textarea->caption = text;
		  textarea->ownscaption = owns;
	 } else {
		  textarea->caption = "";
		  textarea->ownscaption = MxFalse;
	 }

	 /* Split up the text into lines, try to use our current width */
	 textarea_parse(textarea, MxW(&textarea->base.object), refresh);
}
