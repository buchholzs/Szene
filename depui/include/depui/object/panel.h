#ifndef MX_OBJECT_PANEL_H
#define MX_OBJECT_PANEL_H

#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/graphics/frame.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxPanel {
		  union {
				MxObject object;
		  } base;

		  MxFrameFunc frame;
		  int effect;

		  int color;

		  unsigned int PassGeometry:1;

	 } MxPanel;

	 typedef struct MxPanelArgs {

		  MxObjectArgs object;	  /* Must be first */

		  MxFrameFunc frame;
		  int effect;

		  int color;
		  unsigned int hascolor;

	 } MxPanelArgs;

	 void *MxPanelHandler(MxObject * object, const MxEvent * const event);

	 void MxPanelConstruct(MxPanel * panel, MxObject * parent, int x, int y, int w, int h, MxPanelArgs * args);

	 MxPanel *MxPanelNew(MxObject * parent, int x, int y, int w, int h, MxPanelArgs * args);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxPanelArgs > MxpPanelArgs;

class MxpPanel:public MxPanel {
	 public:MxpPanel(MxObject * parent, int x, int y, int width, int height, MxPanelArgs * userargs) {
		  MxPanelConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpPanel();
	 MxpPanel(const MxpPanel & other);
};

#endif

#endif
