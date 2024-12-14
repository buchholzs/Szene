// Copyright (c) 2024, Steffen Buchholz

#ifndef _SetMat_H_
#define _SetMat_H_

#include "TargetCommand.h"

namespace scene {

class SetMat : public TargetCommand {

public:
	SetMat(pl_Obj* obj, pl_Mat *m, int duration, bool repeat);
	virtual ~SetMat ();
    void resetOrigin(pl_Obj *obj, pl_Cam *cam, pl_Light *light) {}
    void Execute(float timeDiff);
private:
    pl_Obj *obj_;
	pl_Mat *m_;
};

} // scene

#endif
