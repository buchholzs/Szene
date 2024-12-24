#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "scenedbg.h"

#ifndef DBG_LOGFILE
#define DBG_LOGFILE "scndebug.log"
#endif

const char *_scene_debug_file;
int   _scene_debug_line;
#ifdef __GNUC__
const char *_scene_debug_function;
# endif

#pragma warning(disable:4996)
void _scene_debug_printf(const char *fmt,...)
{
	FILE *dfp = NULL;
	va_list ap;
	dfp = fopen(DBG_LOGFILE,"at");
	if(!dfp) return;
#ifdef __GNUC__
	fprintf(dfp,"%s|%s|%d: ",
		_scene_debug_file, _scene_debug_function, _scene_debug_line);
#else
	fprintf(dfp,"%s/%d: ", _scene_debug_file, _scene_debug_line);
#endif
	va_start(ap,fmt);
	vfprintf(dfp,fmt,ap);
	va_end(ap);
	fprintf(dfp, "\n");
	fclose(dfp);
}
