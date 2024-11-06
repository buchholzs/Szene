#include "depui/config.h"
#include "depui/event/event.h"
#include "depui/object/object.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxEventSendToChildren(const MxObject * const object, const MxEvent * event, const MxObject * const skip)
{
	 void *ret = 0;
	 MxObject *child;

	 for (child = MxFirstChild(object); child; child = MxNext(child)) {

		  if (child != skip)
				ret = MxEventSend(child, event);

		  if (ret)
				return ret;
	 }
	 return ret;
}

void *MxEventSendSimpleToChildren(const MxObject * const object, const MxEventType type, const MxObject * const skip)
{
	 MxEvent event;

	 event.type = type;

	 return MxEventSendToChildren(object, &event, skip);
}
