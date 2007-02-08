// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.


#include "Controller.h"

#include "depui/depui.h"
#include "Scene.h"
#include "SceneDesktop.h"
#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

namespace scene {

static void *fileOpenOKSelectedHandler(struct MxObject * object, const MxEvent * const event);

// ------------------------------------------------------------
Controller::Controller (MoveMode *moveMode, Scene *scene) :
	moveMode_(moveMode),
	scene_(scene)
{
}

// ------------------------------------------------------------
Controller::~Controller ()
{
}

// ------------------------------------------------------------
void Controller::loadScene (SceneDesktop *desktop)
{
  /* text for filename */
  MxStatictextArgs textargs;
  MxArgsInit(&textargs);
  textargs.caption = (const char *)MxMalloc(MX_MAX_PATH);
  textargs.len = 0;
  textargs.ownscaption = 1;
  MxStatictext *okSel = MxStatictextNew(&desktop->base.object, 0, 0, 0, 0, &textargs);
  okSel->base.object.handler = fileOpenOKSelectedHandler;
  MxHide(&okSel->base.object, MxTrue);

  /* Setup the file selector arguments */
  MxFileselectorArgs args;

  MxArgsInit(&args);
  args.file = (char *)textargs.caption;
  strcpy(args.file, "");
  args.pattern = "*.SCX;*.scx";
  args.attrib = FA_RDONLY | FA_DIREC;
  args.window.caption = "Load scene";

  /* Start the file selector */
  MxFileselector *fs = MxFileselectorStart(&args, &desktop->base.object, &okSel->base.object);
  return;
}

// File | Open Filedialog OK selected
static void *fileOpenOKSelectedHandler(struct MxObject * object, const MxEvent * const event) {
  MxStatictext *okSel	= (MxStatictext *)object;
  SceneDesktop *desktop = (SceneDesktop *)MxParent(&okSel->base.object);
  switch (event->type) {
  case MxEventOk: 
	  {
		// change dir
#ifdef WIN32
		char *lbs = strrchr(okSel->caption, '/');
		if (lbs != NULL) {
			  *lbs='\0';
		}
		char *newDir= lbs == NULL ? NULL : strdup(okSel->caption);
		const char *fileName = lbs == NULL ? okSel->caption : ++lbs;
#else
		char *newDir = dirname(okSel->caption);
		const char *fileName = basename(okSel->caption);
#endif
		if (newDir != NULL) {
		  chdir(newDir);
		  free(newDir);
		}
		loadScene(desktop, fileName);
		MxDestroy(object);	// destroy okSel
	  }
	break;
  default:
	return MxStatictextHandler(object, event);
  }
  return 0;
}

// ------------------------------------------------------------
} // Controller
