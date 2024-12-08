// Copyright (c) 2024, Steffen Buchholz

#include "Rotator.h"
#include <stdexcept>
#include <cmath>

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
Rotator::Rotator (pl_Obj* obj, pl_Cam* cam, pl_Obj* relativeTo, float angle, float duration, bool repeat) :
	obj_(obj), cam_(cam), angle_(angle), duration_(duration), repeat_(repeat), elapsedTime_(0), isRelativeTo_(true),
	origin_({ 0, 0, 0 }), relativeTo_(relativeTo), distance_(0)
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
	distance_ = distance3D();
}
Rotator::Rotator(pl_Obj* obj, pl_Cam* cam, float duration, bool repeat) :
	obj_(obj), cam_(cam), duration_(duration), repeat_(repeat), elapsedTime_(0), isRelativeTo_(false),
	origin_({0, 0, 0}), relativeTo_(NULL), angle_(0), distance_(0)
{
	if (obj_) {
		origin_[0] = obj_->Xa;
		origin_[1] = obj_->Ya;
		origin_[2] = obj_->Za;
	}
	if (cam_) {
		origin_[0] = cam_->Pan;
		origin_[1] = cam_->Pitch;
		origin_[2] = cam_->Roll;
	}
}
// ------------------------------------------------------------
// Destruktor
//
Rotator::~Rotator ()
{
}

void Rotator::Execute (float timeDiff) {
	elapsedTime_+=timeDiff;
	// Calculate the current position based on the elapsed time
	if (elapsedTime_ > duration_) {
		if (!repeat_) {
			return; // Animation Ende
		}
		elapsedTime_ = 0;
	}
	float t = elapsedTime_ / duration_;
	if (isRelativeTo_) {
		if (obj_) {
			obj_->Xp = relativeTo_->Xp + distance_ * cos(degToRad(angle_ * t));
			obj_->Zp = relativeTo_->Zp + distance_ * sin(degToRad(angle_ * t));
		}
		if (cam_) {
			cam_->X = relativeTo_->Xp + distance_ * cos(degToRad(angle_ * t));
			cam_->Z = relativeTo_->Zp + distance_ * sin(degToRad(angle_ * t));
		}
	}
	else {
		std::array<float, 3> angle = getAngle(0);
		if (obj_) {
			obj_->Xa = origin_[0] + angle[0] * t;
			obj_->Ya = origin_[1] + angle[1] * t;
			obj_->Za = origin_[2] + angle[2] * t;
		}
		if (cam_) {
			cam_->Pan = origin_[0] + angle[0] * t;
			cam_->Pitch = origin_[1] + angle[1] * t;
			cam_->Roll = origin_[2] + angle[2] * t;
		}
	}
}

void Rotator::addAngle(float x, float y, float z) {
	angles_.push_back({x, y, z});
}

// Returning array (throws std::out_of_range if index is invalid)
std::array<float, 3> Rotator::getAngle(size_t index) const {
    if (index >= angles_.size()) {
        throw std::out_of_range("Point index out of range");
    }
    return angles_[index];
}

// Get the total number of points
size_t Rotator::getAngleCount() const {
    return angles_.size();
}

// Get the distance between origin_ and relativeTo_
float Rotator::distance3D() {
	float dx = origin_[0] - relativeTo_->Xp;
	float dy = origin_[1] - relativeTo_->Yp;
	float dz = origin_[2] - relativeTo_->Zp;

	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

} // scene
