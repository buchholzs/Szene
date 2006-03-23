// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.


#include "Controller.h"

#include "Scene.h"

namespace scene {

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
void Controller::zoom (const float factor)
{
	// PRESERVE:BEGIN
	// Insert your preservable code here...
	// PRESERVE:END
}

} // scene
