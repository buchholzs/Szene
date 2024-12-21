// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _FlyMode_H_
#define _FlyMode_H_

#include <chrono>
#include "MoveMode.h"

namespace scene {

class FlyMode : public scene::MoveMode {
public:
	FlyMode(std::shared_ptr<Scene> scene, const float moveSpeed, const float turnSpeed) :
	  MoveMode(scene, moveSpeed, turnSpeed) {}
	virtual ~FlyMode ();
	void	moveForward (const std::chrono::milliseconds timeDiff);
	void	moveLeft (const std::chrono::milliseconds timeDiff);
	void	moveRight (const std::chrono::milliseconds timeDiff);
	void	moveBackward (const std::chrono::milliseconds timeDiff);
	void	panView (const float pitch);
	void	pitchView (const float pan);
};

} // scene

#endif
