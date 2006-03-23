#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/object.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

typedef MxObject *(*CONSTRUCTOR) (void *memory, MxObject * parent, int x, int y, int w, int h, MxObjectArgs * args);

MxObject *MxNewObject(unsigned int size, MxVoidFunc construct, MxObject * parent, int x, int y, int w, int h, MxObjectArgs * args)
{
	 CONSTRUCTOR do_construct = (CONSTRUCTOR) construct;

	 MxObject *ret = (MxObject *) MxMalloc(size);

	 assert(do_construct);
	 assert(ret);

	 MX_TRACE("");

	 if (ret) {
		  memset(ret, 0, size);
		  do_construct(ret, parent, x, y, w, h, args);
		  ret->allocated = MxTrue;
	 }

	 return ret;
}
