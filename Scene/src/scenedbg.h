#ifndef __SCENEDEBUG_H_INCLUDED__
#define __SCENEDEBUG_H_INCLUDED__
extern const char *_scene_debug_file;
extern int   _scene_debug_line;
extern void  _scene_debug_printf(char *fmt,...);
# ifdef __GNUC__
  extern const char *_scene_debug_function;
#  define DBGPRINTF(x) do {           \
	   _scene_debug_file = __FILE__;         \
	   _scene_debug_line = __LINE__;         \
	   _scene_debug_function = __FUNCTION__; \
	   _scene_debug_printf x;                \
   } while (0)
# else
#  define DBGPRINTF(x) do {           \
       _scene_debug_file = __FILE__;         \
       _scene_debug_line = __LINE__;         \
       _scene_debug_printf x ;               \
   } while (0)
#endif

#endif  /* whole file */
