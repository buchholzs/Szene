#ifndef MX_OBJECT_FILESEL_H
#define MX_OBJECT_FILESEL_H

#include "depui/config.h"
#include "depui/object/window.h"
#include "depui/object/list.h"
#include "depui/object/edit.h"
#include "depui/object/button.h"
#include "depui/support/findfirs.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxFileselector {
		  union {
				MxObject object;
				MxWindow window;
		  } base;

		  MxList list;
		  MxButton ok;
		  MxEditline editline;

		  int attrib;

		  char *file;

		  MxObject *inform;

		  int border;

		  const char *pattern;
		  unsigned int ownspattern:1;

	 } MxFileselector;

	 typedef struct MxFileselectorArgs {

		  MxWindowArgs window;
		  MxListArgs list;
		  MxButtonArgs ok;
		  MxEditlineArgs editline;

		  const char *pattern;
		  unsigned int ownspattern;
		  int attrib;

		  char *file;

		  int border;

	 } MxFileselectorArgs;

	 void *MxFileselectorHandler(MxObject * object, const MxEvent * const event);

	 MxFileselector *MxFileselectorStart(const MxFileselectorArgs * const args, MxObject * blocked, MxObject * inform);

	 /* Special handlers dor directory and file elements in the list */
	 void *MxFileselectorListareaHandler(MxObject * object, const MxEvent * const event);

	 void mx_filelist_fill(char *file, int attrib, const char *pattern, MxListarea * listarea);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxFileselectorArgs > MxpFileselectorArgs;

#endif

#endif
