// Copyright (c) 2024, Steffen Buchholz

#ifndef _Pause_H_
#define _Pause_H_

#include "TargetCommand.h"

namespace scene {

class Pause : public TargetCommand {

public:
	Pause(int duration);
	virtual ~Pause ();
    void resetOrigin(pl_Obj *obj, pl_Cam *cam, pl_Light *light) {}
    void Execute(int timeDiff);
};

} // scene

#endif
