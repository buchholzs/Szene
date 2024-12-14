// Copyright (c) 2024, Steffen Buchholz

#include "Pause.h"

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
Pause::Pause (int duration) :
	TargetCommand(NULL, NULL, NULL, duration, false)
{
}

// ------------------------------------------------------------
// Destruktor
//
Pause::~Pause ()
{
}

void Pause::Execute (float timeDiff) {
	elapsedTime_+=timeDiff;
	if (elapsedTime_ > duration_) {
		if (!repeat_) {
			return; // Animation Ende
		}
		reset();
	}
}

} // scene
