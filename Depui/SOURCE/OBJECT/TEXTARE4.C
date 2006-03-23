#include "depui/config.h"
#include "depui/object/text.h"
#include "depui/desktop/driver.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

const MxTextareaParse *MxTextareaParseIndex(MxTextarea * textarea, const int offset)
{
	 unsigned int i;
	 const MxTextareaParse *parse = textarea->parse;

	 assert(textarea);
	 assert(parse);

	 for (i = 0; i < textarea->parsenum; i++) {

		  /* Does the end of the line go past the offset we want */
		  const int end = parse->offset + parse->len + parse->skip;

		  if (end > offset)
				return parse;

		  ++parse;
	 }
	 /* Othersize return the last line */
	 return parse - 1;
}

void MxTextareaPixel(MxTextarea * textarea, const MxTextareaParse * parse, const int offset, int *pixx, int *pixy)
{
	 char *temp;
	 const int len = offset - parse->offset;

	 assert(textarea);
	 assert(parse);

	 *pixy = parse->y;
	 temp = mx_text_copy(&textarea->caption[parse->offset], len);
	 if (temp) {
		  *pixx = MxFontLength(MxFontDefault, temp);
		  MxFree(temp);
	 }
}

int MxTextareaOffset(MxTextarea * textarea, const MxTextareaParse * parse, int *pixel)
{
	 unsigned int i;
	 char temp[5];
	 const char *ptr = &textarea->caption[parse->offset];
	 int p = 0;
	 int lastp = 0;

	 assert(textarea);
	 assert(parse);
	 assert(pixel);

	 temp[1] = 0;

	 for (i = 0; i < parse->len; i++) {

		  /* How wide is the character */
		  temp[0] = *ptr;
		  lastp = p;
		  p += MxFontLength(MxFontDefault, temp);

		  /* Have we gone far enough */
		  if (p > *pixel)
				break;
	 }

	 /* Maybe the string isn't wide enough */
	 if (p < *pixel) {
		  *pixel = p;
		  return parse->offset + parse->len;

		  /* The string was wide enough */
	 } else {
		  *pixel = lastp;
		  return parse->offset + i;
	 }
}

const MxTextareaParse *MxTextareaLine(MxTextarea * textarea, int y)
{
	 unsigned int i;
	 const MxTextareaParse *parse = textarea->parse;

	 assert(textarea);
	 assert(parse);

	 for (i = 0; i < textarea->parsenum; i++) {

		  /* Are we abover the y pixel */
		  const int top = parse->y + parse->h;

		  if (top > y)
				return parse;

		  ++parse;
	 }
	 /* Return the last line */
	 return parse - 1;
}
