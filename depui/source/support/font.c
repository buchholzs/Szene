#include "depui/config.h"

#ifdef MX_NEED_FONT

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/types.h"
#include "depui/debug/alloc.h"
#include "depui/support/font.h"

static void Mx_FontConstruct(MxFont * font, unsigned int height, MxFontFlag flags)
{
	 font->height = height, font->size = 0, font->sections = 0, font->allocated = MxFalse, font->flags = flags;
}

void Mx_FontDestroy(MxFont * font)
{
	 if (font->allocated)
		  MxFree(font);
}

MxFont *Mx_FontCreate(unsigned int height, MxFontFlag flags)
{
	 MxFont *font = (MxFont *) MxMalloc(sizeof(MxFont));

	 if (font) {
		  Mx_FontConstruct(font, height, flags);
		  font->allocated = MxTrue;
	 }

	 return font;
}

const MxFontIndex *mx_font_range(const MxFont * font, const unsigned int c)
{
	 unsigned int i = 0;
	 MxFontIndex *data = (MxFontIndex *) (font + 1);

	 /* Look in all the font sections */
	 for (i = 0; i < font->sections; i++) {

		  /* Is the character in the range of the font */
		  if ((c >= data->start) && (c < (data->start + 128)))
				return data;

		  /* The sections are in ascending order, are we past it? */
		  else if (c < data->start)
				return 0;

		  ++data;
	 }
	 return 0;
}

unsigned int Mx_FontLength(const MxFont * font, const char *text)
{
	 unsigned int len = 0;
	 const MxFontIndex *range = 0;

	 MxFontIndex *data = (MxFontIndex *) (font + 1);
	 const unsigned char *chardata = (const unsigned char *) (data + font->sections);

	 if (!text)
		  return 0;

	 if (font->sections == 0)
		  return 0;

	 while (*text) {
		  const unsigned int c = *text;

		  if ((!range) || (c < range->start) || (c >= (range->start + 128)))
				range = mx_font_range(font, c);

		  if ((range) && (c >= range->start) && (c < (range->start + 128))) {

				/* Do nothing, we already have the right range */
		  } else {
				/* Find the new range for the font */
				range = mx_font_range(font, c);
		  }

		  if (range)
				len += chardata[range->index[c - range->start]];

		  ++text;
	 }
	 return len;
}

unsigned int Mx_FontHeight(const MxFont * font)
{
	 return font->height;
}

#else
extern int mx_ignore_this;

#endif
