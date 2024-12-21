// Copyright (c) 2024, Steffen Buchholz

#ifndef _Mover_H_
#define _Mover_H_

#include <vector>
#include <PLUSH.H>
#include "TargetCommand.h"

namespace scene {

class Mover : public TargetCommand {

public:
	Mover(pl_Obj* obj, pl_Cam* cam, pl_Light* light, int duration, bool repeat);
	virtual ~Mover ();
    void resetOrigin(pl_Obj *obj, pl_Cam *cam, pl_Light *light);
    void Execute(int timeDiff);
    void addPoint(float x, float y, float z);
	// return the point as an array
    std::array<float, 3> getPoint(size_t index) const;
    // get the number of points
    size_t getPointCount() const;
private:
	std::vector<std::array<float, 3>> points_;  // Each point is stored as {x, y, z}
};

} // scene

#endif
