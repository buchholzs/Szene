#include "depui/debug/alloc.h"
#include "depui/platform/support/font.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <freetype/freetype.h>

#define HEIGHT_RATIO 7/6
#define OFFSET_RATIO 1/3

static TT_Error _Init_TT_Raster_Map(TT_Raster_Map * Bit, const int w, const int h, const int gray_render)
{
	 Bit->rows = h;
	 Bit->width = w;

	 if (gray_render) {
		  Bit->cols = Bit->width;
		  Bit->size = Bit->rows * Bit->width;
	 } else {
		  Bit->cols = (Bit->width + 7) / 8;	/* convert to # of bytes */
		  Bit->size = Bit->rows * Bit->cols;	/* number of bytes in buffer */
	 }

	 Bit->flow = TT_Flow_Up;
	 Bit->bitmap = (void *) malloc(Bit->size);

	 if (!Bit->bitmap)
		  return 1;

	 return 0;
}

/* Convert an ASCII string to a string of glyph indexes.              */
/*                                                                    */
/* IMPORTANT NOTE:                                                    */
/*                                                                    */
/* There is no portable way to convert from any system's char. code   */
/* to Unicode.  This function simply takes a char. string as argument */
/* and "interprets" each character as a Unicode char. index with no   */
/* further check.                                                     */
/*                                                                    */
/* This mapping is only valid for the ASCII character set (i.e.,      */
/* codes 32 to 127); all other codes (like accentuated characters)    */
/* will produce more or less random results, depending on the system  */
/* being run.                                                         */

static long int _code_to_glyph_index(TT_Face_Properties * properties, TT_Face * face, TT_CharMap * char_map, unsigned long source)
{
	 unsigned short i, n;
	 unsigned short platform, encoding;

	 /* First, look for a Unicode charmap */
	 n = properties->num_CharMaps;

	 for (i = 0; i < n; i++) {
		  TT_Get_CharMap_ID(*face, i, &platform, &encoding);
		  if ((platform == 3 && encoding == 1)
				|| (platform == 0 && encoding == 0)) {
				TT_Get_CharMap(*face, i, char_map);
				i = n + 1;
		  }
	 }

	 if (i == n) {
		  perror("Sorry, but this font doesn't contain any Unicode mapping table\n");
		  exit(2);
	 }

	 return TT_Char_Index(*char_map, source);
}

static unsigned int _write_TT_Raster_Map(TT_Raster_Map * Bit, const int gray_render, unsigned int width, unsigned int height,
													  unsigned char **data, unsigned int *len)
{
	 unsigned int count = 1;
	 unsigned int x, y;
	 const unsigned int lastline = (Bit->rows - 1) * Bit->cols;
	 const unsigned char *buffer = Bit->bitmap;

	 (*data)[0] = width;

	 for (y = 0; y < height; y++) {
		  const unsigned int end = gray_render ? width : ((width + 7) / 8);
		  const unsigned char *scanline = &buffer[lastline - y * Bit->cols];

		  /* Put the bytes for this line into the font character data */
		  for (x = 0; x < end; x++) {
				(*data)[count] = scanline[x];
				++count;

				/* Allocate more room if necessary */
				if (count >= *len) {
					 const unsigned int newlen = ((count + 1 + 127) / 128) * 128;

					 *data = (unsigned char *) MXREALLOC(*data, newlen);
					 *len = newlen;
				}
		  }
	 }
	 return count;
}

/* Load a font from a file */
MxFont *Mx_FontLoadTTF(const char *filename, unsigned int points, unsigned int gray_render)
{
	 MxFont *ret = 0;
	 unsigned int i;

	 /* Freetype variables */
	 TT_Error error;
	 TT_Engine engine;
	 TT_Face face;
	 TT_Face_Properties properties;
	 TT_Instance instance;
	 TT_Glyph glyph;
	 TT_Instance_Metrics imetrics;
	 TT_CharMap char_map;
	 TT_Outline outline;
	 TT_Raster_Map Bit;
	 TT_Glyph_Metrics metrics;

//  unsigned char gray_palette[] = { 0,  64, 128, 192, 255 };
	 unsigned char gray_palette[] = { 0, 128, 192, 224, 255 };

	 int font_height, font_width;

	 unsigned int len = 0;
	 unsigned char *data = 0;

	 /* Initialize engine */
	 error = TT_Init_FreeType(&engine);
	 if (error)
		  goto cleanup_data;

	 /* Load face */
	 error = TT_Open_Face(engine, filename, &face);
	 if (error)
		  goto cleanup_engine;

	 /* get face properties */
	 TT_Get_Face_Properties(face, &properties);

	 /* Create glyph */
	 error = TT_New_Glyph(face, &glyph);
	 if (error)
		  goto cleanup_face;

	 /* Create instance */
	 error = TT_New_Instance(face, &instance);
	 if (error)
		  goto cleanup_face;

	 /* Set point sizes */
	 error = TT_Set_Instance_CharSizes(instance, points * 64, points * 64);
	 if (error)
		  goto cleanup_face;

	 TT_Get_Instance_Metrics(instance, &imetrics);

	 /* Allocate the internal raster map */
	 font_height = imetrics.y_ppem * HEIGHT_RATIO;
	 error = _Init_TT_Raster_Map(&Bit, imetrics.x_ppem * 2, font_height, gray_render);
	 if (error)
		  goto cleanup_face;

	 /* Setup the gradient palette */
	 TT_Set_Raster_Gray_Palette(engine, gray_palette);

	 /* Create the font to return */
	 ret = Mx_FontCreate(font_height, gray_render ? MxFontAntialiased : 0);

	 /* Make some memory to write the character data to */
	 len = 128;
	 data = (unsigned char *) MXMALLOC(len);

	 for (i = 32; i < 128; i++) {

		  long int glyphindex = _code_to_glyph_index(&properties, &face, &char_map, i);

		  error = TT_Load_Glyph(instance, glyph, glyphindex, TTLOAD_DEFAULT);

		  if (!error) {
				TT_Get_Glyph_Metrics(glyph, &metrics);
				TT_Get_Glyph_Outline(glyph, &outline);
				TT_Translate_Outline(&outline, -1 * metrics.bearingX, (points * 64) * OFFSET_RATIO);

				/* Set the rendering quality */
				outline.second_pass = 1;
				outline.high_precision = 1;
				outline.dropout_mode = 5;

				/* Blit the character to the raster map */
				memset(Bit.bitmap, 0, Bit.size);
				if (gray_render)
					 TT_Get_Outline_Pixmap(engine, &outline, &Bit);
				else
					 TT_Get_Outline_Bitmap(engine, &outline, &Bit);

				/* Find out the font_width of this character */
				font_width = (metrics.bbox.xMax - metrics.bbox.xMin) / 64 + 1;
				if (font_width < 2)
					 font_width = imetrics.x_ppem / 2;

				/* Get the character data out */
				len = _write_TT_Raster_Map(&Bit, gray_render, font_width, font_height, &data, &len);

				/* Add the character data to the font */
				mx_font_set_char(&ret, i, data, len);
		  }
	 }

	 /* we are done so we can cleanup */
	 if (Bit.bitmap)
		  free(Bit.bitmap);

  cleanup_face:
	 TT_Close_Face(face);

  cleanup_engine:
	 TT_Done_FreeType(engine);

  cleanup_data:
	 if (data)
		  MXFREE(data);

	 return ret;
}

int main(int argc, char *argv[])
{
	 MxFont *font;
	 int points = 10;

	 char fontname[4096];
	 char filename[4096];
	 char *extension;

	 /* Check arguments */
	 if (argc < 2) {
		  printf("TTF to DEPUI font dump utility\n");
		  printf("Usage: ttfdump <ttffile> <points = 10>\n");
		  exit(0);
	 }

	 /* Get the point size */
	 if (argc > 2) {
		  int p = atoi(argv[2]);

		  if (p != 0)
				points = p;
	 }

	 /* Get the filename */
	 strcpy(filename, argv[1]);

	 /* Make sure it has an extension */
	 extension = strrchr(filename, '.');
	 if (!extension)
		  strcat(filename, ".ttf");

	 /* Actually load the font */
	 font = Mx_FontLoadTTF(filename, points, 1);

	 /* Remove the extension for the fontname */
	 strcpy(fontname, filename);
	 extension = strrchr(fontname, '.');
	 *extension = '\0';

	 /* Dump the font to standard output */
	 mx_font_dump(font, stdout, fontname);
	 MXFREE(font);

	 return 0;
}
