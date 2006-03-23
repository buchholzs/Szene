#ifndef MX_GRAPHICS_DECORATE_H
#define MX_GRAPHICS_DECORATE_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxDecoration {

		  int width;
		  int height;
		  unsigned char data[1];

	 } MxDecoration;

	 typedef struct MxDecoration_6_6 {

		  int width;
		  int height;
		  unsigned char data[6 * 6];

	 } MxDecoration_6_6;

	 typedef struct MxDecoration_7_7 {

		  int width;
		  int height;
		  unsigned char data[7 * 7];

	 } MxDecoration_7_7;

	 typedef struct MxDecoration_9_9 {

		  int width;
		  int height;
		  unsigned char data[9 * 9];

	 } MxDecoration_9_9;

/* A close decoration for a windows */
	 extern MxDecoration_7_7 Mx_DecorationClose;
#define MxDecorationClose ((MxDecoration*)&Mx_DecorationClose)

/* Decoration for a checkbox */
	 extern MxDecoration_9_9 Mx_DecorationCheckon;
	 extern MxDecoration_9_9 Mx_DecorationCheckoff;
#define MxDecorationCheckon  ((MxDecoration*)&Mx_DecorationCheckon)
#define MxDecorationCheckoff ((MxDecoration*)&Mx_DecorationCheckoff)

/* Decoration for a radiobutton */
	 extern MxDecoration_9_9 Mx_DecorationRadioon;
	 extern MxDecoration_9_9 Mx_DecorationRadiooff;
#define MxDecorationRadioon  ((MxDecoration*)&Mx_DecorationRadioon)
#define MxDecorationRadiooff ((MxDecoration*)&Mx_DecorationRadiooff)

/* Decoration for resizing */
	 extern MxDecoration_6_6 Mx_DecorationResize;
#define MxDecorationResize ((MxDecoration*)&Mx_DecorationResize)

/* Access to the generic decoration drawing routine */
	 void Mx_Decorate(const MxDecoration * decoration, int x, int y, struct MxImage *image, MxImagePixelFunc pixel);

#ifdef __cplusplus
}
#endif
#endif
