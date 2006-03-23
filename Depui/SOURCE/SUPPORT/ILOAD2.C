#include "depui/config.h"
#if defined(MX_NEED_IMAGE)

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/support/image.h"
#if defined(MX_IMAGE_LOAD_PCX) || defined(MX_IMAGE_LOAD_BMP)

/* Used by PCX loader */
Int16 mx_igetw(FILE * f)
{
	 int b1, b2;

	 if ((b1 = getc(f)) != EOF)
		  if ((b2 = getc(f)) != EOF)
				return ((b2 << 8) | b1);

	 return EOF;
}

/* Used by PCX loader */
Int32 mx_igetl(FILE * f)
{
	 int b1, b2, b3, b4;

	 if ((b1 = getc(f)) != EOF)
		  if ((b2 = getc(f)) != EOF)
				if ((b3 = getc(f)) != EOF)
					 if ((b4 = getc(f)) != EOF)
						  return (((long) b4 << 24) | ((long) b3 << 16) | ((long) b2 << 8)
									 | (long) b1);

	 return EOF;
}

#if defined(MX_IMAGE_LOAD_BMP)

/* Used by BMP loader */
Int32 mx_mgetl(FILE * f)
{
	 int b1, b2, b3, b4;

	 if ((b1 = getc(f)) != EOF)
		  if ((b2 = getc(f)) != EOF)
				if ((b3 = getc(f)) != EOF)
					 if ((b4 = getc(f)) != EOF)
						  return (((long) b1 << 24) | ((long) b2 << 16) | ((long) b3 << 8)
									 | (long) b4);

	 return EOF;
}

#endif

#else
extern int mx_ignore_this;

#endif

#else
extern int mx_ignore_this;

#endif
