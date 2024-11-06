#include "depui.h"
#include "depui/graphics/clip.h"
#include "depui/draw/region.h"

/* main function */
int MxMain(int argc, char *argv[])
{
	 int i = 0;
	 struct MxImage *image;

	 MxRect rect;
	 MxRegion clip;

	 MxPlatform driver = MxDriverDefault;

	 if (!MxInit(&driver, 800, 600, 16))
		  return 1;

	 image = MxImageLoad("hand.pcx");
	 if (!image)
		  return 1;

	 MxImageVLine(image, 0, 0, 100, MxColorLight);
	 MxImageHLine(image, 0, 0, 100, MxColorLight);
	 MxImageVLine(image, 99, 0, 99, MxColorDark);
	 MxImageHLine(image, 0, 99, 99, MxColorDark);

	 rect.x1 = 0;
	 rect.y1 = 0;
	 rect.x2 = MxScreenWidth(0);
	 rect.y2 = MxScreenHeight(0);

	 MxRegionConstruct(&clip);
	 MxRegionAddRect(&clip, &rect);

	 MxRegionCopyConstruct(&mx_region, &clip);
	 MxRegionDestruct(&clip);

	 for (i = 0; i < 1000; i++) {
		  MxBlitToScreen(image, 0, 0, 0, rand() % 50, rand() % 50, MxImageWidth(image), MxImageHeight(image));

//      rest(100);
//      delay(100);
	 }

	 MxImageDestroy(image);
	 MxRegionDestruct(&mx_region);

	 MxExit();
	 return 0;
}
