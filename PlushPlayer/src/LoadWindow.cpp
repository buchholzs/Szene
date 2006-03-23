#include "LoadWindow.h"

void *LoadWindowHandler(MxObject * object, const MxEvent * const event)
{
	 LoadWindow *stext = (LoadWindow *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 default:
		  return MxWindowHandler(object, event);
	 }
	 return 0;
}

void LoadWindowConstruct(LoadWindow * stext, MxObject * parent, int x, int y, int w, int h, LoadWindowArgs * userargs)
{

}

LoadWindow *LoadWindowNew(MxObject * parent, int x, int y, int w, int h, LoadWindowArgs * args)
{
	 return (LoadWindow *) MxNewObject(sizeof(LoadWindow), (MxVoidFunc) LoadWindowConstruct, parent, x, y, w, h, &args->object);
}
