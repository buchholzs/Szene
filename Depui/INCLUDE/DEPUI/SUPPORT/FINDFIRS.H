#ifndef MX_PLATFORM_SUPPORT_FINDFIRS_H
#define MX_PLATFORM_SUPPORT_FINDFIRS_H

#include "depui/config.h"
#ifdef __cplusplus
extern "C" {
#endif
/* emulate the FA_* flags for platforms that don't already have them */
#ifndef FA_RDONLY
#define FA_RDONLY       1
#define FA_HIDDEN       2
#define FA_SYSTEM       4
#define FA_LABEL        8
#define FA_DIREC        16
#define FA_ARCH         32
#endif
/* Only onclude our filename stuff if the platform really needs it */
#ifdef MX_NEED_FINDFIRST
#include "depui/types.h"
#ifndef WIN32
#include <dirent.h>
#endif
#include <sys/stat.h>
	 typedef struct Mxffblk {
		  unsigned char ff_attrib;
		  unsigned short ff_ftime;
		  unsigned short ff_fdate;
		  unsigned long ff_fsize;
		  char ff_name[1024];
	 } Mxffblk;

	 int MxFindfirst(char *pattern, struct Mxffblk *ffblk, int attrib);
	 int MxFindnext(struct Mxffblk *ffblk);

	 /* We have find first so just macro to the real functions and structs */
#else
#include <dir.h>
#define Mxffblk       struct ffblk
#define MxFindfirst   findfirst
#define MxFindnext    findnext
#endif
	 char *mx_get_filename(char *path);
	 char *mx_get_extension(char *path);
	 void mx_put_backslash(char *filename, int size);
	 void mx_fixpath(char *path);
	 int mx_drive_exists(int x);

#ifdef __cplusplus
}
#endif
#endif
