/* This code has been taken from Allegro with very minor modifications */
#include "depui/config.h"

#ifdef MX_NEED_FINDFIRST

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

#include "depui/debug/alloc.h"
#include "depui/support/findfirs.h"
#ifdef WIN32
#include "depui/support/dirent.h"
#else
#include <dirent.h>
#endif
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define NAMLEN(dirent) (strlen((dirent)->d_name))

struct {
	 int attrib;
	 char dirname[MX_MAX_PATH];
	 char pattern[MX_MAX_PATH];
	 char tempname[MX_MAX_PATH];
	 char filename[MX_MAX_PATH];
	 DIR *dir;
	 struct dirent *entry;
	 struct stat stat;
} ff_info;

static int ff_match(char *s1, char *s2);

/* _alemu_findfirst:
 *  find first file matching pattern, which has no attribs
 *  that are not present in attrib.
 */
int MxFindfirst(char *pattern, struct Mxffblk *ffblk, int attrib)
{
	 /* initialize ff_info structure */
	 ff_info.attrib = attrib;

	 ff_info.dirname[0] = 0;
	 strncat(ff_info.dirname, pattern, sizeof(ff_info.dirname) - 1);
	 *mx_get_filename(ff_info.dirname) = 0;
	 if (ff_info.dirname[0] == 0)
		  strcpy(ff_info.dirname, "./");

	 ff_info.pattern[0] = 0;
	 strncat(ff_info.pattern, mx_get_filename(pattern), sizeof(ff_info.pattern) - 1);

	 /* nasty bodge, but gives better compatibility with DOS programs */
	 if (strcmp(ff_info.pattern, "*.*") == 0)
		  strcpy(ff_info.pattern, "*");

	 if (ff_info.dir != 0)
		  closedir(ff_info.dir);

	 /* open directory */
	 ff_info.dir = opendir(ff_info.dirname);
	 if (ff_info.dir == 0)
		  return ((errno == 0) ? ENOENT : errno);

	 return MxFindnext(ffblk);
}

/* _alemu_findnext:
 *  Find next file matching pattern.
 */
int MxFindnext(struct Mxffblk *ffblk)
{
	 struct tm *mtime;

	 while (1) {
		  /* read directory entry */
		  ff_info.entry = readdir(ff_info.dir);
		  if (ff_info.entry == 0)
				return ((errno == 0) ? ENOENT : errno);

		  /* try to match file name with pattern */
		  ff_info.tempname[0] = 0;
		  if (NAMLEN(ff_info.entry) >= sizeof(ff_info.tempname))
				strncat(ff_info.tempname, ff_info.entry->d_name, sizeof(ff_info.tempname) - 1);
		  else
				strncat(ff_info.tempname, ff_info.entry->d_name, NAMLEN(ff_info.entry));
		  if (!ff_match(ff_info.tempname, ff_info.pattern))
				continue;

		  strcpy(ff_info.filename, ff_info.dirname);
		  mx_put_backslash(ff_info.filename, sizeof(ff_info.filename));
		  strncat(ff_info.filename, ff_info.tempname, sizeof(ff_info.filename) - strlen(ff_info.filename) - 1);

		  /* get file statistics */
		  if (stat(ff_info.filename, &(ff_info.stat)))
				continue;

		  ffblk->ff_attrib = 0;
#ifdef WIN32
		  if ((ff_info.stat.st_mode & S_IWRITE) == 0)
				ffblk->ff_attrib |= FA_RDONLY;
		  if ((ff_info.stat.st_mode & S_IFDIR) != 0)
				ffblk->ff_attrib |= FA_DIREC;
#else
		  if ((ff_info.stat.st_mode & S_IRUSR) == 0)
				ffblk->ff_attrib |= FA_RDONLY;
		  if (S_ISDIR(ff_info.stat.st_mode))
				ffblk->ff_attrib |= FA_DIREC;
#endif
		  if ((ff_info.tempname[0] == '.')
				&& ((ff_info.tempname[1] != '.')
					 || (ff_info.tempname[2] != 0)))
				ffblk->ff_attrib |= FA_HIDDEN;

		  /* have any attributes, not listed in attrib? */
		  if ((ffblk->ff_attrib & ~ff_info.attrib) != 0)
				continue;

		  mtime = gmtime(&(ff_info.stat.st_mtime));
		  ffblk->ff_ftime = ((mtime->tm_hour << 11) | (mtime->tm_min << 5)
									| (mtime->tm_sec >> 1));
		  ffblk->ff_fdate = (((mtime->tm_year - 1980) << 9) | (mtime->tm_mon << 5)
									| (mtime->tm_mday));

		  ffblk->ff_fsize = ff_info.stat.st_size;

		  ffblk->ff_name[0] = 0;
		  strncat(ffblk->ff_name, ff_info.tempname, sizeof(ffblk->ff_name) - 1);

		  return 0;
	 }
}

#define FF_MATCH_TRY 0
#define FF_MATCH_ONE 1
#define FF_MATCH_ANY 2

struct ff_match_data {
	 int type;
	 char *s1;
	 char *s2;
};

/* ff_match:
 *  Match two strings ('*' matches any number of characters,
 *  '?' matches any character).
 */
static int ff_match(char *s1, char *s2)
{
	 static unsigned int size = 0;
	 static struct ff_match_data *data = 0;
	 char *s1end = s1 + strlen(s1);
	 int index, c1, c2;

	 /* allocate larger working area if necessary */
	 if ((data != 0) && (size < strlen(s2))) {
		  MxFree(data);
		  data = 0;
	 }
	 if (data == 0) {
		  size = strlen(s2);
		  data = MxMalloc(sizeof(struct ff_match_data) * size * 2 + 1);

		  if (data == 0)
				return 0;
	 }

	 index = 0;
	 data[0].s1 = s1;
	 data[0].s2 = s2;
	 data[0].type = FF_MATCH_TRY;

	 while (index >= 0) {
		  s1 = data[index].s1;
		  s2 = data[index].s2;
		  c1 = *s1;
		  c2 = *s2;

		  switch (data[index].type) {

		  case FF_MATCH_TRY:
				if (c2 == 0) {
					 /* pattern exhausted */
					 if (c1 == 0)
						  return 1;
					 else
						  index--;
				} else if (c1 == 0) {
					 /* string exhausted */
					 while (*s2 == '*')
						  s2++;
					 if (*s2 == 0)
						  return 1;
					 else
						  index--;
				} else if (c2 == '*') {
					 /* try to match the rest of pattern with empty string */
					 data[index++].type = FF_MATCH_ANY;
					 data[index].s1 = s1end;
					 data[index].s2 = s2 + 1;
					 data[index].type = FF_MATCH_TRY;
				} else if ((c2 == '?') || (c1 == c2)) {
					 /* try to match the rest */
					 data[index++].type = FF_MATCH_ONE;
					 data[index].s1 = s1 + 1;
					 data[index].s2 = s2 + 1;
					 data[index].type = FF_MATCH_TRY;
				} else
					 index--;
				break;

		  case FF_MATCH_ONE:
				/* the rest of string did not match, try earlier */
				index--;
				break;

		  case FF_MATCH_ANY:
				/* rest of string did not match, try add more chars to string
				   tail */
				if (--data[index + 1].s1 >= s1) {
					 data[index + 1].type = FF_MATCH_TRY;
					 index++;
				} else
					 index--;
				break;

		  default:
				/* this is a bird? This is a plane? No it's a bug!!! */
				return 0;
		  }
	 }

	 return 0;
}

#else
extern int mx_ignore_this;

#endif
