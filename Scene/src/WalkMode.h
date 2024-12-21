// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _WalkMode_H_
#define _WalkMode_H_

#include "MoveMode.h"

namespace scene {

class WalkMode : public scene::MoveMode {
public:
	WalkMode(std::shared_ptr<Scene> scene, const float moveSpeed, const float turnSpeed) : 
	  MoveMode(scene, moveSpeed, turnSpeed) {}
	virtual ~WalkMode ();
	void	moveForward (const float timeDiff);
	void	moveLeft (const float timeDiff);
	void	moveRight (const float timeDiff);
	void	moveBackward (const float timeDiff);
	void	panView (const float pan);
	void	pitchView (const float pitch);
};

} // scene

#endif
