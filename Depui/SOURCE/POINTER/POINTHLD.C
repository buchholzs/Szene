#include "depui/config.h"
#include "depui/pointer/pointer.h"
#include "depui/desktop/desktop.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxPointerGrab(MxObject * const object)
{
#ifdef MX_DEBUG_EVENT
	 fprintf(mx_stream, "Grabbing pointer %s [%p]\n", object->name, object);
	 fflush(mx_stream);
#endif

	 Mx.pointer = object;
	 Mx.wantmove = MxFalse;
	 Mx.hold_pointer = MxTrue;
}

void MxPointerRelease(void)
{
#ifdef MX_DEBUG_EVENT
	 fprintf(mx_stream, "Releasing pointer\n");
	 fflush(mx_stream);
#endif

	 Mx.pointer = 0;
	 Mx.wantmove = MxFalse;
	 Mx.hold_pointer = MxFalse;

	 /* Find the the new pointer object */
	 mx_handle_pointer();

#ifdef MX_DEBUG_EVENT
	 if (Mx.pointer)
		  fprintf(mx_stream, "New pointer object is %s [%p]\n", Mx.pointer->name, Mx.pointer);
	 else
		  fprintf(mx_stream, "New pointer object is 0\n");

	 fflush(mx_stream);
#endif

}
