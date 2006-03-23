#include "depui/config.h"
#include "depui/macros.h"
#include "depui/desktop/driver.h"
#include "depui/desktop/desktop.h"
#include "depui/draw/draw.h"
#include "depui/event/queue.h"
#include "depui/pointer/pointer.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

static MxObject *keyboard_base(void)
{
	 return Mx.active ? Mx.active : mx_desk;
}

static unsigned int blocked(MxObject * object)
{
	 if ((object->blocked) && (object != mx_desk))
		  return MxTrue;

	 return MxFalse;
}

static void object_xy(MxObject * object, int x, int y, MxObject ** const ret)
{
	 assert(object);
	 assert(ret);

	 MX_CHECKSTACK(object);

	 /* Is it an object that cannot get the the point */
	 if ((!MX_POINT_IN_RECT(object->position, x, y)) || (object->hidden)
		  || (blocked(object)))
		  return;

	 /* Does the object visible region cover this point */
	 MxVisible(object);
	 if (MxRegionContainsPoint(&object->region, x, y))
		  *ret = object;

	 /* Check the children also */
	 for (object = MxLastChild(object); object; object = MxPrev(object))
		  object_xy(object, x, y, ret);
}

MxObject *MxObjectXY(int x, int y)
{
	 MxObject *ret = mx_desk;

	 object_xy(mx_desk, x, y, &ret);
	 return ret;
}

static void *key_propagate(MxObject * object, const MxEvent * const key)
{
	 void *ret;

	 /* Maybe the object has been blocked by a modal window */
	 if (blocked(object))
		  return 0;

	 /* Does the object want the key */
	 ret = MxEventSend(object, key);
	 if (ret)
		  return ret;

	 /* Maybe stop propagating */
	 if (!object->KeyProp)
		  return 0;

	 /* Check the children */
	 object = MxFirstChild(object);
	 while (object) {

		  /* Do they want the key */
		  ret = key_propagate(object, key);
		  if (ret)
				return ret;

		  /* Try the next child */
		  object = MxNext(object);
	 }
	 return 0;
}

static void handle_keypress(unsigned int raw, MxKey key, unsigned int code)
{
	 void *ret = 0;

	 MxEvent event;

	 event.type = MxEventKey;
	 event.key.raw = raw;
	 event.key.key = key;
	 event.key.code = code;

	 /* Send it to the keyboard object */
	 if (Mx.focus)
		  ret = MxEventSend(Mx.focus, &event);

	 /* Whether the key was used or not, we pass it up the parents */
	 if (Mx.focus) {
		  MxObject *parent = MxParent(Mx.focus);
		  void *parentret = 0;

		  event.type = MxEventKeyChild;

		  while ((parent) &&		  /* We still have a parent */
					(!parentret)) {  /* The parent hasn't used the key */

				/* Send the key to the parent */
				parentret = MxEventSend(parent, &event);

				/* Don't go past our keyboard base */
				if (parent == keyboard_base())
					 break;

				parent = MxParent(parent);
		  }
	 }

	 /* Maybe this was a hotkey of the object */
	 event.type = MxEventHotkey;
	 if ((!ret) && (Mx.focus)) {

		  /* If space or enter was ignored, sent hotkey */
		  if ((event.key.code == ' ') || (event.key.code == 0x0d))
				ret = MxEventSend(Mx.focus, &event);
	 }

	 /* Don't know who to send it to, so send it to the keyboard base as
	    unbound */
	 event.type = MxEventKeyUnbound;
	 if ((!ret) && (keyboard_base()))
		  ret = key_propagate(keyboard_base(), &event);
}

static void handle_button(int x, int y, MxEventType object, MxEventType child, unsigned int pressed)
{
	 MxEvent event;

	 event.point.x = x;
	 event.point.y = y;

	 /* Send the press to an object */
	 if (Mx.pointer) {

		  MxObject *parent;

		  /* Do we destroy any popup objects */
		  if ((pressed) && (Mx.desktop->base.object.popup) && (!Mx.pointer->popup))
				MxPopupClean();

		  /* Send the actual click */
		  event.type = object;
		  MxEventSend(Mx.pointer, &event);

		  /* Tell the object that it was clicked */
		  if (Mx.pointer) {

				if (pressed)
					 Mx.pointer->clicked = MxTrue;

				/* Send the message up to the parent */
				event.type = child;

				parent = MxParent(Mx.pointer);
				while (parent) {

					 MxEventSend(parent, &event);
					 parent = MxParent(parent);
				}
		  }
	 }
}

static void pointer_changed(MxObject * next, int x, int y)
{
	 MxEvent event;

	 event.point.x = x;
	 event.point.y = y;

	 /* Tell the old object that we left */
	 if (Mx.pointer) {

		  /* Tell the object that the pointer left */
		  event.type = MxEventPointerLeave;
		  MxEventSend(Mx.pointer, &event);

		  if (next)
				next->clicked = MxFalse;
	 }

	 /* Maybe the object has grabbed the pointer, so we must enter that object 
	    with the pointer */
	 if ((next) && (Mx.hold_pointer))
		  next = Mx.pointer;

	 /* Tell the new object that we entered */
	 Mx.pointer = next;

	 /* Give the mouse to the next object */
	 if (next) {
		  next->clicked = MxFalse;
		  event.type = MxEventPointerEnter;
		  MxEventSend(next, &event);
	 }
}

static void handle_pointer(const int x, const int y)
{
	 /* Maybe change the dialogs pointer object */
	 if (!Mx.hold_pointer) {

		  /* Find out what object has the mouse now */
		  MxObject *prev = Mx.pointer;
		  MxObject *next = MxObjectXY(x, y);

		  /* Maybe we moved out of the last object */
		  if (next != prev)
				pointer_changed(next, x, y);
	 }

	 /* Tell the object that we have moved and that there is valid movement */
	 if (Mx.wantmove) {
		  MxEvent event;

		  event.type = MxEventPointerMove;
		  event.point.x = x;
		  event.point.y = y;

		  MxEventSend(Mx.pointer, &event);
	 }
}

void mx_handle_pointer(void)
{
	 handle_pointer(Mx.mouse_x, Mx.mouse_y);
}

static void handle_messages(int *idle)
{
	 ++Mx.running;

	 /* Get mouse input */
	 if (mx_input->Mouse)
		  mx_input->Mouse(&Mx.mouse_x, &Mx.mouse_y, &Mx.mouse_b);

	 /* Mouse moved */
	 if ((Mx.mouse_x != Mx.old_mouse_x)
		  || (Mx.mouse_y != Mx.old_mouse_y)) {

		  *idle = 0;
		  handle_pointer(Mx.mouse_x, Mx.mouse_y);
	 }

	 /* Handle mouse buttons */
	 if ((Mx.mouse_b != Mx.old_mouse_b) && (Mx.pointer)) {

		  *idle = 0;

		  /* Some mouse button pressed */
		  if ((Mx.mouse_b & 0x01) && (!(Mx.old_mouse_b & 0x01)))
				handle_button(Mx.mouse_x, Mx.mouse_y, MxEventButtonLeftPress, MxEventButtonLeftPressChild, MxTrue);

		  if ((Mx.mouse_b & 0x02) && (!(Mx.old_mouse_b & 0x02)))
				handle_button(Mx.mouse_x, Mx.mouse_y, MxEventButtonRightPress, MxEventButtonRightPressChild, MxTrue);

		  if ((Mx.mouse_b & 0x04) && (!(Mx.old_mouse_b & 0x04)))
				handle_button(Mx.mouse_x, Mx.mouse_y, MxEventButtonCenterPress, MxEventButtonCenterPressChild, MxTrue);

		  if ((!(Mx.mouse_b & 0x01)) && (Mx.old_mouse_b & 0x01))
				handle_button(Mx.mouse_x, Mx.mouse_y, MxEventButtonLeftRelease, MxEventButtonLeftReleaseChild, MxFalse);

		  if ((!(Mx.mouse_b & 0x02)) && (Mx.old_mouse_b & 0x02))
				handle_button(Mx.mouse_x, Mx.mouse_y, MxEventButtonRightRelease, MxEventButtonRightReleaseChild, MxFalse);

		  if ((!(Mx.mouse_b & 0x04)) && (Mx.old_mouse_b & 0x04))
				handle_button(Mx.mouse_x, Mx.mouse_y, MxEventButtonCenterRelease, MxEventButtonCenterReleaseChild, MxFalse);
	 }

	 /* handle keypresses */
	 if (mx_input->KeyPressed()) {
		  MxKey key;
		  unsigned int code;
		  unsigned int raw;

		  *idle = 0;

		  mx_input->ReadKey(&raw, &key, &code);

		  /* Handle a normal keypress */
		  handle_keypress(raw, key, code);
	 }

	 /* store I/O values */
	 Mx.old_mouse_x = Mx.mouse_x;
	 Mx.old_mouse_y = Mx.mouse_y;
	 Mx.old_mouse_b = Mx.mouse_b;

	 --Mx.running;
}

unsigned int MxDesktopRun(MxDesktop * desktop)
{
	 int idle = 1;

	 (void) desktop;

	 ++Mx.running;

	 /* If dialog is not drawn then initialise and render it */
	 if (!mx_desk->init) {
		  mx_object_init(mx_desk);
		  idle = 0;
	 }

	 /* Check for messages from the dialog */
	 handle_messages(&idle);

	 /* Send any messages that have been waiting */
	 if ((idle) && (!MxEventQueueEmpty())) {

		  /* Send all the events that were in the queue */
		  MxEventQueueDispatch();
		  idle = 0;
	 }

	 /* Tell the platform that we are doing nothing interesting */
	 if ((idle) && (Mx.running == 1)) {

		  ++Mx.idle_count;
		  if (Mx.idle_count > MX_IDLE_TO_YIELD) {
				if (mx_system->Yield)
					 mx_system->Yield();

				Mx.idle_count = 0;

				/* Flush the output if we need to */
				if (Mx.needflush) {
					 if (mx_output->Flush)
						  mx_output->Flush();

					 Mx.needflush = MxFalse;
				}
		  }
	 }

	 /* If we are not idle, reset the idle count */
	 if (!idle)
		  Mx.idle_count = 0;
	 --Mx.running;

	 return (Mx.exiting) ? MxFalse : MxTrue;
}

void mx_forget_object(MxObject * object)
{
	 assert(object);

	 if (object == mx_desk)
		  return;

	 if (Mx.pointer == object) {
		  Mx.pointer = 0;
		  Mx.wantmove = MxFalse;
		  Mx.hold_pointer = MxFalse;
	 }

	 if (Mx.focus == object)
		  Mx.focus = 0;

	 if (Mx.active == object) {
		  Mx.active = 0;
		  Mx.activelock = 0;
	 }

	 if (Mx.droptarget == object)
		  Mx.droptarget = 0;

	 MxEventQueuePurge(object);

	 /* Forget any children also */
	 for (object = MxLastChild(object); object; object = MxPrev(object))
		  mx_forget_object(object);
}
