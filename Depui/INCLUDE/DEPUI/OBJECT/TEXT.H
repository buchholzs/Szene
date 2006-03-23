#ifndef MX_OBJECT_TEXT_H
#define MX_OBJECT_TEXT_H

#include "depui/config.h"
#include "depui/object/scroll.h"
#include "depui/object/statict.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxTextline {
		  union {
				MxObject object;
				MxStatictext stext;
		  } base;

	 } MxTextline;

	 typedef struct MxTextlineArgs {

		  MxObjectArgs object;	  /* Must be first */
		  MxStatictextArgs stext;

	 } MxTextlineArgs;

	 void *MxTextlineHandler(MxObject * object, const MxEvent * const event);

	 void MxTextlineConstruct(MxTextline * stext, MxObject * parent, int x, int y, int w, int h, MxTextlineArgs * args);

	 MxTextline *MxTextlineNew(MxObject * parent, int x, int y, int w, int h, MxTextlineArgs * args);

	 void MxTextlineSet(MxTextline * stext, const char *caption, unsigned int owns);

	 void MxTextlineInsert(MxTextline * textline, const char *text, const int offset);
	 void MxTextlineDelete(MxTextline * textline, const int len, const int offset);

	 /* Function to determine when lines should end */
	 typedef unsigned int (*MxLineEndFunc) (const char *start, int *offset, int *skip, int width);

	 int mx_line_end_return(const char *text);
	 int mx_line_end_charwrap(const char *text, int *count, int width);

	 unsigned int MxLineEndReturn(const char *start, int *offset, int *skip, int width);
	 unsigned int MxLineEndCharwrap(const char *start, int *offset, int *skip, int width);
	 unsigned int MxLineEndWordwrap(const char *start, int *offset, int *skip, int width);

	 typedef struct MxTextareaParse {
		  unsigned int linenum;
		  unsigned int offset;
		  unsigned int len;
		  unsigned int skip;
		  unsigned int y;
		  unsigned int h;
		  unsigned int w;
	 } MxTextareaParse;

	 typedef struct MxTextarea {
		  union {
				MxObject object;
		  } base;

		  MxTextareaParse *parse;
		  unsigned int parsenum;

		  unsigned int maxw, maxh;

		  MxLineEndFunc endtest;

		  const char *caption;
		  unsigned int ownscaption:1;

		  unsigned int basecolor:1;

	 } MxTextarea;

	 typedef struct MxTextareaArgs {

		  MxObjectArgs object;	  /* Must be first */

		  MxLineEndFunc endtest;

		  const char *caption;
		  unsigned int ownscaption:1;

		  unsigned int basecolor:1;

	 } MxTextareaArgs;

	 void *MxTextareaHandler(MxObject * object, const MxEvent * const event);

	 void MxTextareaConstruct(MxTextarea * stext, MxObject * parent, int x, int y, int w, int h, MxTextareaArgs * args);

	 MxTextarea *MxTextareaNew(MxObject * parent, int x, int y, int w, int h, MxTextareaArgs * args);

	 void MxTextareaSet(MxTextarea * textarea, const char *text, unsigned int owns, unsigned int refresh);
	 void MxTextareaInsert(MxTextarea * textarea, const char *text, unsigned int offset);
	 void MxTextareaDelete(MxTextarea * textarea, const int len, const int offset);

	 const MxTextareaParse *MxTextareaParseIndex(MxTextarea * textarea, const int offset);
	 const MxTextareaParse *MxTextareaLine(MxTextarea * textarea, int y);
	 void MxTextareaPixel(MxTextarea * textarea, const MxTextareaParse * parse, const int offset, int *pixx, int *pixy);
	 int MxTextareaOffset(MxTextarea * textarea, const MxTextareaParse * parse, int *pixel);

	 void textarea_parse(MxTextarea * textarea, const int width, unsigned int inform);

	 typedef struct MxScrollTextarea {
		  union {
				MxObject object;
				MxScroll scroll;
		  } base;

		  MxTextarea textarea;

	 } MxScrollTextarea;

	 typedef struct MxScrollTextareaArgs {

		  MxObjectArgs object;	  /* Must be first */

		  MxScrollArgs scroll;
		  MxTextareaArgs textarea;

	 } MxScrollTextareaArgs;

	 void *MxScrollTextareaHandler(MxObject * object, const MxEvent * const event);

	 void MxScrollTextareaConstruct(MxScrollTextarea * textarea, MxObject * parent, int x, int y, int w, int h,
											  MxScrollTextareaArgs * args);

	 MxScrollTextarea *MxScrollTextareaNew(MxObject * parent, int x, int y, int w, int h, MxScrollTextareaArgs * args);

#define MxScrollTextareaSet(scrtextarea, text, owns) \
    MxTextareaSet(&(scrtextarea)->textarea, (text), (owns))

#define MxScrollTextareaInsert(scrtextarea, text, offset) \
    MxTextareaInsert(&(scrtextarea)->textarea, (text), (offset))

#define MxScrollTextareaDelete(scrtextarea, len, offset) \
    MxTextareaDelete(&(scrtextarea)->textarea, (len), (offset))

	 /* General textual functions */
	 char *mx_text_copy(const char *start, int len);
	 void mx_draw_tab_text(MxObject * object, MxTabstopFunc tabstop, const char *text, int x1, int y1, int x2, int y2, int offset,
								  MxColor fore_color, MxColor back_color, MxColor outer_color);
	 void mx_draw_list_button(MxObject * object, const char *text, int x1, int y1, int x2, int y2, int offset, MxColor fore_color,
									  MxColor back_color, MxTabstopFunc tabstop, unsigned int pressed, unsigned int disabled,
									  unsigned int focused);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxScrollTextareaArgs > MxpScrollTextareaArgs;

class MxpScrollTextarea:public MxScrollTextarea {
	 public:MxpScrollTextarea(MxObject * parent, int x, int y, int width, int height, MxScrollTextareaArgs * userargs) {
		  MxScrollTextareaConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpScrollTextarea();
	 MxpScrollTextarea(const MxpScrollTextarea & other);
};

#endif

#endif
