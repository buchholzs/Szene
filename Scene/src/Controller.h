// Copyright (c) 2006,2010 Steffen Buchholz

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#undef GrContext
#undef GrFont
#include "MoveMode.h"

struct SceneDesktop;
struct MxFileselector;

namespace scene {

class Scene;

class Controller {
public:
	Controller (MoveMode* moveMode, Scene *scene, SceneDesktop * desktop);
	virtual ~Controller ();
	void	moveForward (const float timeDiff) { moveMode_->moveForward(timeDiff); }
	void	moveLeft (const float timeDiff) {moveMode_->moveLeft(timeDiff); }
	void	moveRight (const float timeDiff) {moveMode_->moveRight(timeDiff); }
	void	moveBackward (const float timeDiff) {moveMode_->moveBackward(timeDiff); }
	void	setPause (bool pause);
	bool	getPause();
	void	panView (const float pan) {moveMode_->panView(pan); }
	void	pitchView (const float pitch) {moveMode_->pitchView(pitch); }
	void	setMoveMode (MoveMode* moveMode) { moveMode_ = moveMode; }
	const MoveMode* getMoveMode () { return moveMode_; }
	void	openScene();
	void	loadScene(const std::string &filename);
	const std::string &getFilename() { return filename_; }
	void	saveScene();
	void	showHelp();
	void	refreshDesktop();
	void handleError(const std::string& msg);
private:
	void resizeFileSelector(MxFileselector *fs);

	MoveMode*	moveMode_;
	Scene	*scene_;
    std::string filename_;
	SceneDesktop * desktop_;
};

} // scene
#endif
