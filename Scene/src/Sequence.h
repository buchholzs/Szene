// Copyright (c) 2024, Steffen Buchholz

#ifndef _Sequence_H_
#define _Sequence_H_

#include <vector>
#include <array>
#include <string>
#include <PLUSH.H>
#include "TargetCommand.h"

namespace scene {

class Sequence : public Command {

public:
	Sequence(pl_Obj* obj, bool repeat);
	virtual ~Sequence ();
	void Execute (int timeDiff) ;
	void addTargetCommand(std::pair<std::string, TargetCommand*> action);
	// return the point as an array
    std::pair<std::string, TargetCommand*> getTargetCommand(size_t index) const;
    // get the number of commands
    size_t getTargetCommandCount() const;
private:
	void restorePosAndAngle(pl_Obj* other);
	bool repeat_;
	pl_Obj* obj_;
	std::vector<std::pair<std::string, TargetCommand*> > targetCommands_;
	unsigned int idx_;
};

} // scene


#endif
