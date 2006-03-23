#ifndef MX_OBJECT_SCROLL_H
#define MX_OBJECT_SCROLL_H

#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/object/slider.h"
#include "depui/object/panel.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxScroll {
		  union {
				MxObject object;
		  } base;

		  MxPanel visible;
		  MxObject *client;

		  /* Scrollbars if necessary */
		  MxSlider *vslider;
		  MxSlider *hslider;

		  unsigned int no_vscroll:1;
		  unsigned int no_hscroll:1;

		  int slider_border;
		  int slider_size;

		  int border;

	 } MxScroll;

	 typedef struct MxScrollArgs {

		  MxObjectArgs object;	  /* Must be first */

		  MxObject *client;

		  unsigned int no_vscroll;
		  unsigned int no_hscroll;

		  int border;

		  int slider_border;
		  int slider_size;

	 } MxScrollArgs;

	 void *MxScrollHandler(MxObject * object, const MxEvent * const event);
	 void *MxScrollVisibleHandler(MxObject * object, const MxEvent * const event);
	 void *MxScrollTextboxTextboxHandler(MxObject * object, const MxEvent * const event);

	 void MxScrollConstruct(MxScroll * access, MxObject * parent, int x, int y, int w, int h, MxScrollArgs * args);

#ifdef __cplusplus
}
#endif
#endif
