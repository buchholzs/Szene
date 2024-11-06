#include "depui/config.h"
#include "depui/desktop/desktop.h"
#include "depui/object/window.h"
#include "depui/event/focus.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void MxFocusSet(MxObject * object)
{
	 /* Has the object changed */
	 if (Mx.focus != object) {

		  MxObject *old = Mx.focus;
		  MxObject *parent = (object) ? MxParent(object) : 0;

		  /* Inform the new object that they got the focus */
		  if (object)
				MxEventSendSimple(object, MxEventFocusGot);
		  Mx.focus = object;

		  /* Inform the parents that the focus has changed */
		  while (parent) {
				MxEventSendObject(parent, MxEventFocusChild, object);
				parent = MxParent(parent);
		  }

		  /* Inform the old object that they lost the focus */
		  if (old)
				MxEventSendSimple(old, MxEventFocusLost);
	 }
}

MxObject *MxFocus(void)
{
	 return Mx.focus;
}

void MxActiveSet(MxObject * object, void *lock)
{
	 /* Are we forbidden to change the active object */
	 if ((Mx.activelock) && (Mx.activelock != lock))
		  return;

	 /* The desktop can never actually be active */
	 if (object == mx_desk)
		  object = 0;

	 /* Has the object changed */
	 if (Mx.active != object) {

		  MxObject *old = Mx.active;

		  /* Inform the new object that they got the active */
		  if (object)
				MxEventSendSimple(object, MxEventActiveGot);
		  Mx.active = object;
		  Mx.activelock = lock;

		  /* Inform the old object that they lost the active */
		  if (old)
				MxEventSendSimple(old, MxEventActiveLost);

		  /* Is the active window has been changed, we lose the focus */
		  MxFocusSet(0);
	 }

	 /* Maybe move the object to the front */
	 if (object)
		  MxZOrderDraw(object, 0);
}

MxObject *MxActive(void)
{
	 return Mx.active;
}
