// Copyright (c) 2024, Steffen Buchholz

#ifndef _Rotator_H_
#define _Rotator_H_

#include <vector>
#include <array>
#include <PLUSH.H>
#include "Command.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace scene {

class Rotator : public Command {

public:
	Rotator(pl_Obj* obj, pl_Cam* cam, pl_Obj* relativeTo, float angle, float duration, bool relative);
	Rotator(pl_Obj* obj, pl_Cam* cam, float duration, bool relative);
	virtual ~Rotator ();
	void Execute (float timeDiff) ;
	void addAngle(float x, float y, float z);
	// return the point as an array
    std::array<float, 3> getAngle(size_t index) const;
    // get the number of angles
    size_t getAngleCount() const;
private:
	// Get the distance between origin_ and relativeTo_
	float distance3D();

	// Convert degrees to radians
	static float degToRad(float degrees) {
		return degrees * (M_PI / 180.0f);
	}

	pl_Obj* obj_;
	pl_Cam* cam_;
	float elapsedTime_;
	float duration_;
	bool repeat_;
	bool isRelativeTo_;
	float angle_;
	float distance_;
	pl_Obj* relativeTo_;
	std::vector<std::array<float, 3>> angles_;  // Each angle is stored as {x, y, z}
	std::array<float, 3> origin_; // Ursprungspunkt
};

} // scene

#endif
