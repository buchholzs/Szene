// Copyright (c) 2006,2010 Steffen Buchholz


#include "Controller.h"

#include <sstream>
#include <algorithm>
#include <chrono>
#include <depui/depui.h>
#include "Scene.h"
#include "SceneDesktop.h"
#include "Hud.h"
#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#include <libgen.h>
#endif

namespace scene {

static void *fileOpenOKSelectedHandler(struct MxObject * object, const MxEvent * const event);
static void *helpHandler(struct MxObject * object, const MxEvent * const event);
static void callback_exit(MxObject * menu, void *data, unsigned int selected);

//////////////////////////////////////////////////////////////////////////////
// Constants and static variables
//
const int CFixColors = 16;	// Readonly colors
static MxMenuDef helpmenu[] = {
	 {"Exit", callback_exit, 0, 0, 0, 0, 0, 0}
	 ,
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

// ------------------------------------------------------------
// Callbacks
// ------------------------------------------------------------

// Key help | Exit menu selected
static void callback_exit(MxObject * menu, void *data, unsigned int selected)
{
	 (void) data;
	SceneDesktop *desktop = (SceneDesktop *)MxParent(menu->parent);
	setDirectDisplay(desktop, true);
	MxEnqueueSimple(menu->parent, MxEventExit, 0);
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
		char *lbs = strrchr((char *)okSel->caption, '/');
		if (lbs != NULL) {
			  *lbs='\0';
		}
		char *newDir= lbs == NULL ? NULL : strdup(okSel->caption);
		const char * newFile = lbs == NULL ? okSel->caption : ++lbs;
#else
		char *fileName = strdup((char *)okSel->caption);
		char *pathcopy = strdup((char *)okSel->caption);
		const char *newFile = basename(fileName);
		const char *newDir = dirname(pathcopy);
#endif
		if (newDir != NULL) {
		  int res = chdir(newDir);
		  if (res != 0) {
			std::string error = "Cannot change to directory " + std::string(newDir);
			desktop->controller->handleError(error);
		  }
		}
		desktop->controller->loadScene(newFile);
#ifndef WIN32
		free(fileName);
		free(pathcopy);
#endif
	  }
	break;
  default:
	return MxStatictextHandler(object, event);
  }
  return 0;
}

static void *helpHandler(struct MxObject * object, const MxEvent * const event) {
  MxWindow *win	= (MxWindow *)object;
  SceneDesktop *desktop = (SceneDesktop *)MxParent(&win->base.object);
  switch (event->type) {
  case MxEventExit:
	  {
		setDirectDisplay(desktop, true);
		MxWindowHandler(object, event);
	  }
	break;
  default:
	  return MxWindowHandler(object, event);
  }
  return 0;
}
// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Controller::Controller (std::shared_ptr<MoveMode> moveMode, std::shared_ptr<Scene> scene, SceneDesktop *desktop) :
	moveMode_(moveMode),
	scene_(scene),
	filename_(""),
	desktop_(desktop)
{
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Controller::~Controller ()
{
}

void Controller::setPause(bool pause)
{
	scene_->setPause(pause);
}

bool Controller::getPause()
{
	return scene_->getPause();
}

// ------------------------------------------------------------
// Show a file selector
// ------------------------------------------------------------
void Controller::openScene ()
{
  /* text for filename */
  MxStatictextArgs textargs;
  MxArgsInit(&textargs);
  textargs.caption = (const char *)MxMalloc(MX_MAX_PATH);
  assert(textargs.caption);
  *(char*)textargs.caption = '\0';
  textargs.len = 0;
  textargs.ownscaption = 1;
  MxStatictext *okSel = MxStatictextNew(&desktop_->base.object, 0, 0, 50, 50, &textargs);
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
  MxFileselector *fs = MxFileselectorStart(&args, &desktop_->base.object, &okSel->base.object);
  resizeFileSelector(fs);
  return;
}

// ------------------------------------------------------------
// Loads the scene file and reloads the palette
// ------------------------------------------------------------
void Controller::loadScene (const std::string &filename)
{
  try {
    desktop_->scn->loadXML(filename);
#ifdef DEBUG	
	desktop_->scn->dump();
#endif
	moveMode_->setMoveSpeed(desktop_->scn->getMoveSpeed());
	moveMode_->setTurnSpeed(desktop_->scn->getTurnSpeed());
    filename_ = filename;
	scene_->reloadPalette();
	Scene::ActionMap *am = scene_->getAllActions();

    strcpy(desktop_->lastmessage, (std::string(filename) + " loaded.").c_str());
	desktop_->hud->setStatus(desktop_->lastmessage);

	// reset time
	desktop_->prevtime = std::chrono::system_clock::now();
	setDirectDisplay(desktop_, true);
  } catch (Scene::IOError &) {
	std::ostringstream msg;
    msg << filename << ": file not found"; 
    handleError(msg.str()); 
    return;
  } catch (Scene::ParseError &pe) {
    std::ostringstream msg;
    msg << filename << ':' << pe.getLine() << ": error: " << pe.what();
    handleError(msg.str()); 
    return;
  }
}

// ------------------------------------------------------------
// Szene mit Hintergrundfarbe l�schen und Fehlermeldung anzeigen
// ------------------------------------------------------------
void Controller::handleError(const std::string &msg) {

	setDirectDisplay(desktop_, false);
    desktop_->scn->clear();  // destroy all objects in scene and clear with black
    updateScene(desktop_); // shows blue background in scene
    strcpy(desktop_->lastmessage, msg.c_str());
	MxAlertArgs msgOk = { "Alert", desktop_->lastmessage,
			 {"Ok", 0, 1},
			 {NULL, 0, MxFalse},
			 {NULL, 0, MxFalse} };
    MxAlertStart(&msgOk, &desktop_->base.object);
}

// ------------------------------------------------------------
// Change the window size to fit the desktop size
// ------------------------------------------------------------
void Controller::resizeFileSelector(MxFileselector *fs) {
  MxObject *parent = MxParent(&fs->base.object);
  MxGeomSize(&fs->base.object, MxW(&fs->base.object), MxH(parent)/2);
  MxGeomPosition(&fs->base.object, fs->base.object.position.x1, MxH(parent)/4);
  MxEventSendSimple(&fs->base.object, MxEventGeomChanged);
  MxEnqueueRefresh(&fs->base.object, MxTrue);
}

// ------------------------------------------------------------
// Shows a editor window with key help
// ------------------------------------------------------------
void Controller::showHelp() {
	const char* buffer = "    w        move forward\n"
		"    a        move left\n"
		"    s        move backward\n"
		"    d        move right\n"
		"    r        reload scene\n"
		"    q        quit\n"
		"    <space>  play/pause\n"
		"    F1       Key Help\n"
		"    F3       Load Scene File\n"
		"    F9       Set move mode to walk\n"
		"    F10      Set move mode to fly\n"
		;
	MxWindowArgs winargs;
	MxScrollTextareaArgs textargs;

	MxArgsInit(&textargs);
	textargs.textarea.caption = buffer;
	textargs.textarea.endtest = MxLineEndWordwrap;
	//textargs.scroll.border = -1;

	MxScrollTextarea *text = MxScrollTextareaNew(NULL, 0, 0, 300, 250, &textargs);

	MxArgsInit(&winargs);
	winargs.caption = "Key Help";
	winargs.client = &text->base.object;

	MxWindow *win = MxWindowNew(&desktop_->base.object, 150, 150, 300, 250, &winargs);
	win->base.object.handler = helpHandler;
	refreshDesktop();
}

// ------------------------------------------------------------
// Refreshes all the Children of the desktop
// ------------------------------------------------------------
void Controller::refreshDesktop() {
	for (int i = 0; i < desktop_->base.object.children.data->num; i++) {
		MxEnqueueRefresh(desktop_->base.object.children.data->child[i], MxTrue);
	}
}

} // namespace scene