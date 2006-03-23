#include "depui/config.h"
#include "depui/debug/alloc.h"
#include "depui/object/listdef.h"
#include <string.h>

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

/* Count the number of elements in a given list definition */
static unsigned int count(const MxListDef * def)
{
	 int i = 0;

	 while ((def) && (def->caption))
		  ++i, ++def;

	 return i;
}

MxListDef *MxListDefAppend(MxListDef * list, const MxListDef * const def)
{
	 MxListDef zero;

	 /* We always have a NULL caption at the end of the listdef */
	 const unsigned int numdef = count(list);
	 const unsigned int defsize = (numdef + 2) * sizeof(MxListDef);

	 MxListDef *temp = (MxListDef *) MxMalloc(defsize);

/*    assert(list); This works properly even if list == NULL */
	 assert(def);

	 /* Fixup the temporary copy */
	 if (numdef)
		  memcpy(temp, list, numdef * sizeof(MxListDef));
	 temp[numdef] = *def;

	 /* Put the zero terminator up */
	 memset(&zero, 0, sizeof(MxListDef));
	 temp[numdef + 1] = zero;

	 return temp;
}

unsigned int MxListDefRemove(MxListDef * list, const MxListDef * const def)
{
	 unsigned int i;
	 unsigned int found = MxFalse;
	 const unsigned int numdef = count(list);

	 /* Move the higher elements down */
	 for (i = 0; i < numdef; i++) {
		  if ((&list[i] == def) || (found)) {
				list[i] = list[i + 1];
				found = MxTrue;
		  }
	 }
	 return found;
}
