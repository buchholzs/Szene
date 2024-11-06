#include "depui/config.h"
#include "depui/macros.h"
#include "depui/desktop/driver.h"
#include "depui/object/statict.h"
#include "depui/object/text.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

int MxStatictextPixel(const MxStatictext * stext, unsigned int offset)
{
	 int defw;
	 const char *temp;

	 temp = mx_text_copy(stext->caption, offset);
	 defw = MxFontLength(MxFontDefault, temp);

	 MxFree((void *) temp);
	 return defw;
}

int MxStatictextOffset(const MxStatictext * stext, unsigned int *pixel)
{
	 unsigned int rhs = 0;
	 unsigned int lastrhs = 0;
	 unsigned int len = strlen(stext->caption);
	 unsigned int toofar = MxTrue;

	 char *temp = 0;

	 if ((len) && (stext->caption)) {
		  temp = mx_text_copy(stext->caption, len);
		  rhs = MxFontLength(MxFontDefault, temp);
		  lastrhs = rhs;
	 }

	 /* Is the right hand side of the string left of the pixel */
	 while ((temp) && (rhs > *pixel) && (len)) {

		  /* Shorten the string */
		  --len;
		  temp[len] = '\0';

		  /* How wide is the string */
		  lastrhs = rhs;
		  rhs = MxFontLength(MxFontDefault, temp);
		  toofar = MxFalse;
	 }

	 /* Cleanup */
	 if (temp)
		  MxFree((void *) temp);

	 /* Maybe the string isn't wide enough */
	 if (toofar) {
		  *pixel = rhs;
		  return len;

		  /* Front side is closer */
//  } else if (*pixel - rhs < lastrhs - *pixel) {
	 } else {
		  *pixel = rhs;
		  return len;

		  /* Back side is closer */
//  } else {
//      *pixel = lastrhs;
//      return len + 1;
	 }
}
