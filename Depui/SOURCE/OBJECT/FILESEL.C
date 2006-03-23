#include "depui/config.h"
#include "depui/types.h"
#include "depui/args/args.h"
#include "depui/object/filesel.h"
#include "depui/object/defsize.h"
#include "depui/desktop/desktop.h"
#include "depui/desktop/driver.h"
#include "depui/geometry/geometry.h"
#include "depui/support/findfirs.h"
#include "depui/event/focus.h"
#include <stdio.h>
#ifdef WIN32
#include "depui/support/dirent.h"
#else
#include <dirent.h>
#endif

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Made size static so user can set size and it sticks */
static int width = 250;
static int height = 150;

unsigned int is_pattern(const char *p)
{
	 while (*p) {
		  switch (*p++) {

		  case '?':
		  case '*':
				return MxTrue;
		  }
	 }
	 return MxFalse;
}

static void filename_copy(char *dest, const char *src)
{
	 while ((*src) && (*src != '\t')) {
		  *dest = *src;
		  ++dest;
		  ++src;
	 }
	 *dest = '\0';
}

/* Function used to sort the captions in the file list.  It is complex
   because it has to find out which captions are for directories/files/drives
   and then sort them each alhpabetically */
static int filename_sort(const void *one, const void *two)
{
	 MxListDef *button1 = (MxListDef *) one;
	 MxListDef *button2 = (MxListDef *) two;

	 const char *caption1 = button1->caption;
	 const char *caption2 = button2->caption;

	 /* Both captions are empty */
	 if ((!caption1) && (!caption2))
		  return 0;

	 /* One caption is NULL, other is a real caption */
	 else if ((caption1) && (!caption2))
		  return -1;
	 else if ((!caption1) && (caption2))
		  return 1;

	 /* We have two captions, give sort order */
	 else {
		  unsigned int dir1 = MxFalse;
		  unsigned int dir2 = MxFalse;
		  unsigned int drv1 = MxFalse;
		  unsigned int drv2 = MxFalse;

		  const char *ptr1 = strchr(caption1, '/');
		  const char *ptr2 = strchr(caption2, '/');

		  /* Directories are marked with a '/' in the filename */
		  if ((ptr1) && (ptr1[1] == '\t'))
				dir1 = MxTrue;
		  if ((ptr2) && (ptr2[1] == '\t'))
				dir2 = MxTrue;

		  /* Drives are marked with a ':' in the second position */
		  if (caption1[1] == ':')
				drv1 = MxTrue;
		  if (caption2[1] == ':')
				drv2 = MxTrue;

		  /* First entry is a directory */
		  if (dir1) {

				/* Directories are alphabetically */
				if (dir2)
					 return strcmp(caption1, caption2);

				/* Directories are first */
				else
					 return -1;

				/* First entry is a drive */
		  } else if (drv1) {

				/* Drives are alphabetically */
				if (drv2)
					 return strcmp(caption1, caption2);

				/* Drives are last */
				else
					 return 1;

				/* First entry is a file */
		  } else {

				/* Files are alphabetically */
				if ((dir2 == MxFalse) && (drv2 == MxFalse))
					 return strcmp(caption1, caption2);

				/* Directories are before */
				else if (dir2)
					 return 1;

				/* Drives are after */
				else
					 return -1;
		  }
	 }
}

#ifdef __MSDOS__
static void force_drive(MxListDef * button, char drive)
{
	 char *caption = (char *) MxMalloc(5);

	 sprintf(caption, "%c:\t", drive);
	 button->caption = caption;
}

#endif

static void force_dir(MxListDef * button, const char *filename)
{
	 char *caption = (char *) MxMalloc(strlen(filename) + 6);

	 strcpy(caption, filename);
	 strcat(caption, "/\t");
	 button->caption = caption;
}

static void force_file(MxListDef * button, const char *filename, unsigned long size)
{
	 char *caption = (char *) MxMalloc(strlen(filename) + 15);

	 if (size > 1024l * 1024l)
		  sprintf(caption, "%s\t%4liM", filename, size / (1024l * 1024l));
	 else if (size > 1024)
		  sprintf(caption, "%s\t%4lik", filename, size / 1024l);
	 else
		  sprintf(caption, "%s\t%4lib", filename, size);

	 button->caption = caption;
}

static void add_files(char *file, const char *pattern, const int attrib, MxListDef ** def, unsigned int *defnum,
							 unsigned int *allocated)
{
	 int err;
	 Mxffblk blk;

	 char *ptr;

	 assert(file);
	 assert(pattern);
	 assert(attrib);

	 MX_TRACE("");

	 /* Skip past drive specifier */
	 ptr = mx_get_filename(file);
	 *ptr = 0;
	 strcat(file, pattern);

	 /* Search for valid filenames */
	 err = MxFindfirst(file, &blk, attrib);
	 while (!err) {

		  /* Make sure it has the correct attributes */
		  if ((attrib & FA_DIREC) && ((blk.ff_attrib & attrib) == 0))
				goto skipfile;

		  /* Don't put current dir in */
		  if (strcmp(blk.ff_name, ".") == 0)
				goto skipfile;

		  /* Do we need to make more array room */
		  if (*defnum >= *allocated) {
				*allocated = *allocated * 2;
				*def = (MxListDef *) MxRealloc(*def, (*allocated) * sizeof(MxListDef));
		  }
		  /* Fill the definition with zeros */
		  memset(&(*def)[*defnum], 0, sizeof(MxListDef));

		  /* Make the button to the correct type */
		  if (blk.ff_attrib & FA_DIREC)
				force_dir(&(*def)[*defnum], blk.ff_name);
		  else
				force_file(&(*def)[*defnum], blk.ff_name, blk.ff_fsize);

		  /* Goto the next list entry */
		  ++(*defnum);

		  /* Get the next filename */
		skipfile:
		  err = MxFindnext(&blk);
	 }

	 /* Keep the filename presentable */
	 ptr = mx_get_filename(file);
	 *ptr = 0;
}

#ifdef __MSDOS__
static void add_drives(MxListDef ** def, unsigned int *defnum, unsigned int *allocated)
{
	 int i;

	 MX_TRACE("");

	 for (i = 0; i < 26; i++) {

		  /* Only add the drive if we are sure that if exists */
		  if (!mx_drive_exists(i))
				continue;

		  /* Do we need to make more array room */
		  if (*defnum >= *allocated) {
				*allocated = *allocated * 2;
				*def = (MxListDef *) MxRealloc(*def, (*allocated) * sizeof(MxListDef));
		  }
		  /* Fill the definition with zeros */
		  memset(&(*def)[*defnum], 0, sizeof(MxListDef));

		  /* Make the button to the correct type */
		  force_drive(&(*def)[*defnum], 'A' + i);

		  /* Goto the next list entry */
		  ++(*defnum);
	 }
}
#endif

static void free_captions(MxListarea * listarea)
{
	 MxListDef *ptr = listarea->def;

	 while ((ptr) && (ptr->caption)) {

		  MX_TRACE(ptr->caption);

		  MxFree((void *) ptr->caption);
		  ++ptr;
	 }
}

/* Fill the file list with valid filenames */
void mx_filelist_fill(char *file, int attrib, const char *pattern, MxListarea * listarea)
{
	 char mypattern[MX_MAX_PATH];
	 char *ptr = mypattern;

	 MxListDef *def;
	 unsigned int defnum;
	 unsigned int allocated;

	 assert(file);
	 assert(attrib);
	 assert(pattern);

	 /* Get the list definition started */
	 def = (MxListDef *) MxMalloc(sizeof(MxListDef));
	 defnum = 0;
	 allocated = 1;

	 /* Always read in all directories */
	 if (attrib & FA_DIREC)
#ifdef __MSDOS__
		  add_files(file, "*.*", FA_DIREC, &def, &defnum, &allocated);
#else
		  add_files(file, "*", FA_DIREC, &def, &defnum, &allocated);
#endif

	 /* Read file in for each pattern */
	 strcpy(mypattern, pattern);

	 while ((ptr) && (*ptr)) {

		  /* Look forward to a semicolon to pick out the pattern */
		  char *next = strchr(ptr, ';');

		  if (next)
				*next = 0;

		  /* Add the files with the desired pattern */
		  add_files(file, ptr, attrib & ~FA_DIREC, &def, &defnum, &allocated);

		  /* Find the next pattern */
		  if (next)
				ptr = next + 1;
		  else
				ptr = next;
	 }

	 /* Add the drives too */
#ifdef __MSDOS__
	 add_drives(&def, &defnum, &allocated);
#endif

	 /* Cleanup extra list elements not used and put a terminator at the end
	    of the definition */
	 if (allocated != defnum + 1)
		  def = (MxListDef *) MxRealloc(def, (defnum + 1) * sizeof(MxListDef));
	 memset(&def[defnum], 0, sizeof(MxListDef));

	 /* Scroll the list back to the start */
	 MxMove(&listarea->base.object, 0, 0);

	 /* Sort the dirs and files and drives elements and tell the list to use
	    this */
	 qsort(def, defnum + 1, sizeof(MxListDef), filename_sort);

	 /* Set the new list def and cleanup the old one */
	 free_captions(listarea);
	 MxListDefSet(listarea, def, MxTrue);

	 /* Keep the filename up to date */
	 ptr = mx_get_filename(file);
	 *ptr = 0;
	 strcat(file, pattern);
}

/* Fill the file list with valid filenames */
static void fill_filelist(MxFileselector * sel)
{
	 mx_filelist_fill(sel->file, sel->attrib, sel->pattern, &sel->list.listarea);

	 /* Inform the editable line that we have made changes to it's children */
	 if (sel->base.object.init) {

		  /* Inform the text that the currect file has changed */
		  MxEditlineSet(&sel->editline, sel->file);
		  MxEditlineCursorTo(&sel->editline, strlen(sel->file));
		  MxEnqueueRefresh(&sel->editline.base.object, MxFalse);
	 }
}

/* Inform the caller that a file MAY have been chosen */
static void close_inform(MxFileselector * sel, MxEventType type)
{
	 MxEvent event;

	 event.type = type;
	 event.object.object = &sel->base.object;

	 if (sel->inform)
		  MxEnqueue(sel->inform, &event, 0);
}

static void filesel_geometry(MxFileselector * sel)
{
	 int x, y;
	 int bw, bh;
	 int th;

	 /* How big is our client */
	 x = MxW(sel->base.window.client);
	 y = MxH(sel->base.window.client);

	 /* What size are the buttons */
	 bw = MxW(&sel->ok.base.object);
	 bh = MxH(&sel->ok.base.object);

	 /* How high is our static text */
	 th = MxH(&sel->editline.base.object);

	 /* Put our buttons in the right place */
	 y -= bh + 1;
	 MxGeomRequest(&sel->ok.base.object, x - sel->border - bw - 6, y, 0, 0, (MxGeomFlags) (MxGeomX | MxGeomY));

	 /* Put out editable text in place */
	 y -= th + 1 + sel->border;
	 MxGeomRequest(&sel->editline.base.object, 0, y, x - 2 * sel->border, 0, (MxGeomFlags) (MxGeomY | MxGeomW));
	 MxEditlineCursorTo(&sel->editline, strlen(sel->file));

	 /* Make our list the correct size */
	 MxGeomRequest(&sel->list.base.object, 0, 0, x - 2 * sel->border, y - 2 * sel->border, (MxGeomFlags) (MxGeomW | MxGeomH));

	 /* Remember or size for next time */
	 width = MxW(&sel->base.object);
	 height = MxH(&sel->base.object);
}

static void change_drive(MxFileselector * sel, const char *dirname)
{
	 /* Put the drive name at the start */
	 char *p = sel->file;

	 *p++ = dirname[0];
	 *p++ = ':';
	 if (dirname[2] == '/')
		  *p++ = '/';
	 *p = 0;

	 /* Re-read the files in the new dir */
	 mx_fixpath(sel->file);
	 fill_filelist(sel);
}

static void change_dir(MxFileselector * sel, const char *dirname)
{
	 char temp[MX_MAX_PATH];
	 char newdir[MX_MAX_PATH];

	 char *file = mx_get_filename(sel->file);

	 strcpy(temp, file);
	 *file = 0;

	 filename_copy(newdir, dirname);
	 strcat(sel->file, newdir);
	 strcat(sel->file, temp);

	 /* Re-read the files in the new dir */
	 mx_fixpath(sel->file);
	 fill_filelist(sel);
}

static void change_file(MxFileselector * sel, const char *dirname)
{
	 char *file;
	 char temp[MX_MAX_PATH];

	 /* Get the basic path and the filename */
	 mx_fixpath(sel->file);
	 file = mx_get_filename(sel->file);
	 *file = 0;
	 filename_copy(temp, dirname);
	 strcat(sel->file, temp);
}

static void disable_ok(MxFileselector * sel, unsigned int disable)
{
	 /* Maybe there is no change */
	 if (disable == sel->ok.disabled)
		  return;

	 /* Update the object */
	 sel->ok.disabled = disable;
	 MxEnqueueRefresh(&sel->ok.base.object, MxFalse);
}

void *MxFileselectorListareaHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

		  /* What kind of element was selected and what to do with it */
	 case MxEventListareaSelected:{

				/* Which button was selected */
				MxListDef *button = event->listelem.def;
				unsigned int pressed = button->selected;

				const char *caption = button->caption;
				char *ptr = strchr(caption, '/');

				/* What is our file selector */
				MxListarea *list = (MxListarea *) MxParent(MxParent(object));
				MxFileselector *sel = (MxFileselector *) MxParent(MxParent(&list->base.object));

				/* Do the standard handling of clicks */
				MxListareaHandler(object, event);

				/* Was it a drive that was pressed */
				if ((caption) && (caption[0]) && (caption[1] == ':')) {

					 disable_ok(sel, MxTrue);
					 if (pressed)
						  change_drive(sel, caption);
				}

				/* Was it a directory */
				else if (ptr) {

					 disable_ok(sel, MxTrue);
					 if (pressed)
						  change_dir(sel, caption);

					 /* A file was pressed */
				} else {
					 disable_ok(sel, MxFalse);
					 change_file(sel, caption);

					 /* Update the text */
					 if (sel->base.object.init) {
						  MxEditlineSet(&sel->editline, sel->file);
						  MxEditlineCursorTo(&sel->editline, strlen(sel->file));
						  MxEnqueueRefresh(&sel->editline.base.object, MxFalse);
					 }
				}
				break;
		  }

	 default:
		  return MxListareaHandler(object, event);
	 }
	 return 0;
}

void *MxFileselectorHandler(MxObject * object, const MxEvent * const event)
{
	 MxFileselector *sel = (MxFileselector *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventDestroy:

		  free_captions(&sel->list.listarea);

		  /* Cleanup any memory that we may have allocated */
		  if (sel->ownspattern)
				MxFree((char *) sel->pattern);

		  return MxWindowHandler(object, event);

	 case MxEventOk:{
				/* Get the currect filename */
				const char *caption = MxEditlineCaption(&sel->editline);
				DIR *dir = opendir(caption);
				unsigned int pattern = is_pattern(caption);

				/* Maybe the user typed in a pattern */
				if (pattern) {

					 /* Find the user's pattern */
					 char *file = mx_get_filename((char *) caption);
					 char *newpat = (char *) MxMalloc(strlen(file) + 1);

					 if (newpat) {

						  /* Cleanup our old pattern and set the new one */
						  if (sel->ownspattern)
								MxFree((char *) sel->pattern);

						  strcpy(newpat, file);
						  sel->pattern = newpat;
						  sel->ownspattern = MxTrue;
					 }
					 /* Read in the list with this pattern */
					 strcpy(sel->file, caption);
					 fill_filelist(sel);

					 /* Maybe the user typed in a directory, so go there */
				} else if (dir) {
					 closedir(dir);
					 strcpy(sel->file, caption);
					 fill_filelist(sel);

					 /* The user enetered a filename so return it */
				} else {
					 strcpy(sel->file, caption);
					 close_inform(sel, MxEventOk);
					 MxDestroy(object);
				}
				break;
		  }

	 case MxEventCancel:
		  strcpy(sel->file, "");
		  close_inform(sel, MxEventCancel);
		  MxDestroy(object);
		  break;

	 case MxEventExit:
		  close_inform(sel, MxEventCancel);
		  strcpy(sel->file, "");
		  return MxWindowHandler(object, event);

	 case MxEventGeomChanged:
		  MxWindowHandler(object, event);
		  filesel_geometry(sel);
		  return MxWindowHandler(object, event);

	 case MxEventPostInit:
		  MxWindowHandler(object, event);
		  filesel_geometry(sel);
		  break;

		  /* enable the OK button if the user is manually editing a filename */
	 case MxEventFocusChild:
		  disable_ok(sel, MxFalse);
		  break;

		  /* Act like a normal window */
	 default:
		  return MxWindowHandler(object, event);
	 }
	 return 0;
}

/* Simple tabstop function that puts the file size on
   the right hand side of the file list */
static int tabstop(const MxObject * object, const int tab)
{
	 const int w = MxW(object);
	 const int l = MxFontLength(MxFontDefault, "8888M") + 4;

	 (void) tab;

	 return w - l;
}

MxFileselector *MxFileselectorStart(const MxFileselectorArgs * const args, MxObject * blocked, MxObject * inform)
{
	 char *ptr;
	 MxFileselectorArgs realargs;
	 MxFileselector *sel;

	 MX_TRACE("");

	 /* Make sure we have a place to put the resulting filename */
	 assert(args);
	 assert(args->file);

	 /* Make a copy of the args so that the argument can be const, but we can
	    force some thing (like modality) into the window */
	 MxUserArgsInit(realargs, args);

	 /* Allocate room for the file delector dialog */
	 sel = (MxFileselector *) MxMalloc(sizeof(MxFileselector));
	 assert(sel);

	 if (sel) {
		  memset(sel, 0, sizeof(MxFileselector));

		  /* Make the underlying window to be modal */
		  realargs.window.modal = MxTrue;
		  realargs.window.blocked = blocked;
		  realargs.window.centered = MxTrue;

		  /* Construct the underlying window */
		  MxWindowConstruct(&sel->base.window, 0, 0, 0, width, height, &realargs.window);
		  sel->base.object.handler = MxFileselectorHandler;

		  /* Tell the selector where to put the resulting filename */
		  sel->file = realargs.file;
		  sel->inform = inform;

		  sel->border = realargs.border + 2;

		  /* What files to look for */
		  if (realargs.pattern)
				sel->pattern = realargs.pattern;
		  else
#ifdef __MSDOS__
				sel->pattern = "*.*";
#else
				sel->pattern = "*";
#endif

		  /* Keep the filename up to date */
		  ptr = mx_get_filename(sel->file);
		  *ptr = 0;
		  strcat(sel->file, sel->pattern);

		  if (realargs.attrib)
				sel->attrib = realargs.attrib;
		  else
				sel->attrib = FA_ARCH | FA_DIREC;

		  /* Remember that the memory has to be deleted at some point */
		  sel->base.object.allocated = MxTrue;
#ifdef MX_WINDOW_NAMES
		  sel->base.object.name = "MxFileselector";
#endif
		  /* Create the list of filenames */
		  if (sel->border == 0)
				realargs.list.scroll.border -= 1;

		  if (!realargs.list.listarea.tabstop)
				realargs.list.listarea.tabstop = tabstop;

		  MxListConstruct(&sel->list, sel->base.window.client, sel->border, sel->border, 10, 10, &realargs.list);
		  sel->list.listarea.base.object.handler = MxFileselectorListareaHandler;

		  /* Create the text portion */
		  MxEditlineConstruct(&sel->editline, sel->base.window.client, sel->border, 10, MxDefault, MxDefault, 0);
		  MxEditlineSet(&sel->editline, sel->file);

		  /* Create the Ok button */
		  realargs.ok.defaultbutton = MxTrue;
		  MxOkButtonConstruct(&sel->ok, sel->base.window.client, 0, 0, MxDefault, MxDefault, &realargs.ok);
		  sel->ok.disabled = MxTrue;

		  /* Fill in the filenames before we insert so we can save alot of
		     geometry and region messages bieng passed */
		  fill_filelist(sel);

		  /* Start the object running */
		  MxInsert(&sel->base.object, mx_desk, MxTrue);
		  MxActiveSet(&sel->base.object, 0);
		  MxFocusSet(&sel->editline.base.object);

		  /* Tell the user what file selector was made */
		  return sel;
	 }
	 /* We were unsuccessful in making an file selector box */
	 return 0;
}
