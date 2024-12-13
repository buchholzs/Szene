// Copyright (c) 2024, Steffen Buchholz

#include "Mover.h"
#include <stdexcept>

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
Mover::Mover (pl_Obj* obj, pl_Cam* cam, pl_Light* light, float duration, bool repeat) :
	TargetCommand(obj, cam, light, duration, repeat)
{
	resetOrigin(obj, cam, light);
}
// ------------------------------------------------------------
// Destruktor
//
Mover::~Mover ()
{
}

void Mover::resetOrigin(pl_Obj* obj, pl_Cam* cam, pl_Light* light) {
	if (obj) {
		origin_[0] = obj->Xp;
		origin_[1] = obj->Yp;
		origin_[2] = obj->Zp;
	}
	if (cam) {
		origin_[0] = cam->X;
		origin_[1] = cam->Y;
		origin_[2] = cam->Z;
	}
	if (light) {
		origin_[0] = light->Xp;
		origin_[1] = light->Yp;
		origin_[2] = light->Zp;
	}
}

void Mover::Execute (float timeDiff) {
	elapsedTime_+=timeDiff;
	// Calculate the current position based on the elapsed time
	std::array<float, 3> point = getPoint(0);
	if (elapsedTime_ > duration_) {
		if (!repeat_) {
			return; // Animation Ende
		}
		reset();
	}
	float t = (float)elapsedTime_ / (float)duration_;
	pl_Obj* obj = getTargetObj();
	if (obj) {
		obj->Xp = origin_[0] + point[0]*t;
		obj->Yp = origin_[1] + point[1]*t;
		obj->Zp = origin_[2] + point[2]*t;
	}
	pl_Cam* cam = getTargetCam();
	if (cam) {
		cam->X = origin_[0] + point[0] * t;
		cam->Y = origin_[1] + point[1] * t;
		cam->Z = origin_[2] + point[2] * t;
	}
	pl_Light* light = getTargetLight();
	if (light) {
		light->Xp = origin_[0] + point[0] * t;
		light->Yp = origin_[1] + point[1] * t;
		light->Zp = origin_[2] + point[2] * t;
	}
}

void Mover::addPoint(float x, float y, float z) {
	points_.push_back({x, y, z});
}

// Returning array (throws std::out_of_range if index is invalid)
std::array<float, 3> Mover::getPoint(size_t index) const {
    if (index >= points_.size()) {
        throw std::out_of_range("Point index out of range");
    }
    return points_[index];
}

// Get the total number of points
size_t Mover::getPointCount() const {
    return points_.size();
}

} // scene
