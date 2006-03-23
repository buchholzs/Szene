#ifndef MX_OBJECT_BUTTON_H
#define MX_OBJECT_BUTTON_H

#include "depui/config.h"
#include "depui/object/object.h"
#include "depui/object/statict.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxButton {
		  union {
				MxObject object;
				MxStatictext stext;
		  } base;

		  MxCallback callback;
		  void *data;

		  unsigned int pressed:1;
		  unsigned int armed:1;
		  unsigned int disabled:1;
		  unsigned int willexit:1;

		  unsigned int submenu:1; /* Used only by menu buttons */
		  unsigned int defaultbutton:1;

		  unsigned int Style:1;

	 } MxButton;

	 typedef struct MxButtonArgs {

		  MxObjectArgs object;	  /* Must be first */

		  MxStatictextArgs stext;

		  MxCallback callback;
		  void *data;

		  unsigned int defaultbutton:1;
		  unsigned int disabled:1;

		  unsigned int Style;

	 } MxButtonArgs;

	 /* Push button */
	 void *MxPushButtonHandler(MxObject * object, const MxEvent * const event);
	 void MxPushButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);
	 MxButton *MxPushButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);

	 /* Toggle button */
	 void *MxToggleButtonHandler(MxObject * object, const MxEvent * const event);
	 void MxToggleButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);
	 MxButton *MxToggleButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);

	 /* Checkbox */
	 void *MxCheckboxHandler(MxObject * object, const MxEvent * const event);
	 void MxCheckboxConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);
	 MxButton *MxCheckboxNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);

	 /* Radio button */
	 void *MxRadioButtonHandler(MxObject * object, const MxEvent * const event);
	 void MxRadioButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);
	 MxButton *MxRadioButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);

	 /* Special Buttons */
	 void *MxExitButtonHandler(MxObject * object, const MxEvent * const event);
	 void MxExitButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);
	 MxButton *MxExitButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);

	 void *MxCancelButtonHandler(MxObject * object, const MxEvent * const event);
	 void MxCancelButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);
	 MxButton *MxCancelButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);

	 void *MxOkButtonHandler(MxObject * object, const MxEvent * const event);
	 void MxOkButtonConstruct(MxButton * button, MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);
	 MxButton *MxOkButtonNew(MxObject * parent, int x, int y, int w, int h, MxButtonArgs * args);

	 /* Internal functions */
	 void mx_draw_button(MxButton * button, int x1, int y1, int x2, int y2, unsigned int down, unsigned int effect, unsigned int style,
								MxColor fore, MxColor back);
	 void draw_check(MxButton * button, int x1, int y1, int x2, int y2, const struct MxDecoration *const on,
						  const struct MxDecoration *const off);

#define MxButtonSet(button, caption, owns) MxStatictextSet(&(button)->base.stext, caption, owns)

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxButtonArgs > MxpButtonArgs;

class MxpButton:public MxButton { protected:MxpButton() {
};

public:operator MxObject * () {
	 return &this->base.object;
};
operator const MxObject *() const {
	 return &this->base.object;
};

public:operator MxStatictext * () {
	 return &this->base.stext;
};
operator const MxStatictext *() const {
	 return &this->base.stext;
};

	 /* Unimplemented functions */
private:
MxpButton(const MxpButton & other);
};

class MxpToggleButton:public MxpButton {

	 public:MxpToggleButton(MxObject * parent, int x, int y, int width, int height, MxButtonArgs * userargs = 0) {
		  MxToggleButtonConstruct(this, parent, x, y, width, height, userargs);
	 };

	 /* Unimplemented functions */
  private:
	 MxpToggleButton();
	 MxpToggleButton(const MxpToggleButton & other);
};

class MxpPushButton:public MxpButton {

	 public:MxpPushButton(MxObject * parent, int x, int y, int width = MxDefault, int height = MxDefault, MxButtonArgs * userargs = 0) {
		  MxPushButtonConstruct(this, parent, x, y, width, height, userargs);
	 };

	 /* Unimplemented functions */
  private:
	 MxpPushButton();
	 MxpPushButton(const MxpPushButton & other);
};

class MxpCheckbox:public MxpButton {

	 public:MxpCheckbox(MxObject * parent, int x, int y, int width = MxDefault, int height = MxDefault, MxButtonArgs * userargs = 0) {
		  MxCheckboxConstruct(this, parent, x, y, width, height, userargs);
	 };

	 /* Unimplemented functions */
  private:
	 MxpCheckbox();
	 MxpCheckbox(const MxpCheckbox & other);
};

class MxpExitButton:public MxpButton {

	 public:MxpExitButton(MxObject * parent, int x, int y, int width = MxDefault, int height = MxDefault, MxButtonArgs * userargs = 0) {
		  MxExitButtonConstruct(this, parent, x, y, width, height, userargs);
	 };

	 /* Unimplemented functions */
  private:
	 MxpExitButton();
	 MxpExitButton(const MxpExitButton & other);
};

class MxpCancelButton:public MxpButton {

	 public:MxpCancelButton(MxObject * parent, int x, int y, int width = MxDefault, int height = MxDefault, MxButtonArgs * userargs = 0) {
		  MxCancelButtonConstruct(this, parent, x, y, width, height, userargs);
	 };

	 /* Unimplemented functions */
  private:
	 MxpCancelButton();
	 MxpCancelButton(const MxpCancelButton & other);
};

class MxpOkButton:public MxpButton {

	 public:MxpOkButton(MxObject * parent, int x, int y, int width = MxDefault, int height = MxDefault, MxButtonArgs * userargs = 0) {
		  MxOkButtonConstruct(this, parent, x, y, width, height, userargs);
	 };

	 /* Unimplemented functions */
  private:
	 MxpOkButton();
	 MxpOkButton(const MxpOkButton & other);
};

#endif

#endif
