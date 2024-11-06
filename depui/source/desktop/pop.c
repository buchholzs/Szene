#include "depui/config.h"
#include "depui/desktop/desktop.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxPopupClean(void)
{
	 MxObject *ptr = MxFirstChild(mx_desk);

	 /* Destroy popup objects */
	 while (ptr) {
		  MxObject *next = MxNext(ptr);

		  if (ptr->popup)
				MxDestroy(ptr);

		  ptr = next;
	 }

	 /* We don't need to destroy them again */
	 mx_desk->popup = MxFalse;
}
