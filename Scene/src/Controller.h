// Copyright (c) 2006,2010 Steffen Buchholz

#ifndef _Controller_H_
#define _Controller_H_

#include "MoveMode.h"

struct SceneDesktop;
class MxFileselector;

namespace scene {

class Scene;

class Controller {
public:
	Controller (MoveMode* moveMode, Scene *scene);
	virtual ~Controller ();
	void	moveForward (const float timeDiff) { moveMode_->moveForward(timeDiff); }
	void	moveLeft (const float timeDiff) {moveMode_->moveLeft(timeDiff); }
	void	moveRight (const float timeDiff) {moveMode_->moveRight(timeDiff); }
	void	moveBackward (const float timeDiff) {moveMode_->moveBackward(timeDiff); }
	void	zoom (const float factor);
	void	panView (const float pan) {moveMode_->panView(pan); }
	void	pitchView (const float pitch) {moveMode_->pitchView(pitch); }
	void	setMoveMode (MoveMode* moveMode) { moveMode_ = moveMode; }
	const MoveMode* getMoveMode () { return moveMode_; }
	void	loadScene(SceneDesktop *desktop);
	void	saveScene(SceneDesktop *desktop);
private:
        void resizeFileSelector(MxFileselector *fs);
	MoveMode*	moveMode_;
	Scene	*scene_;
};

} // scene
#endif
