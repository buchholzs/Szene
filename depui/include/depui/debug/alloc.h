#ifndef MX_DEBUG_ALLOC_H
#define MX_DEBUG_ALLOC_H

#include "depui/config.h"

#ifdef __cplusplus
extern "C" {
#endif
/* Allocation defines for memory debugging */
#ifdef MX_DEBUG_MEM
#define MxMalloc(A) _MxMalloc(A,__FILE__,__LINE__)
#define MxRealloc(A,B) _MxRealloc((A),(B),__FILE__,__LINE__)
#define MxFree(A) _MxFree(A,__FILE__,__LINE__)
#define MX_CHECKSTACK(A) _MxCheckStack((void*)&(A),__FILE__,__LINE__)
	 void *_MxMalloc(unsigned int bytes, const char *file, const int line);
	 void *_MxRealloc(void *mem, unsigned int bytes, const char *file, const int line);
	 void _MxFree(void *mem, const char *file, const int line);

	 extern void *_mx_stack_base;
	 extern void *_mx_highest_stack;
	 void _MxCheckStack(void *ptr, const char *file, const int line);

/* Allocation defines for NO memory debugging */
#else
#include <stdlib.h>
#define MxMalloc(A) malloc(A)
#define MxRealloc(A,B) realloc((A),(B))
#define MxFree(A) free(A)
#define MX_CHECKSTACK(A)
#endif
#ifdef __cplusplus
}
#endif
#endif
