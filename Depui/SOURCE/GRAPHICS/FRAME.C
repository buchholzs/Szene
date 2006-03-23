#include "depui/config.h"
#include "depui/types.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/draw.h"
#include "depui/desktop/driver.h"
#include <stdlib.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxFrameEmpty(int x1, int y1, int x2, int y2, int width, MxColor light_color, MxColor dark_color)
{
	 int i;

	 if (width < 0) {
		  int temp = light_color;

		  light_color = dark_color;
		  dark_color = temp;

		  width *= -1;
	 }

	 for (i = 0; i < width; i++) {
		  MxScreenVLine(0, x1, y1, y2, light_color);
		  MxScreenHLine(0, x1 + 1, y1, x2, light_color);

		  MxScreenVLine(0, x2, y1 + 1, y2, dark_color);
		  MxScreenHLine(0, x1 + 1, y2, x2 - 1, dark_color);

		  x1++, y1++, x2--, y2--;
	 }
}

void MxFrameFilled(int x1, int y1, int x2, int y2, int width, MxColor light_color, MxColor dark_color, MxColor fill_color)
{
	 MxFrameEmpty(x1, y1, x2, y2, width, light_color, dark_color);
	 MxScreenRectFill(0, x1 + abs(width), y1 + abs(width), x2 - abs(width), y2 - abs(width), fill_color);
}

void MxFrameButton(int x1, int y1, int x2, int y2, unsigned int pressed, unsigned int focus, const char *text, MxColor outside_color1,
						 MxColor outside_color2)
{
	 int light_shadow_color = MxColorLight, dark_shadow_color = MxColorDark, pushed_fx = 0;

	 int fore_color = MxColorFore, back_color = MxColorBack;

	 if (pressed) {				  /* if button is pressed swap */
		  int temp = light_shadow_color;

		  light_shadow_color = dark_shadow_color;
		  dark_shadow_color = temp;
		  pushed_fx = 1;
	 }

	 if (focus) {
		  outside_color1 = MxColorFocus, outside_color2 = MxColorFocus;
	 }

	 MxFrameEmpty(x1, y1, x2, y2, 1, outside_color1, outside_color2);

	 MxFrameEmpty(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 1, light_shadow_color, dark_shadow_color);

	 MxScreenRectFill(0, x1 + 2, y1 + 2, x2 - 2, y2 - 2, back_color);

	 if (text)
		  MxFontScreenRender(0, text, MxFontDefault, x1 + 3 + pushed_fx, y1 + 3 + pushed_fx, fore_color, back_color);
}
