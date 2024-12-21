// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.


#include "MoveMode.h"

using namespace scene;

// ------------------------------------------------------------
MoveMode::MoveMode (std::shared_ptr<Scene> scene, const float moveSpeed, const float turnSpeed) :
	scene_(scene),
	moveSpeed_(moveSpeed),
	turnSpeed_(turnSpeed)
{}

// ------------------------------------------------------------
MoveMode::~MoveMode ()
{
}
