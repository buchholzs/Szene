#ifndef MX_ARGS_ARGS_H
#define MX_ARGS_ARGS_H

#include "depui/config.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
#define MxUserArgsInit(realargs, args)           \
   do {                                          \
      if (args)                                  \
         realargs = *args;                       \
      else                                       \
         memset(&realargs, 0, sizeof(realargs)); \
   } while (0)
#define MxArgsInit(realargs)                     \
   do {                                          \
      memset(realargs, 0, sizeof(*realargs));    \
   } while (0)
#ifdef __cplusplus
}
#endif
#endif
