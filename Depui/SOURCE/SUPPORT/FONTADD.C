#include "depui/config.h"
#ifdef MX_NEED_FONT

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/debug/alloc.h"
#include "depui/support/font.h"
#include <stdlib.h>

static int _index_compare(const void *one, const void *two)
{
	 return ((MxFontIndex *) one)->start - ((MxFontIndex *) two)->start;
}

static void _font_extend(MxFont ** font, const unsigned int c, const unsigned char *newchardata, const int bytes)
{
	 int i;
	 unsigned int size;

	 MxFontIndex *data;
	 MxFontIndex newdata;
	 unsigned char *chardata;

	 const unsigned int memsize = sizeof(MxFont) + ((*font)->sections + 1) * sizeof(MxFontIndex) + ((*font)->size + bytes);

	 /* Reallocate the font to the new size */
	 *font = (MxFont *) MxRealloc(*font, memsize);

	 /* Point to the data of the old font */
	 data = (MxFontIndex *) ((*font) + 1);
	 chardata = (unsigned char *) (data + (*font)->sections);
	 size = (*font)->size;

	 /* Move the bytes over */
	 for (i = size; i >= 0; i--)
		  chardata[i + sizeof(MxFontIndex)] = chardata[i];

	 /* Put the new bytes at the end */
	 for (i = 0; i < bytes; i++)
		  chardata[size + sizeof(MxFontIndex) + i] = newchardata[i];

	 /* Put the new section in */
	 newdata.start = c & (~0x7f);
	 for (i = 0; i < 128; i++)
		  newdata.index[i] = 0;

	 /* Point to the new added character data */
	 newdata.index[c - newdata.start] = size;

	 /* Update the font sizes and sections */
	 data[(*font)->sections] = newdata;
	 ++((*font)->sections);
	 (*font)->size += bytes;

	 /* Make sure the index sections are in order */
	 qsort(data, (*font)->sections, sizeof(MxFontIndex), _index_compare);
}

static void _font_data(MxFont ** font, const unsigned int c, const unsigned char *newchardata, const int bytes)
{
	 int i;

	 MxFontIndex *data;
	 unsigned char *chardata;

	 const unsigned int memsize = sizeof(MxFont)
		  + ((*font)->sections) * sizeof(MxFontIndex)
		  + ((*font)->size + bytes);

	 const unsigned int size = (*font)->size;

	 /* Reallocate the font to the new size */
	 *font = (MxFont *) MxRealloc(*font, memsize);

	 /* Point to the data of the old font */
	 data = (MxFontIndex *) ((*font) + 1);
	 chardata = (unsigned char *) (data + (*font)->sections);

	 /* Put the new bytes at the end */
	 for (i = 0; i < bytes; i++)
		  chardata[size + i] = newchardata[i];

	 /* Tell the section where the char data is */
	 data = (MxFontIndex *) mx_font_range(*font, c);
	 data->index[c - data->start] = (*font)->size;

	 /* The font is bigger now */
	 (*font)->size += bytes;
}

static void _font_add_char(MxFont ** font, const unsigned int c, const unsigned char *data, unsigned int size)
{
	 /* We want mx_font_range to return a const, so we have to cast away
	    constness here so we can update the index of the character data */
	 MxFontIndex *range = (MxFontIndex *) mx_font_range(*font, c);

	 /* Make a new range if we don't already have a suitable font range */
	 if (!range)
		  _font_extend(font, c, data, size);

	 /* Has the character allready been filled in */
	 else if (!(range->index[c - range->start]))
		  _font_data(font, c, data, size);
}

unsigned int mx_font_set_char(MxFont ** font, const unsigned int index, const unsigned char *data, unsigned int size)
{
	 if (!((*font)->allocated))
		  return MxFalse;

	 _font_add_char(font, index, data, size);
	 return MxTrue;
}

#else
extern int mx_ignore_this;

#endif
