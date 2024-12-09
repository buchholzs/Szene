// Copyright (c) 2024, Steffen Buchholz

#ifndef _Rotator_H_
#define _Rotator_H_

#include <vector>
#include <array>
#include <PLUSH.H>
#include "TargetCommand.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace scene {

class Rotator : public TargetCommand {

public:
	Rotator(pl_Obj* obj, pl_Cam* cam, pl_Obj* relativeTo, float angle, int duration, bool repeat);
	Rotator(pl_Obj* obj, pl_Cam* cam, int duration, bool repeat);
	virtual ~Rotator ();
    void resetOrigin(pl_Obj *obj, pl_Cam *cam, pl_Light *light);
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

	bool isRelativeTo_;
	float angle_;
	float distance_;
	pl_Obj* relativeTo_;
	std::vector<std::array<float, 3>> angles_;  // Each angle is stored as {x, y, z}
	std::array<float, 3> origin_; // Ursprungspunkt
};

} // scene

#endif
