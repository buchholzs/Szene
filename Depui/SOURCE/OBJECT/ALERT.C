#include "depui/config.h"
#include "depui/types.h"
#include "depui/args/args.h"
#include "depui/draw/draw.h"
#include "depui/object/alert.h"
#include "depui/object/button.h"
#include "depui/object/defsize.h"
#include "depui/desktop/desktop.h"
#include "depui/desktop/driver.h"
#include "depui/geometry/geometry.h"

#ifdef MX_DEBUG_MODULES
static const char *mx_link_flag = "MxModule" __FILE__;
#endif

void *MxAlertHandler(MxObject * object, const MxEvent * const event)
{
	 MxAlert *alert = (MxAlert *) object;

	 MX_TRACE(event_name[event->type]);
	 MX_CHECKSTACK(object);

	 switch (event->type) {

	 case MxEventPreInit:{
				int y;
				int x = 2;

				int tw = 0, th = 0;

				/* Position the textbox */
				MxGeomPosition(&alert->textbox.base.object, 2, 2);
				MxGeomQuery(&alert->textbox.base.object, 0, 0, &tw, &th, (MxGeomFlags) (MxGeomW | MxGeomH));
				MxGeomSize(&alert->textbox.base.object, tw, th);

				y = MxY2(&alert->textbox.base.object);

				/* Position the buttons */
				if (alert->button1) {
					 MxGeomPosition(&alert->button1->base.object, x, y + 2);
					 x += MxW(&alert->button1->base.object) + 2;
				}

				if (alert->button2) {
					 MxGeomPosition(&alert->button2->base.object, x, y + 2);
					 x += MxW(&alert->button2->base.object) + 2;
				}

				if (alert->button3)
					 MxGeomPosition(&alert->button3->base.object, x, y + 2);
				break;
		  }

	 case MxEventPostInit:{
				int x2 = MxMaxChildX2(alert->base.window.client);
				int y2 = MxMaxChildY2(alert->base.window.client);
				const int hoff = alert->base.window.unresizeable ? 0 : 5;
				const int barheight = (alert->base.window.menu) ? MxH(&alert->base.window.menu->base.object) + 1 : 0;

				const int title_height = barheight + MxFontHeight(MxFontDefault) + 2;

				/* Change the window size to fit the client stuff */
				MxGeomSize(object, x2 + 4, title_height + y2 + 4 + hoff);
				MxEventSendSimple(object, MxEventGeomChanged);
				break;
		  }

	 default:
		  break;
	 }
	 /* Act like a normal window */
	 return MxWindowHandler(object, event);
}

static MxButton *create_button(const MxAlertButtonArgs * const args, MxObject * parent)
{
	 MxButton *ret = 0;
	 MxButtonArgs buttonargs;

	 MxArgsInit(&buttonargs);

	 if (args->caption) {
		  buttonargs.stext.caption = args->caption;
		  buttonargs.defaultbutton = args->defaultbutton;
		  buttonargs.callback = args->callback;

		  ret = MxExitButtonNew(parent, 0, 0, MxDefault, MxDefault, &buttonargs);
	 }

	 return ret;
}

MxAlert *MxAlertStart(const MxAlertArgs * const args, MxObject * blocked)
{
	 /* Create and construct an object to show that we are dragging and
	    dropping */
	 MxAlert *alert = (MxAlert *) MxMalloc(sizeof(MxAlert));

	 assert(args);

	 if (alert) {
		  MxWindowArgs windowargs;
		  MxTextareaArgs textboxargs;

		  memset(alert, 0, sizeof(MxAlert));

		  /* Create the underlying window */
		  MxArgsInit(&windowargs);
		  windowargs.caption = args->caption;
		  windowargs.unresizeable = MxTrue;
		  windowargs.centered = MxTrue;

		  /* Make the underlying window to be modal */
		  windowargs.modal = MxTrue;
		  windowargs.blocked = blocked;

		  /* Construct the underlying window */
		  MxWindowConstruct(&alert->base.window, 0, 0, 0, 0, 0, &windowargs);
		  alert->base.object.handler = MxAlertHandler;

		  /* Remember that the memory has to be deleted at some point */
		  alert->base.object.allocated = MxTrue;
#ifdef MX_WINDOW_NAMES
		  alert->base.object.name = "MxAlert";
#endif

		  /* Create the internal textbox */
		  MxArgsInit(&textboxargs);
		  textboxargs.caption = args->message;
		  textboxargs.basecolor = MxTrue;

		  MxTextareaConstruct(&alert->textbox, alert->base.window.client, 0, 0, 0, 0, &textboxargs);

		  /* Create the buttons */
		  alert->button1 = create_button(&args->button1, alert->base.window.client);
		  alert->button2 = create_button(&args->button2, alert->base.window.client);
		  alert->button3 = create_button(&args->button3, alert->base.window.client);

		  /* Start the object running */
		  MxInsert(&alert->base.object, mx_desk, MxTrue);

		  /* Tell the user what alert was made */
		  return alert;
	 }
	 /* We were unsuccessful in making an alert box */
	 return 0;
}
