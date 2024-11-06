#include "depui/config.h"
#if defined(MX_NEED_IMAGE)

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/support/image.h"
#include <string.h>

MxImage *Mx_ImageLoad(const char *filename, int bits, MxColorFunc makecol)
{
	 /* Find the extension on the filename */
	 const char *pnt = strrchr(filename, '.');

	 if (!pnt)
		  return 0;

	 (void) bits;
	 (void) makecol;

#ifdef MX_IMAGE_LOAD_PCX
	 if (!strcmp(pnt, ".pcx"))
		  return Mx_ImageLoadPCX(filename, bits, makecol);
#endif

#ifdef MX_IMAGE_LOAD_BMP
	 if (!strcmp(pnt, ".bmp"))
		  return Mx_ImageLoadBMP(filename, bits, makecol);
#endif

	 return 0;
}

#else
extern int mx_ignore_this;

#endif
