#ifndef __SCENEDEBUG_H_INCLUDED__
#define __SCENEDEBUG_H_INCLUDED__
extern char *_scene_debug_file;
extern int   _scene_debug_line;
extern void  _scene_debug_printf(char *fmt,...);
#  define DBGPRINTF(x) do {           \
       _scene_debug_file = __FILE__;         \
       _scene_debug_line = __LINE__;         \
       _scene_debug_printf x ;               \
   } while (0)
#endif  /* whole file */
