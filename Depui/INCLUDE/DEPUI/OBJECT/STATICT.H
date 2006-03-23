#ifndef MX_OBJECT_STATICT_H
#define MX_OBJECT_STATICT_H

#include "depui/config.h"
#include "depui/object/object.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef enum MxStatictextJustify {
		  MxJustifyHNone = 0,

		  MxJustifyHLeft = 1,
		  MxJustifyHRight = 1 << 1,
		  MxJustifyHCenter = 1 << 2,

		  MxJustifyVTop = 1 << 3,
		  MxJustifyVBot = 1 << 4,
		  MxJustifyVCenter = 1 << 5
	 } MxStatictextJustify;

	 typedef struct MxStatictext {
		  union {
				MxObject object;
		  } base;

		  /* Justification values */
		  short tx, ty, tw, th;
		  MxStatictextJustify just;
		  int border;

		  const char *caption;
		  unsigned int ownscaption:1;
		  unsigned int justified:1;

	 } MxStatictext;

	 typedef struct MxStatictextArgs {

		  MxObjectArgs object;	  /* Must be first */

		  const char *caption;
		  unsigned int len;
		  unsigned int ownscaption;

		  MxStatictextJustify just;
		  int border;

	 } MxStatictextArgs;

	 void *MxStatictextHandler(MxObject * object, const MxEvent * const event);

	 void MxStatictextConstruct(MxStatictext * stext, MxObject * parent, int x, int y, int w, int h, MxStatictextArgs * args);

	 MxStatictext *MxStatictextNew(MxObject * parent, int x, int y, int w, int h, MxStatictextArgs * args);

	 void MxStatictextSet(MxStatictext * stext, const char *caption, unsigned int owns);

	 int MxStatictextPixel(const MxStatictext * stext, unsigned int offset);
	 int MxStatictextOffset(const MxStatictext * stext, unsigned int *pixel);

	 void mx_draw_statictext(MxStatictext * stext, int x, int y, int x1, int y1, int x2, int y2, MxColor fore, MxColor back);
	 void mx_statictext_justify(MxStatictext * stext, int x1, int y1, int x2, int y2);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxStatictextArgs > MxpStatictextArgs;

class MxpStatictext:public MxStatictext {
	 public:MxpStatictext(MxObject * parent, int x, int y, int width, int height, MxStatictextArgs * userargs) {
		  MxStatictextConstruct(this, parent, x, y, width, height, userargs);
	 };

	 operator MxObject *() {
		  return &this->base.object;
	 };
	 operator const MxObject *() const {
		  return &this->base.object;
	 };

	 /* Unimplemented functions */
  private:
	 MxpStatictext();
	 MxpStatictext(const MxpStatictext & other);
};

#endif

#endif
