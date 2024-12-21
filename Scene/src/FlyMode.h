// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _FlyMode_H_
#define _FlyMode_H_

#include "MoveMode.h"

namespace scene {

class FlyMode : public scene::MoveMode {
public:
	FlyMode(std::shared_ptr<Scene> scene, const float moveSpeed, const float turnSpeed) :
	  MoveMode(scene, moveSpeed, turnSpeed) {}
	virtual ~FlyMode ();
	void	moveForward (const float timeDiff);
	void	moveLeft (const float timeDiff);
	void	moveRight (const float timeDiff);
	void	moveBackward (const float timeDiff);
	void	panView (const float pitch);
	void	pitchView (const float pan);
};

} // scene

#endif
