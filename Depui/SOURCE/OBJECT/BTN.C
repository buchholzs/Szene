#include "depui/config.h"
#include "depui/object/button.h"
#include "depui/event/focus.h"
#include "depui/graphics/frame.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void mx_draw_button(MxButton * button, int x1, int y1, int x2, int y2, unsigned int down, unsigned int effect, unsigned int style,
						  MxColor fore, MxColor back)
{
	 MxColor light_shadow_color = MxColorLight;
	 MxColor dark_shadow_color = MxColorDark;
	 MxColor outside_color = MxColorBack;
	 int pushed_fx = 0;

	 if ((down) && (effect))
		  pushed_fx = effect;

	 if (button->defaultbutton)
		  outside_color = MxColorFore;

	 if (button->disabled)
		  fore = MxColorDisabled;

	 if (MxFocus() == &button->base.object)
		  outside_color = MxColorFocus;

	 MxFrameEmpty(x1, y1, x2, y2, 1, outside_color, outside_color);

	 if (style) {
		  MxFrameEmpty(x1 + 1, y1 + 1, x2 - 1, y2 - 1, down ? -1 : 1, MxColorMed, dark_shadow_color);
		  MxFrameEmpty(x1 + 2, y1 + 2, x2 - 2, y2 - 2, down ? -1 : 1, light_shadow_color, MxColorMed);
	 } else {
		  MxFrameEmpty(x1 + 1, y1 + 1, x2 - 1, y2 - 1, down ? -1 : 1, MxColorLight, MxColorDark);
		  MxFrameEmpty(x1 + 2, y1 + 2, x2 - 2, y2 - 2, 1, back, back);
	 }

	 mx_draw_statictext(&button->base.stext, 1 + pushed_fx, 1 + pushed_fx, x1 + 3, y1 + 3, x2 - 3, y2 - 3, fore, back);
}
