#include "depui.h"
#include <stdio.h>

/* main function */
int MxMain(int argc, char *argv[])
{
	 int x, y;
	 int w = 3, h = 3;

	 MxImage *image = Mx_ImageCreate16(w, h);

	 for (y = 0; y <= h; y++) {
		  for (x = 0; x <= w; x++) {

				MxImagePixel(image, x, y, x * y);
		  }
	 }

	 for (y = 0; y <= h; y++) {
		  for (x = 0; x <= w; x++) {

				printf("%i  ", MxImageGetPixel(image, x, y));
		  }
		  printf("\n");
	 }

	 MxImageDestroy(image);

	 return 0;
}
