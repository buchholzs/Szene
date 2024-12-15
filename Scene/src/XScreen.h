// Copyright (c) 2024, Steffen Buchholz

#ifndef _ScreenResolution_H_
#define _ScreenResolution_H_

#ifdef __cplusplus
extern "C" {
#endif

namespace scene {

void ScreenResolution(int *width, int *height);
bool FullScreen(bool fullscreen);

} // scene
#ifdef __cplusplus
}
#endif
#endif
