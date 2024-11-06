#include "depui/config.h"
#include "depui/object/button.h"
#include "depui/desktop/driver.h"
#include "depui/event/focus.h"
#include "depui/event/event.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/decorate.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void draw_check(MxButton * button, int x1, int y1, int x2, int y2, const MxDecoration * const on, const MxDecoration * const off)
{
	 int outside_color = MxColorBack;
	 const MxDecoration *decoration = off;

	 MxObject *object = &button->base.object;

	 int dh;

	 if (button->pressed)
		  decoration = on;

	 if (MxFocus() == object)
		  outside_color = MxColorFocus;

	 MxFrameEmpty(x1, y1, x2, y2, 1, outside_color, outside_color);

	 dh = y1 + MxH(object) / 2 - decoration->height / 2;
	 MxDecorate(decoration, x1 + 1, dh);

	 MxFontScreenRender(0, button->base.stext.caption, MxFontDefault, x1 + decoration->width + 4, y1 + 2,
							  button->disabled ? MxColorDisabled : MxColorFore, MxColorBack);
}
