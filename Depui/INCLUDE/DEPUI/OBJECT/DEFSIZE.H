#ifndef MX_OBJECT_DEFSIZE_H
#define MX_OBJECT_DEFSIZE_H

#include "depui/config.h"
#include <stdlib.h>
#ifdef _MSC_VER
#include <limits.h>
#define MAXINT INT_MAX
#else
#include <values.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#define MxDefault  (-MAXINT)
	 void MxDefaultSize(int *w, int *h, int defw, int defh);

#ifdef __cplusplus
}
#endif
#endif
