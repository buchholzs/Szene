#include <stdlib.h>
#include <stdio.h>
#include "depui/depui.h"

static MxDesktop desktop;

static void second_main(MxObject * object, void *data, unsigned int selected)
{
	 MxButton button;

	 MxDesktop desktop;
	 MxDesktopArgs desktopargs;

	 (void) object;
	 (void) data;

	 if (!selected)
		  return;

	 MxArgsInit(&desktopargs);

	 desktopargs.desktop_w = 640;
	 desktopargs.desktop_h = 480;
	 desktopargs.desktop_c = 16;
	 desktopargs.system = 0;
	 desktopargs.output = 0;
	 desktopargs.input = 0;
	 desktopargs.window.caption = "recursive";

	 /* Initailize the library */
	 MxDesktopConstruct(&desktop, 100, 100, 100, 100, &desktopargs);
	 if (!&desktop.base.object)
		  return;

	 /* Make a nice exit button */
	 MxExitButtonConstruct(&button, &desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 /* Run the desktop until it wants to exit */
	 while (MxDesktopRun(&desktop)) {
	 };

	 /* Close and go home */
	 MxDestroy(&desktop.base.object);
}

static void desktop_exit(MxObject * object, void *data, unsigned int selected)
{
	 (void) object;
	 (void) data;
	 if (selected)
		  MxEventSendSimple(&desktop.base.object, MxEventExit);
}

static MxAlertArgs alertargs = { "Alert", "line1\nline2\nline3",
	 {"Ok", 0, MxFalse},
	 {"Cancel", 0, MxFalse},
	 {"Exit", desktop_exit, MxFalse}
};

MxWindow *w1, *w2;

static char filename[MX_MAX_PATH];

static void *DesktopHandler(MxObject * object, const MxEvent * const event)
{
	 /* Wait for an unused escape key */
	 if ((event->type == MxEventKeyUnbound)
		  && (event->key.code == 0x1b)) {

		  /* Make an event to force an exit */
		  MxEventSendSimple(&desktop.base.object, MxEventExit);
		  return object;

		  /* Test out the alert function */
	 } else if ((event->type == MxEventKeyUnbound)
					&& (event->key.code == 'a')) {

		  MxAlertStart(&alertargs, &w2->base.object);
		  return object;

		  /* Test out the fileselector function */
	 } else if ((event->type == MxEventKeyUnbound)
					&& (event->key.code == 'f')) {

		  /* Setup the file selector arguments */
		  MxFileselectorArgs args;

		  MxArgsInit(&args);
		  args.file = filename;
		  strcpy(filename, "");
		  args.pattern = "*.jpg;*.c;*.exe";
		  args.window.caption = "File Selector";

		  /* Start the file selector */
		  MxFileselectorStart(&args, 0, 0);
		  return object;
	 }

	 /* Otherwise behave just as a regular desktop */
	 return MxDesktopHandler(object, event);
}

/* The menu definition */
static MxMenuDef SubSubmenu1[] = {
	 {"SSub1", 0, 0, 0, 0, 0, 0, 0},
	 {"SSub2", 0, 0, 0, 0, 0, 0, 0},
	 {"SSub3", 0, 0, 0, 0, 0, 0, 0},
	 {"SSub4", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxMenuDef SubSubmenu2[] = {
	 {"gSub1", 0, 0, 0, 0, 0, 0, 0},
	 {"gSub2", 0, 0, 0, 0, 0, 0, 0},
	 {"gSub3", 0, 0, 0, 0, 0, 0, 0},
	 {"gSub4", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

char const *const MenuTearoff = "---";

static MxMenuDef Submenu1[] = {
	 {"Sub1", 0, SubSubmenu1, 0, 0, 0, 0, 0},
	 {"", 0, 0, 0, 0, 0, 0, 0},
	 {"Sub2", 0, SubSubmenu2, 0, 0, 0, 0, 0},
	 {"Sub3", 0, 0, 0, 0, 0, 0, 0},
	 {"Sub4", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxMenuDef Submenu2[] = {
	 {"Sjb1", 0, 0, 0, 0, 0, 0, 0},
	 {"Sjb2", 0, 0, 0, 0, 0, 0, 0},
	 {"Sjb3", 0, 0, 0, 0, 0, 0, 0},
	 {"Sjb4", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxMenuDef Menu1[] = {
	 {"Men1", 0, Submenu1, 0, 0, 0, 0, 0},
	 {"Men2", 0, Submenu2, 0, 0, 0, 0, 0},
	 {"Men3", 0, 0, 0, 0, 0, 0, 0},
	 {"Men4", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxListDef List1[] = {
	 {"List\telem0", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem1", 0, 0, 0, 0, 0, 0, 0},
	 {"", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem2", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem3", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem4", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem5", 0, 0, 0, 0, 0, 0, 0},
	 {"Listelem6", 0, 0, 0, MxTrue, 0, 0, 0},
	 {"Listelem7", 0, 0, MxTrue, MxTrue, 0, 0, 0},
	 {"Listelem8", 0, 0, MxTrue, 0, 0, 0, 0},
	 {"Listelem9", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
};

static MxListDef shortlist[] = {
	 {"Short0", 0, 0, 0, 0, 0, 0, 0},
	 {"Short1", 0, 0, 0, 0, 0, 0, 0},
	 {"Short2", 0, 0, 0, 0, 0, 0, 0},
	 {"Short3", 0, 0, 0, 0, 0, 0, 0},
	 {"Short4", 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
};

static const char *longstring = "My lodestars were blotted out; In that \
canopy of grim fire shone no star...\r\r\
The universe was one huge, dead, immeasurable steam engine, rolling on, \
in its dead indifference, to grind me limb from limb. And I asked myself, \
'What art thou afraid of ?'\n\n\
Wherefore like a coward, dost forever pip and \
whimper, and go cowering and whimpering.  Despicable Biped!  What is the \
sum-total of the worst that lies before thee?  Death?  Well, Death: and say \
to the pangs of Tophet too and all that the Devil and Man may, will or can \
do against thee!  Hast thou not a heart; canst thou not suffer whatso it be: \
and, as a child of freedom, though outcast, trample Tophet itself under thy \
feet, while it consumes thee?  Let it come, then: I will meet and defy it! \r\r\
 - Carlyle, Sartor Resartus.\n\n\n\n\n\
This part is only here to make the screenshot have a scrollbar";

/* main function */
int main(int argc, char *argv[])
{
	 MxWindowArgs winargs;

	 MxButton *b1, *b2, *b3;
	 MxButtonArgs btnargs;

	 MxSlider *s1, *s2;

	 MxMenu *menu;
	 MxMenuArgs menuargs;

	 MxStatictextArgs statictextargs;

	 /* Create some drivers specific to the system */
	 MxDesktopArgs desktopargs;
	 MxDriverSystem system = MxDriverSystemDefault;
	 MxDriverOutput output = MxDriverOutputDefault;
	 MxDriverInput input = MxDriverInputDefault;

	 MxDriverOutputBuffer buffered = MxDriverOutputDoublebuffer;

	 (void) argc;
	 (void) argv;

	 /* Construct some double buffering for the output */
	 MxDriverOutputBufferInit(&buffered, &output);

	 desktopargs.desktop_w = 640;
	 desktopargs.desktop_h = 480;
	 desktopargs.desktop_c = 16;
	 desktopargs.system = &system;
	 desktopargs.output = &output;
//    desktopargs.output = &buffered.output;
	 desktopargs.input = &input;

	 /* Initailize the library */
	 MxDesktopConstruct(&desktop, 10, 10, 100, 100, &desktopargs);
	 desktop.base.object.handler = DesktopHandler;
	 if (!desktop.ok)
		  return 1;

	 /* Set our own bacgground color */
//  MxColorDesktop = MxColorEncode(0, 127, 0, 0);

	 /* Make a nice exit button */
	 MxExitButtonNew(&desktop.base.object, 0, 0, MxDefault, MxDefault, 0);

	 MxArgsInit(&winargs);
	 winargs.caption = "Window is unmovable";
	 winargs.unmovable = MxTrue;
	 winargs.unresizeable = MxFalse;

	 w1 = MxWindowNew(&desktop.base.object, 50, 50, 260, 120, &winargs);

	 MxArgsInit(&btnargs);
	 btnargs.stext.caption = "Push";
	 btnargs.callback = second_main;
	 b1 = MxPushButtonNew(w1->client, 10, 10, MxDefault, MxDefault, &btnargs);

	 MxArgsInit(&statictextargs);
	 statictextargs.caption = "Statictext";
	 statictextargs.len = strlen(statictextargs.caption);
	 statictextargs.just = (MxStatictextJustify) (MxJustifyVCenter | MxJustifyHRight);
//  MxStatictextNew(w1->client, 70, 13, MxDefault, MxDefault, &statictextargs);
	 MxStatictextNew(w1->client, 70, 13, 100, 16, &statictextargs);

	 s1 = MxSliderVNew(w1->client, 10, 40, MxDefault, 100, 0);

	 /* Make a menu */
	 MxArgsInit(&menuargs);
	 menuargs.listarea.def = Menu1;

	 menu = MxMenuNew(0, 0, 0, MxDefault, MxDefault, &menuargs);

	 winargs.caption = "Window is unresizable";
	 winargs.unmovable = MxFalse;
	 winargs.unresizeable = MxTrue;
	 winargs.menu = menu;
	 w2 = MxWindowNew(&desktop.base.object, 65, 65, 210, 170, &winargs);
	 winargs.menu = 0;
//    MxHide(w2->base.object.hidden);

	 MxArgsInit(&btnargs);
	 btnargs.stext.caption = "Toggle";
	 btnargs.stext.just = (MxStatictextJustify) (MxJustifyVCenter | MxJustifyHRight);
	 btnargs.defaultbutton = MxTrue;
	 b2 = MxToggleButtonNew(w2->client, 10, 10, 85, 25, &btnargs);
	 btnargs.defaultbutton = MxFalse;

	 btnargs.stext.caption = "Check";
	 b3 = MxCheckboxNew(w2->client, 10, 38, MxDefault, MxDefault, &btnargs);

	 /* Create a radio group and radio buttons */
	 {
		  MxRadioGroupArgs radioargs;
		  MxRadioGroup *group;

		  MxArgsInit(&radioargs);
		  radioargs.caption = "Radio";

		  group = MxRadioGroupNew(w2->client, 10, 57, 85, 55, &radioargs);

		  /* Create the radio buttons */
		  btnargs.stext.caption = "Radio1";
		  MxRadioButtonNew(&group->base.object, 5, 12, MxDefault, MxDefault, &btnargs);

		  btnargs.stext.caption = "Radio2";
		  MxRadioButtonNew(&group->base.object, 5, 30, MxDefault, MxDefault, &btnargs);
	 }

	 {
		  MxListArgs listargs;

		  MxArgsInit(&listargs);

		  listargs.listarea.def = List1;
		  MxListNew(w1->client, 30, 30, 100, 91, &listargs);
	 }
//    MxAnimateNew(w1->client, 140, 60, 80, 124, 0);

	 s2 = MxSliderHNew(w2->client, 10, 120, 100, 10, 0);

	 /* Test the listarea */
	 {
		  MxList *scrolllist;
		  MxListArgs args;

		  MxArgsInit(&args);
		  args.listarea.def = shortlist;
//        args.listarea.border = 2;
//        args.listarea.multiple = MxTrue;

		  scrolllist = MxListNew(w2->client, 100, 10, 70, 100, &args);

//        MxListareaAppend(&scrolllist->listarea, &shortlist[0]);
//        MxListareaAppend(&scrolllist->listarea, &shortlist[1]);
//        MxListareaAppend(&scrolllist->listarea, &shortlist[2]);
//        MxListareaAppend(&scrolllist->listarea, &shortlist[3]);
	 }

	 MxBarNew(w2->client, 5, 5, 150, 100, 0);

	 if (1) {
		  MxScrollTextarea *text;
		  MxScrollTextareaArgs textargs;

		  MxArgsInit(&textargs);
		  textargs.textarea.caption = longstring;
		  textargs.textarea.endtest = MxLineEndWordwrap;
		  textargs.scroll.border = -1;

		  text = MxScrollTextareaNew(0, 0, 0, 300, 120, &textargs);

		  MxArgsInit(&winargs);
		  winargs.caption = "Window is uncloseable";
		  winargs.client = &text->base.object;
		  winargs.uncloseable = MxTrue;

		  MxWindowNew(&desktop.base.object, 150, 150, 300, 120, &winargs);
	 }
//  if (0)
	 {
		  MxEditorArgs edit;

		  MxArgsInit(&edit);
//    edit.scrledit.editarea.textarea.endtest = MxLineEndWordwrap;

//		  MxEditorNew(&desktop.base.object, 100, 100, 200, 200, &edit);
	 }

//    desktop.OpaqueMove = MxTrue;

	 while (MxDesktopRun(&desktop)) {
	 };

//  MxFontDestroy(font);

//    fprintf(stderr, "%s\n", edit->editbox.base.textbox.caption);

	 MxDestroy(&desktop.base.object);

	 fprintf(stderr, "Rect    size = %li\n", sizeof(MxRect));
	 fprintf(stderr, "Region  size = %li\n", sizeof(MxRegion));
	 fprintf(stderr, "Event   size = %li\n", sizeof(MxEvent));
	 fprintf(stderr, "Object  size = %li\n", sizeof(MxObject));
	 fprintf(stderr, "Button  size = %li\n", sizeof(MxButton));
	 fprintf(stderr, "StaticT size = %li\n", sizeof(MxStatictext));
	 fprintf(stderr, "Window  size = %li\n", sizeof(MxWindow));
	 fprintf(stderr, "Desktop size = %li\n", sizeof(MxDesktop));
	 fprintf(stderr, "Filesel size = %li\n", sizeof(MxFileselector));

	 fprintf(stderr, "File selected = %s\n", filename);

//    mx_font_dump(font, stdout, "normal");

	 return 0;
}
