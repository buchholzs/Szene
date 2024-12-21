// Copyright (c) 2024, Steffen Buchholz

#include "Rotator.h"
#include <stdexcept>
#include <cmath>

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
Rotator::Rotator (pl_Obj* obj, pl_Cam* cam, pl_Obj* relativeTo, float angle, int duration, bool repeat) :
	TargetCommand(obj, cam, NULL, duration, repeat), isRelativeTo_(true),
	origin_({ 0, 0, 0 }), relativeTo_(relativeTo), angle_(angle), distance_(0)
{
	resetOrigin(obj, cam, NULL);
	distance_ = distance3D();
}
Rotator::Rotator(pl_Obj* obj, pl_Cam* cam, int duration, bool repeat) :
	TargetCommand(obj, cam, NULL, duration, repeat), isRelativeTo_(false),
	origin_({0, 0, 0}), relativeTo_(NULL), angle_(0), distance_(0)
{
	resetOrigin(obj, cam, NULL);
}
// ------------------------------------------------------------
// Destruktor
//
Rotator::~Rotator ()
{
}

void Rotator::resetOrigin(pl_Obj* obj, pl_Cam* cam, pl_Light* light) {
	if (relativeTo_ != NULL) {
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
	} else {
		if (obj) {
			origin_[0] = obj->Xa;
			origin_[1] = obj->Ya;
			origin_[2] = obj->Za;
		}
		if (cam) {
			origin_[0] = cam->Pan;
			origin_[1] = cam->Pitch;
			origin_[2] = cam->Roll;
		}
	 }
}

void Rotator::Execute (int timeDiff) {
	elapsedTime_+=timeDiff;
	// Calculate the current position based on the elapsed time
	if (elapsedTime_ > duration_) {
		if (!repeat_) {
			return; // Animation Ende
		}
		elapsedTime_ = 0;
	}
	float t = (float)elapsedTime_ / (float)duration_;
	if (isRelativeTo_) {
		pl_Obj* obj = getTargetObj();
		if (obj) {
			obj->Xp = relativeTo_->Xp + distance_ * cos(degToRad(angle_ * t));
			obj->Zp = relativeTo_->Zp + distance_ * sin(degToRad(angle_ * t));
		}
		pl_Cam* cam = getTargetCam();
		if (cam) {
			cam->X = relativeTo_->Xp + distance_ * cos(degToRad(angle_ * t));
			cam->Z = relativeTo_->Zp + distance_ * sin(degToRad(angle_ * t));
		}
	}
	else {
		std::array<float, 3> angle = getAngle(0);
		pl_Obj* obj = getTargetObj();
		if (obj) {
			obj->Xa = origin_[0] + angle[0] * t;
			obj->Ya = origin_[1] + angle[1] * t;
			obj->Za = origin_[2] + angle[2] * t;
		}
		pl_Cam* cam = getTargetCam();
		if (cam) {
			cam->Pan = origin_[0] + angle[0] * t;
			cam->Pitch = origin_[1] + angle[1] * t;
			cam->Roll = origin_[2] + angle[2] * t;
		}
	}
}

void Rotator::addAngle(float x, float y, float z) {
	angles_.push_back({x, y, z});
}

// Returning array (throws std::out_of_range if index is invalid)
std::array<float, 3> Rotator::getAngle(size_t index) const {
    if (index >= angles_.size()) {
        throw std::out_of_range("Angle index out of range");
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
