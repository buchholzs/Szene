#include "depui/config.h"
#ifdef MX_IMAGE_LOAD_BMP

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

#define BI_RGB          0
#define BI_RLE8         1
#define BI_RLE4         2
#define BI_BITFIELDS    3

#define OS2INFOHEADERSIZE  12
#define WININFOHEADERSIZE  40

typedef struct BITMAPFILEHEADER {
	 UInt32 bfType;
	 UInt32 bfSize;
	 UInt16 bfReserved1;
	 UInt16 bfReserved2;
	 UInt32 bfOffBits;
} BITMAPFILEHEADER;

/*
 * Used for both OS/2 and Windows BMP. * Contains only the parameters needed 
 * to load the image 
 */
typedef struct BITMAPINFOHEADER {
	 UInt32 biWidth;
	 UInt32 biHeight;
	 UInt16 biBitCount;
	 UInt32 biCompression;
} BITMAPINFOHEADER;

typedef struct WINBMPINFOHEADER {	/* 
												   * size: 40 */
	 UInt32 biWidth;
	 UInt32 biHeight;
	 UInt16 biPlanes;
	 UInt16 biBitCount;
	 UInt32 biCompression;
	 UInt32 biSizeImage;
	 UInt32 biXPelsPerMeter;
	 UInt32 biYPelsPerMeter;
	 UInt32 biClrUsed;
	 UInt32 biClrImportant;
} WINBMPINFOHEADER;

typedef struct OS2BMPINFOHEADER {	/* 
												   * size: 12 */
	 UInt16 biWidth;
	 UInt16 biHeight;
	 UInt16 biPlanes;
	 UInt16 biBitCount;
} OS2BMPINFOHEADER;

/*
 * read_bmfileheader: *  Reads a BMP file header and check that it has the
 * BMP magic number. 
 */
static int read_bmfileheader(FILE * f, BITMAPFILEHEADER * fileheader)
{
	 fileheader->bfType = mx_igetw(f);
	 fileheader->bfSize = mx_igetl(f);
	 fileheader->bfReserved1 = mx_igetw(f);
	 fileheader->bfReserved2 = mx_igetw(f);
	 fileheader->bfOffBits = mx_igetl(f);

	 if (fileheader->bfType != 19778)
		  return -1;

	 return 0;
}

/*
 * read_win_bminfoheader: *  Reads information from a BMP file header. 
 */
static int read_win_bminfoheader(FILE * f, BITMAPINFOHEADER * infoheader)
{
	 WINBMPINFOHEADER win_infoheader;

	 win_infoheader.biWidth = mx_igetl(f);
	 win_infoheader.biHeight = mx_igetl(f);
	 win_infoheader.biPlanes = mx_igetw(f);
	 win_infoheader.biBitCount = mx_igetw(f);
	 win_infoheader.biCompression = mx_igetl(f);
	 win_infoheader.biSizeImage = mx_igetl(f);
	 win_infoheader.biXPelsPerMeter = mx_igetl(f);
	 win_infoheader.biYPelsPerMeter = mx_igetl(f);
	 win_infoheader.biClrUsed = mx_igetl(f);
	 win_infoheader.biClrImportant = mx_igetl(f);

	 infoheader->biWidth = win_infoheader.biWidth;
	 infoheader->biHeight = win_infoheader.biHeight;
	 infoheader->biBitCount = win_infoheader.biBitCount;
	 infoheader->biCompression = win_infoheader.biCompression;

	 return 0;
}

/*
 * read_os2_bminfoheader: *  Reads information from an OS/2 format BMP file
 * header. 
 */
static int read_os2_bminfoheader(FILE * f, BITMAPINFOHEADER * infoheader)
{
	 OS2BMPINFOHEADER os2_infoheader;

	 os2_infoheader.biWidth = mx_igetw(f);
	 os2_infoheader.biHeight = mx_igetw(f);
	 os2_infoheader.biPlanes = mx_igetw(f);
	 os2_infoheader.biBitCount = mx_igetw(f);

	 infoheader->biWidth = os2_infoheader.biWidth;
	 infoheader->biHeight = os2_infoheader.biHeight;
	 infoheader->biBitCount = os2_infoheader.biBitCount;
	 infoheader->biCompression = 0;

	 return 0;
}

/*
 * read_bmicolors: *  Loads the color palette for 1,4,8 bit formats. 
 */
static void read_bmicolors(int ncols, rgb * pal, FILE * f, int win_flag)
{
	 int i;

	 for (i = 0; i < ncols; i++) {
		  pal[i].b = getc(f);
		  pal[i].g = getc(f);
		  pal[i].r = getc(f);

		  if (win_flag)
				getc(f);
	 }
}

/*
 * read_1bit_line: *  Support function for reading the 1 bit bitmap file
 * format. 
 */
static void read_1bit_line(int length, FILE * f, MxImage * bmp, int line)
{
	 unsigned char b[32];
	 UInt32 n;
	 int i, j, k;
	 int pix;

	 for (i = 0; i < length; i++) {

		  j = i % 32;
		  if (j == 0) {
				n = mx_mgetl(f);

				for (k = 0; k < 32; k++) {
					 b[31 - k] = (char) (n & 1);
					 n = n >> 1;
				}
		  }
		  pix = b[j];

		  bmp->vtable->Pixel(bmp, i, line, pix);
		  // bmp->line[line][i] = pix;
	 }
}

/*
 * read_4bit_line: *  Support function for reading the 4 bit bitmap file
 * format. 
 */
static void read_4bit_line(int length, FILE * f, MxImage * bmp, int line, rgb * pal, MxColorFunc makecol)
{
	 unsigned char b[8];
	 UInt32 n;
	 int i, j, k;
	 int temp;
	 int pix;

	 for (i = 0; i < length; i++) {
		  j = i % 8;
		  if (j == 0) {
				n = mx_igetl(f);
				for (k = 0; k < 4; k++) {
					 temp = n & 255;
					 b[k * 2 + 1] = temp & 15;
					 temp = temp >> 4;
					 b[k * 2] = temp & 15;
					 n = n >> 8;
				}
		  }
		  pix = b[j];

		  bmp->vtable->Pixel(bmp, i, line, makecol(pal[pix].r, pal[pix].g, pal[pix].b));
		  // bmp->line[line][i] = pix;
	 }
}

/*
 * read_8bit_line: *  Support function for reading the 8 bit bitmap file
 * format. 
 */
static void read_8bit_line(int length, FILE * f, MxImage * bmp, int line, rgb * pal, MxColorFunc makecol)
{
	 unsigned char b[4];
	 UInt32 n;
	 int i, j, k;
	 int pix;

	 for (i = 0; i < length; i++) {
		  j = i % 4;
		  if (j == 0) {
				n = mx_igetl(f);
				for (k = 0; k < 4; k++) {
					 b[k] = (char) (n & 255);
					 n = n >> 8;
				}
		  }
		  pix = b[j];
		  bmp->vtable->Pixel(bmp, i, line, makecol(pal[pix].r, pal[pix].g, pal[pix].b));
		  // bmp->line[line][i] = pix;
	 }
}

/*
 * read_24bit_line: *  Support function for reading the 24 bit bitmap file
 * format, doing *  our best to convert it down to a 256 color palette. 
 */
static void read_24bit_line(int length, FILE * f, MxImage * bmp, int line, MxColorFunc makecol)
{
	 int i, nbytes;
	 rgb c;

	 nbytes = 0;

	 for (i = 0; i < length; i++) {
		  c.b = getc(f);
		  c.g = getc(f);
		  c.r = getc(f);
		  bmp->vtable->Pixel(bmp, i, line, makecol(c.r, c.g, c.b));
		  // bmp->line[line][i*3+_rgb_r_shift_24/8] = c.r;
		  // bmp->line[line][i*3+_rgb_g_shift_24/8] = c.g;
		  // bmp->line[line][i*3+_rgb_b_shift_24/8] = c.b;
		  nbytes += 3;
	 }

	 nbytes = nbytes % 4;
	 if (nbytes != 0)
		  for (i = nbytes; i < 4; i++)
				getc(f);
}

/*
 * read_image: *  For reading the noncompressed BMP image format. 
 */
static void read_image(FILE * f, MxImage * bmp, BITMAPINFOHEADER * infoheader, rgb * pal, MxColorFunc makecol)
{
	 int i, line;

	 for (i = 0; i < (int) infoheader->biHeight; i++) {
		  line = i;

		  switch (infoheader->biBitCount) {

		  case 1:
				read_1bit_line(infoheader->biWidth, f, bmp, infoheader->biHeight - i - 1);
				break;

		  case 4:
				read_4bit_line(infoheader->biWidth, f, bmp, infoheader->biHeight - i - 1, pal, makecol);
				break;

		  case 8:
				read_8bit_line(infoheader->biWidth, f, bmp, infoheader->biHeight - i - 1, pal, makecol);
				break;

		  case 24:
				read_24bit_line(infoheader->biWidth, f, bmp, infoheader->biHeight - i - 1, makecol);
				break;
		  }
	 }
}

/*
 * read_RLE8_compressed_image: *  For reading the 8 bit RLE compressed BMP
 * image format. 
 */
static void read_RLE8_compressed_image(FILE * f, MxImage * bmp, BITMAPINFOHEADER * infoheader, rgb * pal, MxColorFunc makecol)
{
	 unsigned char count, val, val0;
	 int j, pos, line;
	 int eolflag, eopicflag;

	 eopicflag = 0;
	 line = infoheader->biHeight - 1;

	 while (eopicflag == 0) {
		  pos = 0;					  /* 
										     * x position in bitmap */
		  eolflag = 0;				  /* 
										     * end of line flag */

		  while ((eolflag == 0) && (eopicflag == 0)) {
				count = getc(f);
				val = getc(f);

				if (count > 0) {	  /* 
										     * repeat pixel count times */
					 for (j = 0; j < count; j++) {
						  bmp->vtable->Pixel(bmp, pos, line, makecol(pal[val].r, pal[val].g, pal[val].b));
						  // bmp->line[line][pos] = val;
						  pos++;
					 }
				} else {

					 switch (val) {
					 case 0:		  /* 
										     * end of line flag */
						  eolflag = 1;
						  break;

					 case 1:		  /* 
										     * end of picture flag */
						  eopicflag = 1;
						  break;

					 case 2:		  /* 
										     * displace picture */
						  count = getc(f);
						  val = getc(f);
						  pos += count;
						  line -= val;
						  break;

					 default:		  /* 
										     * read in absolute mode */
						  for (j = 0; j < val; j++) {
								val0 = getc(f);
								bmp->vtable->Pixel(bmp, pos, line, makecol(pal[val0].r, pal[val0].g, pal[val0].b));
								// bmp->line[line][pos] = val0;
								pos++;
						  }

						  if (j % 2 == 1)
								val0 = getc(f);	/* 
														   * align on word boundary */
						  break;
					 }
				}

				if (pos - 1 > (int) infoheader->biWidth)
					 eolflag = 1;
		  }
		  line--;
		  if (line < 0)
				eopicflag = 1;
	 }
}

/*
 * read_RLE4_compressed_image: *  For reading the 4 bit RLE compressed BMP
 * image format. 
 */
static void read_RLE4_compressed_image(FILE * f, MxImage * bmp, BITMAPINFOHEADER * infoheader, rgb * pal, MxColorFunc makecol)
{
	 unsigned char b[8];
	 unsigned char count;
	 UInt16 val0, val;
	 int j, k, pos, line;
	 int eolflag, eopicflag;

	 eopicflag = 0;				  /* 
										     * end of picture flag */
	 line = infoheader->biHeight - 1;

	 while (eopicflag == 0) {
		  pos = 0;
		  eolflag = 0;				  /* 
										     * end of line flag */

		  while ((eolflag == 0) && (eopicflag == 0)) {
				count = getc(f);
				val = getc(f);

				if (count > 0) {	  /* 
										     * repeat pixels count times */
					 b[1] = val & 15;
					 b[0] = (val >> 4) & 15;
					 for (j = 0; j < count; j++) {
						  bmp->vtable->Pixel(bmp, pos, line, makecol(pal[b[j % 2]].r, pal[b[j % 2]].g, pal[b[j % 2]].b));
						  // bmp->line[line][pos] = b[j%2];
						  pos++;
					 }
				} else {
					 switch (val) {

					 case 0:		  /* 
										     * end of line */
						  eolflag = 1;
						  break;

					 case 1:		  /* 
										     * end of picture */
						  eopicflag = 1;
						  break;

					 case 2:		  /* 
										     * displace image */
						  count = getc(f);
						  val = getc(f);
						  pos += count;
						  line -= val;
						  break;

					 default:		  /* 
										     * read in absolute mode */
						  for (j = 0; j < val; j++) {
								if ((j % 4) == 0) {
									 val0 = mx_igetw(f);
									 for (k = 0; k < 2; k++) {
										  b[2 * k + 1] = val0 & 15;
										  val0 = val0 >> 4;
										  b[2 * k] = val0 & 15;
										  val0 = val0 >> 4;
									 }
								}
								bmp->vtable->Pixel(bmp, pos, line, makecol(pal[b[j % 4]].r, pal[b[j % 4]].g, pal[b[j % 4]].b));
								// bmp->line[line][pos] = b[j%4];
								pos++;
						  }
						  break;
					 }
				}

				if (pos - 1 > (int) infoheader->biWidth)
					 eolflag = 1;
		  }

		  line--;
		  if (line < 0)
				eopicflag = 1;
	 }
}

/*
 * load_bmp: *  Loads a Windows BMP file, returning a bitmap structure and
 * storing *  the palette data in the specified palette (this should be an
 * array of *  at least 256 RGB structures). * *  Thanks to Seymour Shlien
 * for contributing this function. 
 */
MxImage *Mx_ImageLoadBMP(const char *filename, int bits, MxColorFunc makecol)
{
	 BITMAPFILEHEADER fileheader;
	 BITMAPINFOHEADER infoheader;
	 FILE *f;
	 MxImage *bmp;
	 rgb pal[256];
	 int ncol;
	 UInt32 biSize;
	 int bpp, dest_depth;

	 f = fopen(filename, "r");
	 if (!f)
		  return NULL;

	 if (read_bmfileheader(f, &fileheader) != 0) {
		  fclose(f);
		  return NULL;
	 }

	 biSize = mx_igetl(f);

	 if (biSize == WININFOHEADERSIZE) {
		  if (read_win_bminfoheader(f, &infoheader) != 0) {
				fclose(f);
				return NULL;
		  }
		  /* 
		   * compute number of colors recorded 
		   */
		  ncol = (fileheader.bfOffBits - 54) / 4;
		  read_bmicolors(ncol, pal, f, 1);
	 } else if (biSize == OS2INFOHEADERSIZE) {
		  if (read_os2_bminfoheader(f, &infoheader) != 0) {
				fclose(f);
				return NULL;
		  }
		  /* 
		   * compute number of colors recorded 
		   */
		  ncol = (fileheader.bfOffBits - 26) / 3;
		  read_bmicolors(ncol, pal, f, 0);
	 } else {
		  fclose(f);
		  return NULL;
	 }

	 if (infoheader.biBitCount == 24)
		  bpp = 24;
	 else
		  bpp = 8;

	 dest_depth = bits;

	 bmp = Mx_ImageCreateDepth(infoheader.biWidth, infoheader.biHeight, dest_depth);
	 if (!bmp) {
		  fclose(f);
		  return 0;
	 }
	 // clear(bmp);

	 switch (infoheader.biCompression) {

	 case BI_RGB:
		  read_image(f, bmp, &infoheader, pal, makecol);
		  break;

	 case BI_RLE8:
		  read_RLE8_compressed_image(f, bmp, &infoheader, pal, makecol);
		  break;

	 case BI_RLE4:
		  read_RLE4_compressed_image(f, bmp, &infoheader, pal, makecol);
		  break;

	 default:
		  Mx_ImageDestroy(bmp);
		  bmp = 0;
	 }

	 fclose(f);
	 return bmp;
}

#else
extern int mx_ignore_this;

#endif
