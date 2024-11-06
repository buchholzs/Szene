#ifndef MX_PLATFORM_VTABLE_H
#define MX_PLATFORM_VTABLE_H

#include "depui/config.h"
#include "depui/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxImageVTable {

		  MxImageDestroyFunc Destroy;

		  MxImageAquireFunc Aquire;
		  MxImageReleaseFunc Release;

		  MxImageWidthFunc Width;
		  MxImageHeightFunc Height;
		  MxImageDepthFunc Depth;

		  MxImagePixelFunc Pixel;
		  MxImageGetPixelFunc GetPixel;

		  MxImageHLineFunc HLine;
		  MxImageVLineFunc VLine;

		  MxImageRectFillFunc RectFill;

	 } MxImageVTable;

	 typedef struct MxTransVTable {

		  MxImagePixelTransFunc Pixel;

	 } MxTransVTable;

#ifdef __cplusplus
}
#endif
#endif
