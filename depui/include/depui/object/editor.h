#ifndef MX_OBJECT_EDITOR_H
#define MX_OBJECT_EDITOR_H

#include "depui/config.h"
#include "depui/object/edit.h"
#include "depui/object/window.h"
#include "depui/object/menu.h"
#include "depui/object/filesel.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxEditor {
		  union {
				MxObject object;
				MxWindow win;
		  } base;

		  MxScrollEditarea scrledit;
		  MxMenu menu;

		  MxFileselector *filesave;
		  MxFileselector *fileopen;
		  char filename[MX_MAX_PATH];

	 } MxEditor;

	 typedef struct MxEditorArgs {
		  MxObjectArgs object;	  /* Must be first */

		  MxWindowArgs win;
		  MxScrollEditareaArgs scrledit;
		  MxMenuArgs menu;

	 } MxEditorArgs;

	 extern MxMenuDef MxEditorFilemenu[];
	 extern MxMenuDef MxEditorTopmenu[];

	 void *MxEditorHandler(MxObject * object, const MxEvent * const event);

	 void MxEditorConstruct(MxEditor * stext, MxObject * parent, int x, int y, int w, int h, MxEditorArgs * args);

	 MxEditor *MxEditorNew(MxObject * parent, int x, int y, int w, int h, MxEditorArgs * args);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxEditorArgs > MxpEditorArgs;

class MxpEditor:public MxEditor {
	 public:MxpEditor(MxObject * parent, int x, int y, int width, int height, MxEditorArgs * userargs = 0) {
		  MxEditorConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpEditor();
	 MxpEditor(const MxpEditor & other);
};

#endif

#endif
