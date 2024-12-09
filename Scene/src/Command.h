// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _Command_H_
#define _Command_H_

namespace scene {

class Command {
public:
	Command(int duration) : duration_(duration), elapsedTime_(0) {}
	virtual ~Command ();
	virtual void Execute (float timeDiff) = 0;
	virtual void reset() {
		elapsedTime_ = 0;
	}
	virtual int getDuration() {
		return duration_;
	}
protected:
	int elapsedTime_;
	int duration_;
};

} // scene
#endif
