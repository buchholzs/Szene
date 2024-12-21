// Copyright (c) 2024, Steffen Buchholz

#include "TargetCommand.h"

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
TargetCommand::TargetCommand (pl_Obj* obj, pl_Cam* cam, pl_Light* light, int duration, bool repeat) :
	Command(duration), obj_(obj), cam_(cam), light_(light), repeat_(repeat), origin_({ 0.0f, 0.0f, 0.0f })
{
}
// ------------------------------------------------------------
// Destruktor
//
TargetCommand::~TargetCommand ()
{
}

} // scene

