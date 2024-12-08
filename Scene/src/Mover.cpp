// Copyright (c) 2024, Steffen Buchholz

#include "Mover.h"
#include <stdexcept>

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
Mover::Mover (pl_Obj* obj, pl_Cam* cam, pl_Light* light, float duration, bool repeat) :
	obj_(obj), cam_(cam), light_(light), duration_(duration), repeat_(repeat), elapsedTime_(0)
{
	if (obj_) {
		origin_[0] = obj_->Xp;
		origin_[1] = obj_->Yp;
		origin_[2] = obj_->Zp;
	}
	if (cam_) {
		origin_[0] = cam_->X;
		origin_[1] = cam_->Y;
		origin_[2] = cam_->Z;
	}
	if (light_) {
		origin_[0] = light_->Xp;
		origin_[1] = light_->Yp;
		origin_[2] = light_->Zp;
	}
}
// ------------------------------------------------------------
// Destruktor
//
Mover::~Mover ()
{
}

void Mover::Execute (float timeDiff) {
	elapsedTime_+=timeDiff;
	// Calculate the current position based on the elapsed time
	std::array<float, 3> point = getPoint(0);
	if (elapsedTime_ > duration_) {
		if (!repeat_) {
			return; // Animation Ende
		}
		elapsedTime_ = 0;
	}
	float t = elapsedTime_ / duration_;
	if (obj_) {
		obj_->Xp = origin_[0] + point[0]*t;
		obj_->Yp = origin_[1] + point[1]*t;
		obj_->Zp = origin_[2] + point[2]*t;
	}
	if (cam_) {
		cam_->X = origin_[0] + point[0] * t;
		cam_->Y = origin_[1] + point[1] * t;
		cam_->Z = origin_[2] + point[2] * t;
	}
	if (light_) {
		light_->Xp = origin_[0] + point[0] * t;
		light_->Yp = origin_[1] + point[1] * t;
		light_->Zp = origin_[2] + point[2] * t;
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
