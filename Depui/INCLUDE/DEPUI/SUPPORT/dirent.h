/*--------------------------------------------------------------------------
 DEPUI-GFX-TK 3.0 - GPL portable source code libraries 
 http://www.deleveld.dds.nl/depui.htm
 See file docs/copying for copyright details
 ---------------------------------------------------------------------------*/

#ifndef MX_HAVE_DEPUI_DIRENT
#define MX_HAVE_DEPUI_DIRENT

/*

    Implementation of POSIX directory browsing functions and types for Win32.

    Author:  Kevlin Henney (kevlin@acm.org, kevlin@curbralan.com)
    History: Created March 1997. Updated February 2003.
    Rights:  See end of file.

*/

struct dirent {
	 char *d_name;
};

#include <errno.h>
#include <io.h>					  /* _findfirst and _findnext set errno iff
										     they return -1 */
#include <stdlib.h>
#include <string.h>

typedef struct DIR {
	 long handle;					  /* -1 for failed rewind */
	 struct _finddata_t info;
	 struct dirent result;		  /* d_name null iff first time */
	 char *name;					  /* null-terminated char string */
} DIR;


#ifdef __cplusplus
extern "C" {
#endif

DIR *opendir(const char *name);
int closedir(DIR * dir);
struct dirent *readdir(DIR * dir);
void rewinddir(DIR * dir);

#ifdef __cplusplus
}
#endif
/*

    Copyright Kevlin Henney, 1997, 2003. All rights reserved.

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose is hereby granted without fee, provided
    that this copyright and permissions notice appear in all copies and
    derivatives.

    This software is supplied "as is" without express or implied warranty.

    But that said, if there are any problems please get in touch.

*/

#endif
