#ifndef MX_PLATFORM_SUPPORT_FONT_H
#define MX_PLATFORM_SUPPORT_FONT_H

#include "depui/config.h"
#include "depui/types.h"
#include "depui/platform/vtable.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef MX_NEED_FONT
	 typedef struct MxFontIndex {

		  unsigned int start;	  /* Character number to start with */
		  unsigned int index[128];	/* Indicies in data of each character */

	 } MxFontIndex;

	 typedef struct MxFont {

		  unsigned int height;
		  unsigned int size;		  /* Size of extra font data allocated (bytes) */
		  unsigned int sections;  /* Number of index section in the font */

		  MxFontFlag flags;
		  unsigned int allocated:1;

	 } MxFont;

#define MXFONTDEFINE(numsec, datasize)     \
typedef struct MxFont_numsec_datasize)  {  \
   MxFont        base;                     \
	MxFontIndex   index[numsec];            \
   unsigned char data[datasize];           \
} MxFont_numsec_datasize

/* A default font for all purposes */
	 typedef struct MxFont_1_864 {
		  MxFont base;
		  MxFontIndex index[1];
		  unsigned char data[864];
	 } MxFont_1_864;

	 typedef struct MxFont_1_1632 {
		  MxFont base;
		  MxFontIndex index[1];
		  unsigned char data[1632];
	 } MxFont_1_1632;

	 typedef struct MxFont_1_672 {
		  MxFont base;
		  MxFontIndex index[1];
		  unsigned char data[672];
	 } MxFont_1_672;

	 typedef struct MxFont_1_9441 {
		  MxFont base;
		  MxFontIndex index[1];
		  unsigned char data[9441];
	 } MxFont_1_9441;

	 typedef struct MxFont_1_9936 {
		  MxFont base;
		  MxFontIndex index[1];
		  unsigned char data[9936];
	 } MxFont_1_9936;

	 extern const MxFont_1_864 Mx_FontBuiltin;
	 extern const MxFont_1_864 Mx_FontBuiltin8x8;
	 extern const MxFont_1_1632 Mx_FontBuiltin8x16;
	 extern const MxFont_1_9441 Mx_FontBuiltinArial;
	 extern const MxFont_1_9936 Mx_FontBuiltinTimes;

#define MxFontBuiltin         (&Mx_FontBuiltin.base)
#define MxFontBuiltin8x8      (&Mx_FontBuiltin8x8.base)
#define MxFontBuiltin8x16     (&Mx_FontBuiltin8x16.base)
#define MxFontBuiltinArial    (&Mx_FontBuiltinArial.base)
#define MxFontBuiltinTimes    (&Mx_FontBuiltinTimes.base)

	 MxFont *Mx_FontCreate(unsigned int height, MxFontFlag flags);
	 void Mx_FontDestroy(MxFont * font);

	 unsigned int Mx_FontLength(const struct MxFont *font, const char *text);
	 unsigned int Mx_FontHeight(const struct MxFont *font);

	 void Mx_FontDump(const MxFont * font, FILE * stream, const char *name, const char *render);

/* Font rendering functions */
	 void Mx_FontTextPixmapRender(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
											MxColor back, const MxRect * const clip, MxImagePixelFunc pixel);
	 void Mx_FontTextAntialiasedRender(struct MxImage *image, const char *text, const struct MxFont *font, int x, int y, MxColor color,
												  MxColor back, MxBlendFunc blend, const MxRect * const clip, MxImagePixelFunc pixel,
												  MxImagePixelTransFunc trans);

/* Private functions */
	 const MxFontIndex *mx_font_range(const MxFont * font, const unsigned int c);
	 unsigned int mx_font_set_char(MxFont ** font, const unsigned int index, const unsigned char *data, unsigned int size);
	 void mx_font_dump(const MxFont * font, FILE * stream, const char *name);

#endif

#ifdef __cplusplus
}
#endif
#endif
