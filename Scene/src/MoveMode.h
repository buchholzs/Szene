// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _MoveMode_H_
#define _MoveMode_H_

#include <memory>
#include <chrono>

namespace scene {

class Scene;

class MoveMode {
public:
	MoveMode (std::shared_ptr<Scene> scene, const float moveSpeed, const float turnSpeed);
	virtual ~MoveMode ();
	virtual void	moveForward (const std::chrono::milliseconds timeDiff) = 0;
	virtual void	moveLeft (const std::chrono::milliseconds timeDiff) = 0;
	virtual void	moveRight (const std::chrono::milliseconds timeDiff) = 0;
	virtual void	moveBackward (const std::chrono::milliseconds timeDiff) = 0;
	virtual void	panView (const float pan) = 0;
	virtual void	pitchView (const float pitch) = 0;
	void	setMoveSpeed (const float speed) { moveSpeed_=speed; }
	void	setTurnSpeed (const float speed) { turnSpeed_=speed; }
protected:
	std::shared_ptr<Scene>	scene_;
	float	moveSpeed_;
	float	turnSpeed_;
};

} // scene

#endif
