#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_draw_list_button(MxObject * object, const char *text, int x1, int y1, int x2, int y2, int offset, MxColor fore_color,
								 MxColor back_color, MxTabstopFunc tabstop, unsigned int pressed, unsigned int disabled, unsigned int focused)
{
	 MxColor outer_color = back_color;

	 if (pressed) {
		  fore_color = MxColorSelectedFore;
		  back_color = MxColorSelectedBack;
	 }

	 if (disabled)
		  fore_color = MxColorDisabled;

	 if (focused)
		  outer_color = MxColorFocus;

	 mx_draw_tab_text(object, tabstop, text, x1, y1, x2, y2, offset, fore_color, back_color, outer_color);
}
