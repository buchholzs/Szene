// Copyright (c) 2024, Steffen Buchholz

#ifndef _TargetCommand_H_
#define _TargetCommand_H_

#include <array>
#include <PLUSH.H>
#include "Command.h"

namespace scene {

class TargetCommand : public Command {

public:
	TargetCommand(pl_Obj* obj, pl_Cam* cam, pl_Light* light, int duration, bool repeat);
	virtual ~TargetCommand ();
	pl_Obj *getTargetObj() {
    	return obj_;
	}
	pl_Cam *getTargetCam() {
    	return cam_;
	}
	pl_Light *getTargetLight() {
    	return light_;
	}
	void setTargetObj(pl_Obj *obj) {
    	obj_ = obj;
	}
	void setTargetCam(pl_Cam *cam) {
    	cam_ = cam;
	}
	void setTargetLight(pl_Light *light) {
    	light_ = light;
	}
	virtual void resetOrigin(pl_Obj* obj, pl_Cam* cam, pl_Light* light) = 0;
protected:
	bool repeat_;
	std::array<float, 3> origin_; // Ursprungspunkt
private:
	pl_Obj* obj_;
	pl_Cam* cam_;
	pl_Light* light_;
};

} // scene

#endif
