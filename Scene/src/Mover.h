// Copyright (c) 2024, Steffen Buchholz

#ifndef _Mover_H_
#define _Mover_H_

#include <vector>
#include <array>
#include <PLUSH.H>
#include "Command.h"

namespace scene {

class Mover : public Command {

public:
	Mover(pl_Obj* obj, pl_Cam* cam, pl_Light* light, float duration, bool relative);
	virtual ~Mover ();
	void Execute (float timeDiff) ;
	void addPoint(float x, float y, float z);
	// return the point as an array
    std::array<float, 3> getPoint(size_t index) const;
    // get the number of points
    size_t getPointCount() const;
private:
	pl_Obj* obj_;
	pl_Cam* cam_;
	pl_Light* light_;
	float elapsedTime_;
	float duration_;
	bool repeat_;
	std::vector<std::array<float, 3>> points_;  // Each point is stored as {x, y, z}
	std::array<float, 3> origin_; // Ursprungspunkt
};

} // scene

#endif
