#include <stdlib.h>
#include <stdio.h>
#include "depui.h"

static char caption[100];
static MxStaticText text;

typedef struct Keylist {
	 char *name;
	 UInt32 raw;
	 UInt32 expected;
} Keylist;

static int listiterator = 0;
static Keylist keylist[] = {
	 {"Enter", 0, 13,},
	 {"Space", 0, 32,},
	 {"Backspace", 0, 8,},
	 {"Tab", 0, 9,},

	 {"Up", 0, 0,},
	 {"Down", 0, 0,},
	 {"Left", 0, 0,},
	 {"Right", 0, 0,},

	 {"Insert", 0, 0,},
	 {"Delete", 0, 0,},
	 {"Home", 0, 0,},
	 {"End", 0, 0,},
	 {"Pageup", 0, 0,},
	 {"Pagedown", 0, 0,},

	 {0, 0, 0,}
};

static void *DesktopHandler(MxObject * object, const MxEvent * const event)
{
	 switch (event->type) {

		  /* Grab keys to the desktop and record them */
	 case MxEventHotkey:
	 case MxEventKeyChild:
	 case MxEventKeyUnbound:

		  /* Record the key */
		  keylist[listiterator].raw = event->key.raw;
		  ++listiterator;

		  /* Do the next key in the list */
		  if (keylist[listiterator].name) {

				/* Make a new caption */
				strcpy(caption, "Press ");
				strcat(caption, keylist[listiterator].name);
				printf("%s\n", caption);
				MxStaticTextCaption(&text, caption, MxFalse, strlen(caption), 0);
				MxEnqueueRefresh(&text.base.object);

				/* Are we done with the list, close the application */
		  } else {
				MxEvent event;

				event.type = MxEventExit;

				MxEnqueue(MxDesk, &event, 0);
		  }
		  break;

		  /* Otherwise behave just as a regular desktop */
	 default:
		  return MxDesktopHandler(object, event);
	 }
	 return 0;
}

/* main function */
int main(void)
{
	 MxStaticTextArgs textargs;

	 /* Create some drivers specific to the system */
	 MxDesktop desktop;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 if (!MxDesktopConstruct(&desktop, 320, 200, 8, &system, &output, &input, 0))
		  return 1;

	 MxDesk->handler = DesktopHandler;

	 /* Make a nice exit button */
	 MxExitButtonNew(MxDesk, 0, 0, MxDefault, MxDefault, 0);

	 /* Make the static text messages */
	 strcpy(caption, "Press ");
	 strcat(caption, keylist[0].name);
	 printf("%s\n", caption);

	 MxArgsInit(&textargs);
	 textargs.caption = caption;
	 textargs.len = strlen(caption);

	 MxStaticTextConstruct(&text, MxDesk, 10, 30, 150, 20, &textargs);

	 /* Run the message loop */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* Cleanup */
	 MxDesktopDestruct(&desktop);

	 /* Write the keydata out */
	 fprintf(stderr, "Keydata for DEPUI platform %s\n", MX_PLATFORM);
	 listiterator = 0;
	 while (keylist[listiterator].name) {

		  /* Is it a standard key, that we expect a code for */
		  if (keylist[listiterator].expected) {
				if (keylist[listiterator].raw != keylist[listiterator].expected)
					 fprintf(stderr, "\tif (*raw == %li)\n\t\t*code = %li;\n", keylist[listiterator].raw, keylist[listiterator].expected);

				/* Write the key translation table */
		  } else
				fprintf(stderr, "\t{ %8li, MxKey%-10s },\n", keylist[listiterator].raw, keylist[listiterator].name);

		  ++listiterator;
	 }
	 fprintf(stderr, "\t{ %8i, MxKey%-10s }\n\n", 0, "None");

	 return 0;
}
