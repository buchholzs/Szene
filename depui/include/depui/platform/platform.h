#ifndef MX_PLATFORM_PLATFORM_H
#define MX_PLATFORM_PLATFORM_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/platform/vtable.h"

#ifdef __cplusplus
extern "C" {
#endif
	 struct MxFont;
	 struct MxImage;
	 struct MxPlatform;
	 struct MxDecoration;

	 typedef enum MxKey {
		  MxKeyNone = 0,

		  MxKeyUp,
		  MxKeyDown,
		  MxKeyLeft,
		  MxKeyRight,

		  MxKeyInsert,
		  MxKeyDelete,
		  MxKeyPagedown,
		  MxKeyPageup,
		  MxKeyHome,
		  MxKeyEnd,

		  KeyLast = 0xffff
	 } MxKey;

	 typedef enum MxColorIndex {
		  MxForeIndex = 0,
		  MxBackIndex,
		  MxObjectForeIndex,
		  MxObjectBackIndex,

		  MxSelectedForeIndex,
		  MxSelectedBackIndex,
		  MxLightIndex,
		  MxMedIndex,

		  MxDarkIndex,
		  MxFocusIndex,
		  MxDisabledIndex,
		  MxDesktopIndex
	 } MxColorIndex;

	 typedef struct MxDriverOutput {

		  /* Initialization related functions */
		  int (*Init) (struct MxDriverOutput * driver, int x, int y, int c, const char *title);
		  void (*Exit) (void);
		  void (*Flush) (void);

		  void (*MouseShow) (const int show);

		  /* Basic color handling */
		  MxColor colors[12];
		   MxColor(*ColorBlend) (MxColor one, MxColor two, unsigned int blend);
		   MxColor(*ColorEncode) (int cindex, int r, int g, int b);

		  /* Screen related functions */
		  void (*DrawingArea) (int x1, int y1, int x2, int y2);
		  void (*DoneDrawingArea) (void);
		  void (*Region) (const struct MxRegion * const region);
		  MxImageVTable screen_vtable;
		  MxTransVTable screen_trans_vtable;
		  MxImageVTable screen_fast_vtable;
		  MxTransVTable screen_fast_trans_vtable;

		  /* Image related functions */
		  struct MxImage *(*ImageCreate) (int w, int h);
		  struct MxImage *(*ImageLoad) (const char *filename);
		  MxImageVTable image_vtable;
		  MxTransVTable image_trans_vtable;

		  /* Blitting functions */
		  void (*Blit) (struct MxImage * src, struct MxImage * dest, int sx, int sy, int dx, int dy, int w, int h);
		  void (*BlitToScreen) (struct MxImage * src, struct MxImage * dest, int sx, int sy, int dx, int dy, int w, int h);
		  void (*BlitFromScreen) (struct MxImage * src, struct MxImage * dest, int sx, int sy, int dx, int dy, int w, int h);
		  void (*BlitScreen) (struct MxImage * src, struct MxImage * dest, int sx, int sy, int dx, int dy, int w, int h);

		  /* Decoration functions */
		  void (*Decorate) (const struct MxDecoration * decoration, int x, int y);

		  /* Font related functions */
		  const struct MxFont *font;
		  struct MxFont *(*FontLoad) (const char *name, int points, MxFontFlag flags);
		  void (*FontDestroy) (struct MxFont * image);

		  void (*FontScreenRender) (struct MxImage * image, const char *text, const struct MxFont * f, int x, int y, MxColor color,
											 MxColor back);
		  void (*FontImageRender) (struct MxImage * image, const char *text, const MxRect * const clip, const struct MxFont * f, int x,
											int y, MxColor color, MxColor back);

		  unsigned int (*FontLength) (const struct MxFont * f, const char *text);
		  unsigned int (*FontHeight) (const struct MxFont * f);

	 } MxDriverOutput;

	 typedef struct MxDriverInput {

		  /* Initialization related functions */
		  int (*Init) (void);
		  void (*Exit) (void);

		  /* Keyboard related functions */
		  int (*KeyPressed) (void);
		  void (*ReadKey) (unsigned int *raw, MxKey * key, unsigned int *code);

		  /* Mouse related functions */
		  void (*Mouse) (int *x, int *y, int *b, int *key);

	 } MxDriverInput;

	 typedef struct MxDriverSystem {

		  void (*Yield) (void);

	 } MxDriverSystem;

/* Always include an and buffered drivers.  They will only be linked in
   if they are actually used */
#include "depui/platform/empty.h"
#include "depui/platform/buffdbl.h"

/* Bring in the driver defines */
#if defined(MX_DRIVER_NONE)
#include "depui/platform/none/none.h"

#elif defined(MX_DRIVER_GENERIC)
#include "depui/platform/generic/generic.h"

#elif defined(MX_DRIVER_ALLEGRO)
#include "depui/platform/allegro/allegro.h"

#elif defined(MX_DRIVER_BORLAND_BGI)
#include "depui/platform/borland/bgi/bgi.h"

#elif defined(MX_DRIVER_GRX)
#include "depui/platform/grx/grx.h"

#elif defined(MX_DRIVER_SVGALIB)
#include "depui/platform/svgalib/svgalib.h"

#elif defined(MX_DRIVER_DJVESA2)
#include "depui/platform/djvesa2/djvesa2.h"

#elif defined(MX_DRIVER_DJVESA1)
#include "depui/platform/djvesa1/djvesa1.h"

#elif defined(MX_DRIVER_TINYPTC)
#include "depui/platform/tiny_ptc/tiny_ptc.h"

#elif defined(MX_DRIVER_NANOX)
#include "depui/platform/nanox/nanox.h"

#elif defined(MX_DRIVER_X)
#include "depui/platform/x/x.h"

#elif defined(MX_DRIVER_OPENGUI)
#include "depui/platform/opengui/opengui.h"

#elif defined(MX_DRIVER_VGA)
#include "depui/platform/vga/vga.h"

#elif defined(MX_DRIVER_PORT)
#include "depui/platform/port/port.h"

#endif

#ifdef __cplusplus
}
#endif
#endif
