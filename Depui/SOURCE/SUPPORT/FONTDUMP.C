#include "depui/config.h"
#ifdef MX_NEED_FONT

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/support/font.h"
static void _print_section(const MxFontIndex * index, FILE * stream)
{
	 int i;

	 fprintf(stream, "\t\t{\n");
	 fprintf(stream, "\t\t\t%i,\n", index->start);

	 fprintf(stream, "\t\t\t{\n");
	 fprintf(stream, "\t\t\t\t");

	 for (i = 0; i < 127; i++) {
		  fprintf(stream, "%i,", index->index[i]);

		  if (i % 16 == 15)
				fprintf(stream, "\n\t\t\t\t");
	 }

	 fprintf(stream, "%i \n\t\t\t}\n", index->index[127]);

	 fprintf(stream, "\t\t}");
}

static void _print_data(const unsigned char *data, const unsigned int size, FILE * stream)
{
	 unsigned int i, c = 0;

	 fprintf(stream, "\t{\n\t\t");

	 for (i = 0; i < size - 1; i++) {
		  fprintf(stream, "0x%02x,", data[i]);

		  if ((c % 16) == 15)
				fprintf(stream, "\n\t\t");
		  ++c;
	 }

	 fprintf(stream, "0x%02x\n", *data);

	 fprintf(stream, "\t}\n");
}

void mx_font_dump(const MxFont * font, FILE * stream, const char *name)
{
	 unsigned int i;

	 MxFontIndex *data = (MxFontIndex *) (font + 1);
	 const unsigned char *chardata = (const unsigned char *) (data + font->sections);

	 fprintf(stream, "typedef struct MxFont_%i_%i {\n", font->sections, font->size);
	 fprintf(stream, "\tMxFont        base;\n");
	 fprintf(stream, "\tMxFontIndex   index[%i];\n", font->sections);
	 fprintf(stream, "\tunsigned char data[%i];\n", font->size);
	 fprintf(stream, "} MxFont_%i_%i;\n\n\n", font->sections, font->size);

	 fprintf(stream, "const MxFont_%i_%i %s = {\n", font->sections, font->size, name);

	 fprintf(stream, "\t{\n");
	 fprintf(stream, "\t\t%i,\n", font->height);
	 fprintf(stream, "\t\t%i,\n", font->size);
	 fprintf(stream, "\t\t%i,\n", font->sections);
	 fprintf(stream, "\t\t(MxFontFlag)%i,\n", font->flags);
	 fprintf(stream, "\t\t0\n"); /* Dumped font is never allocated */
	 fprintf(stream, "\t},\n");

	 fprintf(stream, "\t{\n");

	 for (i = 0; i < font->sections - 1; i++) {
		  _print_section(&data[i], stream);

		  fprintf(stream, ",\n");
	 }
	 _print_section(&data[font->sections - 1], stream);
	 fprintf(stream, "\n");

	 fprintf(stream, "\t},\n");

	 _print_data(chardata, font->size, stream);

	 fprintf(stream, "};\n\n");
}

#else
extern int mx_ignore_this;

#endif
