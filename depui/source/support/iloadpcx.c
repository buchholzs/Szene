#include "depui/config.h"
#ifdef MX_IMAGE_LOAD_PCX

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/debug/alloc.h"
#include "depui/platform/support/image.h"

typedef struct rgb {
	 unsigned char r;
	 unsigned char g;
	 unsigned char b;
} rgb;

MxImage *Mx_ImageLoadPCX(const char *filename, int bits, MxColorFunc makecol)
{
	 MxImage *b;
	 rgb pal[256];
	 int y, c;
	 int width, height;
	 int bpp, bytes_per_line, stride;
	 unsigned char *data;
	 MxImagePixelFunc pixel;

	 FILE *f = fopen(filename, "rb");

	 if (!f)
		  return 0;

	 getc(f);						  /* skip manufacturer ID */
	 getc(f);						  /* skip version flag */
	 getc(f);						  /* skip encoding flag */

	 if (getc(f) != 8) {			  /* we like 8 bit color planes */
		  fclose(f);
		  return 0;
	 }

	 width = -(mx_igetw(f));	  /* xmin */
	 height = -(mx_igetw(f));	  /* ymin */
	 width += mx_igetw(f) + 1;	  /* xmax */
	 height += mx_igetw(f) + 1;  /* ymax */

	 mx_igetl(f);					  /* skip DPI values */

	 for (c = 0; c < 16; c++) {  /* read the 16 color palette */
		  pal[c].r = getc(f);
		  pal[c].g = getc(f);
		  pal[c].b = getc(f);
	 }

	 getc(f);

	 bpp = getc(f) * 8;			  /* how many color planes? */
	 if ((bpp != 8) && (bpp != 24)) {
		  fclose(f);
		  return 0;
	 }

	 bytes_per_line = mx_igetw(f);
	 stride = bytes_per_line * bpp / 8;

	 for (c = 0; c < 60; c++)	  /* skip some more junk */
		  getc(f);

	 b = Mx_ImageCreateDepth(width, height, bits);
	 pixel = b->vtable->Pixel;

	 if (!b) {
		  fclose(f);
		  return 0;
	 }

	 /* Allocate some memory to hold one line in it */
	 data = (unsigned char *) MXMALLOC(stride * height);
	 if (!data) {
		  fclose(f);
		  return 0;
	 }

	 for (y = 0; y < height; y++) {	/* read RLE encoded PCX data */
		  int x = 0, xx = 0, po = 2;

		  while (x < stride) {
				char ch = getc(f);

				if ((ch & 0xC0) == 0xC0) {
					 c = (ch & 0x3F);
					 ch = getc(f);

				} else
					 c = 1;

				if (bpp == 8) {
					 while (c--) {
						  if (x < b->w)
								data[y * stride + x] = ch;
						  x++;
					 }

				} else {
					 while (c--) {

						  if (xx < b->w)
								data[y * stride + xx * 3 + po] = ch;
						  x++;

						  if (x == bytes_per_line) {
								xx = 0;
								po = 1;
						  }

						  else if (x == bytes_per_line * 2) {
								xx = 0;
								po = 0;

						  } else
								xx++;
					 }
				}
		  }
	 }

	 if (bpp == 8) {				  /* look for a 256 color palette */
		  while (!feof(f)) {
				if (getc(f) == 12) {
					 for (c = 0; c < 256; c++) {
						  pal[c].r = getc(f);
						  pal[c].g = getc(f);
						  pal[c].b = getc(f);
					 }
					 break;
				}
		  }
	 }

	 /* Convert the raw data into the right colors */
	 for (y = 0; y < height; y++) {
		  int x;
		  const int yoff = y * stride;

		  if (bpp == 8) {
				for (x = 0; x < width; x++) {
					 c = data[yoff + x];
					 pixel(b, x, y, makecol(pal[c].r, pal[c].g, pal[c].b));
				}

		  } else {
				for (x = 0; x < width; x++) {
					 const int offset = yoff + x * 3;

					 pixel(b, x, y, makecol(data[offset], data[offset + 1], data[offset + 2]));
				}
		  }
	 }

	 MXFREE(data);
	 fclose(f);
	 return b;
}

#else
extern int mx_ignore_this;

#endif
