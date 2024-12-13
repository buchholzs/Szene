// Copyright (c) 2024, Steffen Buchholz

#include "Sequence.h"
#include <stdexcept>
#include <utility>

namespace scene {

// ------------------------------------------------------------
// Konstruktor
//
Sequence::Sequence (pl_Obj* obj, bool repeat) :
	Command(0),  repeat_(repeat), idx_(0), obj_(plObjClone(obj))
{}

// ------------------------------------------------------------
// Destruktor
//
Sequence::~Sequence ()
{
	// Alle Commands löschen
	for (auto& targetCommand : targetCommands_) {
		delete targetCommand.second;
	}
	// Targetobjekt löschen
	free(obj_);
}

void Sequence::restorePosAndAngle(pl_Obj* other) {
	other->Xp = obj_->Xp;
	other->Yp = obj_->Yp;
	other->Zp = obj_->Zp;
	other->Xa = obj_->Xa;
	other->Ya = obj_->Ya;
	other->Za = obj_->Za;
}

void Sequence::Execute (float timeDiff) {
	elapsedTime_+=timeDiff;
	std::pair<std::string, TargetCommand*> action;
	bool resetOrigin = false;
	bool resetTarget = false;

	action = getTargetCommand(idx_);
	if (elapsedTime_ > action.second->getDuration()) {
		if (idx_ < getTargetCommandCount() - 1) {
			idx_++;
			resetOrigin = true;
		} else {
			if (!repeat_) {
				return; // Animation Ende
			}
			else {
				idx_ = 0;
				resetTarget = true;
			}
		}
		reset();
		action = getTargetCommand(idx_);
		action.second->reset();
		if (resetOrigin) {
			TargetCommand* targetCommand = action.second;
			action.second->resetOrigin(targetCommand->getTargetObj(),
				targetCommand->getTargetCam(),
				targetCommand->getTargetLight());

		}
		if (resetTarget) {
			TargetCommand* targetCommand = action.second;
			pl_Obj* oldObj = action.second->getTargetObj();
			restorePosAndAngle(oldObj);
		}
	}
	action.second->Execute(timeDiff);
}

void Sequence::addTargetCommand(std::pair<std::string, TargetCommand*> action) {
	targetCommands_.push_back(action);
}

// Returning command (throws std::out_of_range if index is invalid)
std::pair<std::string, TargetCommand*> Sequence::getTargetCommand(size_t index) const {
    if (index >= targetCommands_.size()) {
        throw std::out_of_range("TargetCommand index out of range");
    }
    return targetCommands_[index];
}

// Get the total number of commands
size_t Sequence::getTargetCommandCount() const {
    return targetCommands_.size();
}

} // scene
