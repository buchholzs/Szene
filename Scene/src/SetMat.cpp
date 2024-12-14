// Copyright (c) 2024, Steffen Buchholz

#include "SetMat.h"

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
SetMat::SetMat (pl_Obj* obj, pl_Mat *m, int duration, bool repeat) :
	TargetCommand(NULL, NULL, NULL, duration, repeat),
	obj_(obj),
	m_(m)
{
}

// ------------------------------------------------------------
// Destruktor
//
SetMat::~SetMat ()
{
}

void SetMat::Execute (float timeDiff) {
	if (elapsedTime_ == 0) {
		plObjSetMat(obj_, m_, true);
	}
	elapsedTime_+=timeDiff;
	if (elapsedTime_ > duration_) {
		if (!repeat_) {
			return; // Animation Ende
		}
		reset();
	}
}

} // scene
