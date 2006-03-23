#ifndef LOAD_WINDOW_H
#define LOAD_WINDOW_H

#include <depui/depui.h>

	 typedef struct LoadWindow {
		  union {
				MxObject object;
				MxWindow window;
		  } base;

		  MxObject *inform;

	 } LoadWindow;

	 typedef struct LoadWindowArgs {

		  MxWindowArgs window;

	 } LoadWindowArgs;

	 void *LoadWindowHandler(MxObject * object, const MxEvent * const event);

	 void LoadWindowConstruct(LoadWindow * stext, MxObject * parent, int x, int y, int w, int h, LoadWindowArgs * args);

	 LoadWindow *LoadWindowNew(MxObject * parent, int x, int y, int w, int h, LoadWindowArgs * args);

	 void LoadWindowSet(LoadWindow * stext, const char *caption, unsigned int owns);

typedef MxpArgs < LoadWindowArgs > LoadWindowArgs;

class LoadWindow:public LoadWindow {
	 public:LoadWindow(MxObject * parent, int x, int y, int width, int height, LoadWindowArgs * userargs) {
		  LoadWindowConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 LoadWindow();
	 LoadWindow(const LoadWindow & other);
};

#endif

