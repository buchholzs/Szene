#ifndef MX_OBJECT_ALERT_H
#define MX_OBJECT_ALERT_H

#include "depui/config.h"
#include "depui/object/window.h"
#include "depui/object/text.h"
#include "depui/object/button.h"

#ifdef __cplusplus
extern "C" {
#endif
	 typedef struct MxAlert {
		  union {
				MxObject object;
				MxWindow window;
		  } base;

		  MxTextarea textbox;

		  MxButton *button1;
		  MxButton *button2;
		  MxButton *button3;

	 } MxAlert;

	 typedef struct MxAlertButtonArgs {

		  const char *caption;
		  MxCallback callback;
		  unsigned int defaultbutton:1;

	 } MxAlertButtonArgs;

	 typedef struct MxAlertArgs {

		  const char *caption;
		  const char *message;
		  MxAlertButtonArgs button1;
		  MxAlertButtonArgs button2;
		  MxAlertButtonArgs button3;

	 } MxAlertArgs;

	 void *MxAlertHandler(MxObject * object, const MxEvent * const event);

	 MxAlert *MxAlertStart(const MxAlertArgs * const args, MxObject * blocked);

#ifdef __cplusplus
}
#endif
/* Make a nice C++ interface */
#ifdef __cplusplus
typedef MxpArgs < MxAlertArgs > MxpAlertArgs;

#endif

#endif
