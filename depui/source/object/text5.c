#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/desktop/driver.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/clip.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_draw_tab_text(MxObject * object, MxTabstopFunc tabstop, const char *text, int x1, int y1, int x2, int y2, int offset,
							 MxColor fore_color, MxColor back_color, MxColor outer_color)
{
	 unsigned int done = MxFalse;

	 int i = 0;

	 int leftside = offset;

	 MxFrameEmpty(x1, y1, x2, y2, 1, outer_color, outer_color);
	 MxFrameEmpty(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 1, back_color, back_color);
	 MxScreenRectFill(0, x1 + 2, y1 + 2, x1 + offset - 1, y2 - 2, back_color);

	 /* Draw the captions as necessary */
	 while ((text) && (!done)) {

		  /* Check to see if we will draw multiple coloums */
		  const char *next = strchr(text, '\t');

		  if (next) {

				MxRect coloumrect;
				MxRegion oldregion;
				MxRegion coloumregion;

				int len;
				int rightside = leftside;

				/* Make a copy of the coloum */
				const char *temp = mx_text_copy(text, next - text);

				assert(temp);

				/* Find the coloum width */
				if (tabstop)
					 rightside = leftside + tabstop(object, i);

				/* Remember the old region */
				MxRegionCopyConstruct(&oldregion, &mx_region);
				MxRegionCopyConstruct(&coloumregion, &mx_region);

				/* Clip to this coloum */
				coloumrect.x1 = x1 + leftside;
				coloumrect.y1 = y1;
				coloumrect.x2 = x1 + rightside;
				coloumrect.y2 = y2;

				/* Find the visible part of the coloum */
				MxRegionIntersectRect(&coloumregion, &coloumrect);

				/* Clip to the visible part of this coloum */
				MxRegionDestruct(&mx_region);
				MxRegionCopyConstruct(&mx_region, &coloumregion);

				/* Print out the text at the correct offset */
				MxFontScreenRender(0, temp, MxFontDefault, x1 + leftside, y1 + 2, fore_color, back_color);

				/* Blank to the side of the text */
				len = MxFontLength(MxFontDefault, temp);
				MxScreenRectFill(0, x1 + leftside + len, y1 + 2, x1 + rightside, y2 - 2, back_color);

				/* Draw the dividing line */
//            MxScreenVLine(0, x1 + rightside - 1, y1, y2, MxColorDark);

				/* Go to the next coloum */
				++i, text = next + 1, leftside = rightside;

				/* Clean up out temporary copy of the coloum */
				MxFree((char *) temp);

				/* Replace the old clipping region */
				MxRegionDestruct(&mx_region);
				MxRegionCopyConstruct(&mx_region, &oldregion);

				MxRegionDestruct(&oldregion);
				MxRegionDestruct(&coloumregion);

				/* We only have one coloum (or just one left) */
		  } else {
				int len;

				MxFontScreenRender(0, text, MxFontDefault, x1 + leftside, y1 + 2, fore_color, back_color);

				/* Cleanup to the right side */
				len = MxFontLength(MxFontDefault, text);
				MxScreenRectFill(0, x1 + leftside + len, y1 + 2, x2 - 2, y2 - 2, back_color);

				done = MxTrue;
		  }
	 }

}
