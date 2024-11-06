#ifndef MX_DESKTOP_DRIVER_H
#define MX_DESKTOP_DRIVER_H

#include "depui/config.h"
#include "depui/platform/platform.h"

#ifdef __cplusplus
extern "C" {
#endif
	 extern MxDriverSystem *mx_system;
	 extern MxDriverOutput *mx_output;
	 extern MxDriverInput *mx_input;

/* Some helpful defines to help users call platform functions */
#define MxColorFore           (mx_output->colors[MxForeIndex])
#define MxColorBack           (mx_output->colors[MxBackIndex])
#define MxColorObjectFore     (mx_output->colors[MxObjectForeIndex])
#define MxColorObjectBack     (mx_output->colors[MxObjectBackIndex])
#define MxColorSelectedFore   (mx_output->colors[MxSelectedForeIndex])
#define MxColorSelectedBack   (mx_output->colors[MxSelectedBackIndex])
#define MxColorLight          (mx_output->colors[MxLightIndex])
#define MxColorMed            (mx_output->colors[MxMedIndex])
#define MxColorDark           (mx_output->colors[MxDarkIndex])
#define MxColorDesktop        (mx_output->colors[MxDesktopIndex])
#define MxColorFocus          (mx_output->colors[MxFocusIndex])
#define MxColorDisabled       (mx_output->colors[MxDisabledIndex])

#define MxColorBlend          (mx_output->ColorBlend)
#define MxColorEncode         (mx_output->ColorEncode)

#define MxImageCreate         (mx_output->ImageCreate)
#define MxImageLoad           (mx_output->ImageLoad)
#define MxImageDestroy        (mx_output->image_vtable.Destroy)

#define MxImageAquire         (mx_output->image_vtable.Aquire)
#define MxImageRelease        (mx_output->image_vtable.Release)

#define MxImageWidth          (mx_output->image_vtable.Width)
#define MxImageHeight         (mx_output->image_vtable.Height)
#define MxImageDepth          (mx_output->image_vtable.Depth)

#define MxImagePixelFast      (mx_output->image_vtable.Pixel)
#define MxImageGetPixelFast   (mx_output->image_vtable.GetPixel)

#define MxImageVLineFast      (mx_output->image_vtable.VLine)
#define MxImageHLineFast      (mx_output->image_vtable.HLine)

#define MxImageRectFillFast   (mx_output->image_vtable.RectFill)

#define MxImagePixelTransFast (mx_output->image_trans_vtable.Pixel)

#define MxBlitFast            (mx_output->Blit)
#define MxBlitToScreenFast    (mx_output->BlitToScreen)
#define MxBlitFromScreenFast  (mx_output->BlitFromScreen)
#define MxBlitScreenFast      (mx_output->BlitScreen)

#define MxDecorate            (mx_output->Decorate)

#define MxScreenWidth         (mx_output->screen_vtable.Width)
#define MxScreenHeight        (mx_output->screen_vtable.Height)
#define MxScreenDepth         (mx_output->screen_vtable.Depth)

/* Region clipped drawing functions */
#define MxScreenPixel         (mx_output->screen_vtable.Pixel)
#define MxScreenGetPixel      (mx_output->screen_vtable.GetPixel)

#define MxScreenVLine         (mx_output->screen_vtable.VLine)
#define MxScreenHLine         (mx_output->screen_vtable.HLine)
#define MxScreenLine          (mx_output->screen_vtable.Line)

#define MxScreenRectFill      (mx_output->screen_vtable.RectFill)

#define MxScreenPixelTrans    (mx_output->screen_trans_vtable.Pixel)

/* Non clipped drawing functions */
#define MxScreenPixelFast     (mx_output->screen_fast_vtable.Pixel)
#define MxScreenGetPixelFast  (mx_output->screen_fast_vtable.GetPixel)

#define MxScreenVLineFast     (mx_output->screen_fast_vtable.VLine)
#define MxScreenHLineFast     (mx_output->screen_fast_vtable.HLine)
#define MxScreenLineFast      (mx_output->screen_fast_vtable.Line)

#define MxScreenRectFillFast  (mx_output->screen_fast_vtable.RectFill)

#define MxScreenPixelTransFast (mx_output->screen_fast_trans_vtable.Pixel)

#define MxFontDefault         (mx_output->font)

#define MxFontLoad            (mx_output->FontLoad)
#define MxFontDestroy         (mx_output->FontDestroy)

#define MxFontScreenRender    (mx_output->FontScreenRender)
#define MxFontImageRender     (mx_output->FontImageRender)
#define MxFontLength          (mx_output->FontLength)
#define MxFontHeight          (mx_output->FontHeight)

#ifdef __cplusplus
}
#endif
#endif
