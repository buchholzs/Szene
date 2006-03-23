#include "depui/config.h"
#include "depui/object/direct.h"
#include "depui/args/args.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxDirectAccessHandler(MxObject * object, const MxEvent * const event)
{
	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventZOrderRequest:
		  /* Don't let other objects in front */
		  if (MxIndex(object) < MxIndex(event->object.object))
				return object;
		  break;

	 case MxEventZOrderInform:
		  MxZOrder(object, 0);
		  break;

	 default:
		  break;
	 }
	 return 0;
}

void MxDirectAccessConstruct(MxDirectAccess * access, MxObject * parent, int x, int y, int w, int h, MxDirectAccessArgs * userargs)
{
	 MxDirectAccessArgs args;

	 assert(access);
	 MxUserArgsInit(args, userargs);

	 memset(access, 0, sizeof(MxDirectAccess));
	 MxObjectConstruct(access, parent, x, y, w, h, &args);
	 access->handler = MxDirectAccessHandler;

#ifdef MX_WINDOW_NAMES
	 access->name = "MxDirectAccess";
#endif
}

MxDirectAccess *MxDirectAccessNew(MxObject * parent, int x, int y, int w, int h, MxDirectAccessArgs * args)
{
	 return (MxDirectAccess *) MxNewObject(sizeof(MxDirectAccess), (MxVoidFunc)
														MxDirectAccessConstruct, parent, x, y, w, h, args);
}
