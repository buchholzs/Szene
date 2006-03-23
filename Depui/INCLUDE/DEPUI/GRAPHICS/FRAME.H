#ifndef MX_GRAPHICS_FRAME_H
#define MX_GRAPHICS_FRAME_H

#include "depui/config.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef void (*MxFrameFunc) (int *x1, int *y1, int *x2, int *y2, int effect);

	 void MxFrameRaised(int *x1, int *y1, int *x2, int *y2, int effect);
	 void MxFrameGroove(int *x1, int *y1, int *x2, int *y2, int effect);

	 /* Basic frame drawing functions */

	 void MxFrameEmpty(int x1, int y1, int x2, int y2, int width, MxColor light_color, MxColor dark_color);

	 void MxFrameFilled(int x1, int y1, int x2, int y2, int width, MxColor light_color, MxColor dark_color, MxColor fill_color);

	 void MxFrameButton(int x1, int y1, int x2, int y2, unsigned int pressed, unsigned int focus, const char *text,
							  MxColor outsize_color1, MxColor outside_color2);

#ifdef __cplusplus
}
#endif
#endif
