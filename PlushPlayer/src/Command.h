// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _Command_H_
#define _Command_H_

namespace scene {

class Command {
public:
	virtual ~Command ();
	virtual void Execute (float timeDiff) = 0;
};

} // scene
#endif
