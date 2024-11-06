#ifndef MX_OBJECT_EDIT_H
#define MX_OBJECT_EDIT_H

#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/object/cursor.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxEditline {
		  union {
				MxObject object;
				MxStatictext stext;
				MxTextline textline;
		  } base;

		  MxCursor cursor;
		  unsigned int offset;	  /* Cursor text offset in caption */

	 } MxEditline;

	 typedef struct MxEditlineArgs {

		  MxObjectArgs object;	  /* Must be first */
		  MxTextlineArgs textline;
		  MxCursorArgs cursor;

	 } MxEditlineArgs;

	 void *MxEditlineHandler(MxObject * object, const MxEvent * const event);

	 void MxEditlineConstruct(MxEditline * stext, MxObject * parent, int x, int y, int w, int h, MxEditlineArgs * args);

	 MxEditline *MxEditlineNew(MxObject * parent, int x, int y, int w, int h, MxEditlineArgs * args);

	 void MxEditlineSet(MxEditline * stext, const char *caption);
	 void MxEditlineCursorTo(MxEditline * line, unsigned int cursorindex);
	 const char *MxEditlineCaption(MxEditline * line);

	 typedef struct MxEditarea {
		  union {
				MxObject object;
				MxTextarea textarea;
		  } base;

		  MxCursor cursor;
		  unsigned int offset;	  /* Cursor text offset in textbox caption */
		  unsigned int xpixel;	  /* Desired xpixel offset of the cursor */

	 } MxEditarea;

	 typedef struct MxEditareaArgs {

		  MxObjectArgs object;	  /* Must be first */

		  MxTextareaArgs textarea;

		  MxCursorArgs cursor;

	 } MxEditareaArgs;

	 void *MxEditareaHandler(MxObject * object, const MxEvent * const event);

	 void MxEditareaConstruct(MxEditarea * editarea, MxObject * parent, int x, int y, int w, int h, MxEditareaArgs * args);

	 MxEditarea *MxEditareaNew(MxObject * parent, int x, int y, int w, int h, MxEditareaArgs * args);

	 const char *MxEditareaCaption(MxEditarea * editbox);
	 void MxEditareaSet(MxEditarea * editbox, const char *text, unsigned int owns, unsigned int refresh);

#define MxEditareaLength(editarea) (strlen((editarea)->base.textarea.caption))
#define MxEditareaCopy(editarea, dest) (strcpy(dest, (editarea)->base.textarea.caption))

	 typedef struct MxScrollEditarea {
		  union {
				MxObject object;
				MxScroll scroll;
		  } base;

		  MxEditarea editarea;

	 } MxScrollEditarea;

	 typedef struct MxScrollEditareaArgs {

		  MxObjectArgs object;	  /* Must be first */

		  MxScrollArgs scroll;
		  MxEditareaArgs editarea;

	 } MxScrollEditareaArgs;

	 void *MxScrollEditareaEditareaHandler(MxObject * object, const MxEvent * const event);
	 void *MxScrollEditareaPanelHandler(MxObject * object, const MxEvent * const event);
	 void *MxScrollEditareaHandler(MxObject * object, const MxEvent * const event);

	 void MxScrollEditareaConstruct(MxScrollEditarea * editarea, MxObject * parent, int x, int y, int w, int h,
											  MxScrollEditareaArgs * args);

	 MxScrollEditarea *MxScrollEditareaNew(MxObject * parent, int x, int y, int w, int h, MxScrollEditareaArgs * args);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxEditlineArgs > MxpEditlineArgs;

class MxpEditline:public MxEditline {
	 public:MxpEditline(MxObject * parent, int x, int y, int width, int height, MxEditlineArgs * userargs) {
		  MxEditlineConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpEditline();
	 MxpEditline(const MxpEditline & other);
};

typedef MxpArgs < MxScrollEditareaArgs > MxpScrollEditareaArgs;

class MxpScrollEditarea:public MxScrollEditarea {
	 public:MxpScrollEditarea(MxObject * parent, int x, int y, int width, int height, MxScrollEditareaArgs * userargs) {
		  MxScrollEditareaConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpScrollEditarea();
	 MxpScrollEditarea(const MxpScrollEditarea & other);
};

#endif

#endif
