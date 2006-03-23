#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/slider.h"
#include "depui/object/defsize.h"
#include "depui/pointer/pointer.h"
#include "depui/desktop/driver.h"
#include "depui/event/focus.h"
#include "depui/event/queue.h"
#include "depui/graphics/frame.h"
#include "depui/graphics/draw.h"
#include <stdlib.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void draw_v_slider(MxSlider * slider, int x1, int y1, int x2, int y2)
{
	 MxObject *object = &slider->base.object;

	 const int border = abs(slider->border);
	 const int dborder = 2 * border;

	 long _range = 100;
	 long _thumb = 30;
	 long _index = 0;
	 long upper, lower;

	 const MxColor ring = (MxFocus() == object) ? MxColorFocus : MxColorMed;

	 _range = y2 - y1 - dborder - MxSliderMinThumb + 1;
	 if (slider->range) {
		  _thumb = slider->thumb * _range / slider->range;
		  _index = slider->index * _range / slider->range;
	 }

	 upper = y1 + border + _index;
	 lower = upper + _thumb + MxSliderMinThumb;

	 /* Draw the outer border */
	 if (slider->border)
		  MxFrameEmpty(x1, y1, object->position.x2, y2, slider->border, MxColorDark, MxColorLight);

	 /* Draw the thumb */
	 MxFrameEmpty(x1 + border, upper, x2 - border, lower, 1, ring, ring);
	 MxFrameFilled(x1 + border + 1, upper + 1, x2 - border - 1, lower - 1, 1, MxColorLight, MxColorDark, MxColorBack);

	 /* Show that the slider is sliding */
	 if (slider->slide_offset >= 0)
		  MxFrameEmpty(x1 + border + 3, upper + 3, x2 - border - 3, lower - 3, 1, MxColorDark, MxColorLight);

	 /* Draw part above thumb */
	 if (_index > 0)
		  MxScreenRectFill(0, x1 + border, y1 + border, x2 - border, upper - 1, MxColorMed);

	 /* Draw part below thumb */
	 if (lower + border < y2)
		  MxScreenRectFill(0, x1 + border, lower + 1, x2 - border, y2 - border, MxColorMed);
}

/* vertical slider event handler */
void *MxSliderVHandler(MxObject * object, const MxEvent * const event)
{
	 MxSlider *slider = (MxSlider *) object;

	 const int border = abs(slider->border);
	 const int dborder = 2 * border;

	 long _range = 100;
	 long _thumb = 30;
	 long _index = 0;
	 long upper, lower;

	 _range = object->position.y2 - object->position.y1 - dborder - MxSliderMinThumb + 1;
	 if (slider->range) {
		  _thumb = slider->thumb * _range / slider->range;
		  _index = slider->index * _range / slider->range;
	 }

	 upper = object->position.y1 + border + _index;
	 lower = upper + _thumb + MxSliderMinThumb;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventExpose:
		  draw_v_slider(slider, object->position.x1, object->position.y1, object->position.x2, object->position.y2);
		  break;

	 case MxEventButtonLeftPress:

		  MxFocusSet(object);

		  /* Did we click avove the thumb */
		  if (event->point.y < upper) {

				mx_slider_scroll_to(slider, slider->index - slider->thumb);
		  }
		  /* Did we click avove the thumb */
		  else if (event->point.y > lower) {

				mx_slider_scroll_to(slider, slider->index + slider->thumb);
		  }
		  /* Did the user try to scroll */
		  else {
				slider->slide_offset = event->point.y - upper;

				MxPointerGrab(object);
				MxPointerWantMove(object, MxTrue);
				MxEnqueueRefresh(object, MxFalse);
		  }

		  /* We did use the click */
		  return object;

	 case MxEventButtonLeftRelease:	/* on mouse button release */
		  if (slider->slide_offset >= 0) {
				slider->slide_offset = -1;

				MxPointerRelease();

				MxEnqueueRefresh(object, MxFalse);
				return object;
		  }
		  break;

	 case MxEventPointerMove:
		  if (slider->slide_offset >= 0) {

				/* Move the slider */
				_index = event->point.y - object->position.y1 - slider->slide_offset;

				mx_slider_scroll_to(slider, _index * slider->range / _range);
		  }
		  return object;

	 case MxEventKey:
		  if (MxKeyDown == event->key.key)
				mx_slider_scroll_to(slider, slider->index + slider->step);

		  else if (MxKeyUp == event->key.key)
				mx_slider_scroll_to(slider, slider->index - slider->step);

		  else if (MxKeyPageup == event->key.key)
				mx_slider_scroll_to(slider, slider->index - slider->thumb);

		  else if (MxKeyPagedown == event->key.key)
				mx_slider_scroll_to(slider, slider->index + slider->thumb);
		  else
				return 0;

		  return object;

	 case MxEventFocusGot:
	 case MxEventFocusLost:
		  MxEnqueueRefresh(object, MxFalse);
		  return object;

	 default:
		  break;
	 }
	 return 0;
}

void MxSliderVConstruct(MxSlider * slider, MxObject * parent, int x, int y, int w, int h, MxSliderArgs * args)
{
	 assert(slider);
	 MxDefaultSize(&w, &h, MxSliderDefaultSize, 100);

	 mx_construct_slider(slider, parent, x, y, w, h, MxSliderVHandler, args);

#ifdef MX_WINDOW_NAMES
	 slider->base.object.name = "MxSliderVertical";
#endif
}

MxSlider *MxSliderVNew(MxObject * parent, int x, int y, int w, int h, MxSliderArgs * args)
{
	 return (MxSlider *) MxNewObject(sizeof(MxSlider), (MxVoidFunc) MxSliderVConstruct, parent, x, y, w, h, &args->object);
}
