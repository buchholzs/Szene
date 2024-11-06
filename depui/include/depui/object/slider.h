#ifndef MX_OBJECT_SLIDER_H
#define MX_OBJECT_SLIDER_H

#include "depui/config.h"
#include "depui/object/object.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
#define MxSliderDefaultSize  10
#define MxSliderMinThumb     10
	 typedef struct MxSlider {	  /* a button object */
		  union {
				MxObject object;
		  } base;

		  MxObject *target;
		  int slide_offset;
		  int index;
		  int range;
		  int thumb;
		  int step;

		  int border;
	 } MxSlider;

	 typedef struct MxSliderArgs {	/* a button object */

		  MxObjectArgs object;	  /* Must be first */

		  MxObject *target;
		  int index;
		  int range;
		  int thumb;
		  int step;

		  int border;

	 } MxSliderArgs;

/* Private include functions */
	 void mx_slider_scroll_to(MxSlider * slider, int scrollindex);
	 void mx_construct_slider(MxSlider * slider, MxObject * parent, int x, int y, int w, int h, MxHandler event_handler,
									  MxSliderArgs * userargs);

	 unsigned int MxSliderGoTo(MxSlider * slider, int scrollindex);

	 void *MxSliderVHandler(MxObject * object, const MxEvent * const event);
	 void *MxSliderHHandler(MxObject * object, const MxEvent * const event);

	 void MxSliderVConstruct(MxSlider * slider, MxObject * parent, int x, int y, int w, int h, MxSliderArgs * args);
	 void MxSliderHConstruct(MxSlider * slider, MxObject * parent, int x, int y, int w, int h, MxSliderArgs * args);

	 MxSlider *MxSliderHNew(MxObject * parent, int x, int y, int w, int h, MxSliderArgs * args);
	 MxSlider *MxSliderVNew(MxObject * parent, int x, int y, int w, int h, MxSliderArgs * args);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxSliderArgs > MxpSliderArgs;

class MxpSliderH:public MxSlider {
	 public:MxpSliderH(MxObject * parent, int x, int y, int width, int height, MxSliderArgs * userargs) {
		  MxSliderHConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpSliderH();
	 MxpSliderH(const MxpSliderH & other);
};

class MxpSliderV:public MxSlider {

	 public:MxpSliderV(MxObject * parent, int x, int y, int width, int height, MxSliderArgs * userargs) {
		  MxSliderVConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpSliderV();
	 MxpSliderV(const MxpSliderV & other);
};

#endif

#endif
