#ifndef MX_PLATFORM_SUPPORT_MOUSE_H
#define MX_PLATFORM_SUPPORT_MOUSE_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 void Mx_MouseShow(int show, MxImagePixelFunc pixel, MxImageGetPixelFunc getpixel);

	 void Mx_MouseMove(int x, int y, MxImagePixelFunc pixel, MxImageGetPixelFunc getpixel);

#ifdef __cplusplus
}
#endif
#endif
