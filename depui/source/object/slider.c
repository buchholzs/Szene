#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/slider.h"
#include "depui/args/args.h"
#include "depui/event/queue.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static void _limit_thumb(MxSlider * slider)
{
	 long v;

	 if (slider->step < 1)
		  slider->step = 1;

	 /* Quantization of index */
	 v = (2 * slider->index + slider->step) / slider->step;
	 slider->index = (v / 2) * slider->step;

	 if (slider->thumb > slider->range) {
		  slider->thumb = slider->range;
		  slider->index = 0;
	 }

	 if (slider->thumb < 0)
		  slider->thumb = 0;

	 if (slider->index > (slider->range - slider->thumb))
		  slider->index = slider->range - slider->thumb;

	 if (slider->index < 0)
		  slider->index = 0;
}

static void _scroll_target(MxSlider * slider)
{
	 if ((slider->target) && (slider->target->init)) {

		  MxEvent event;

		  event.type = MxEventSlider;
		  event.slider.offset = slider->index;
		  event.slider.source = slider;

		  MxEventSend(slider->target, &event);
	 }
}

unsigned int MxSliderGoTo(MxSlider * slider, int index)
{
	 long old = slider->index;

	 if ((slider->index != index) && (slider->base.object.init)) {

		  slider->index = index;
		  _limit_thumb(slider);
	 }
	 return slider->index != old;
}

void mx_slider_scroll_to(MxSlider * slider, int index)
{
	 if (MxSliderGoTo(slider, index)) {

		  _scroll_target(slider);
		  MxEnqueueRefresh(&slider->base.object, MxFalse);
	 }
}

void mx_construct_slider(MxSlider * slider, MxObject * parent, int x, int y, int w, int h, MxHandler handler, MxSliderArgs * userargs)
{
	 MxSliderArgs args;

	 MxUserArgsInit(args, userargs);

	 memset(slider, 0, sizeof(MxSlider));
	 MxObjectConstruct(&slider->base.object, parent, x, y, w, h, &args.object);
	 slider->base.object.handler = handler;

	 slider->target = args.target;
	 slider->index = args.index;
	 slider->range = args.range ? args.range : 100;
	 slider->thumb = args.thumb ? args.thumb : 30;
	 slider->step = args.step ? args.step : 1;
	 slider->slide_offset = -1;
	 slider->border = args.border + 1;

#ifdef MX_WINDOW_NAMES
	 slider->base.object.name = "MxSlider";
#endif

}
