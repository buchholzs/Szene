// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _Hud_H_
#define _Hud_H_

#include <PLUSH.H>
#include <grx20.h>
#include <string>
#include <list>

namespace scene {

class Hud {
public:
	// Konstruktor
	Hud(GrColor statusColor);
	// measurements for hud
	void	setPosition (const pl_Float Xp, const pl_Float Yp, const pl_Float Zp, const pl_Float Xa, const pl_Float Ya, const pl_Float Za)
		{ Xp_=Xp; Yp_=Yp; Zp_=Zp; Xa_=Xa; Ya_=Ya; Za_=Za; }
	void	setStatus(std::string status) { status_=status; }
	void	setFPS(float fps) { fps_ = fps; }
	// display hud in graphic context
	void	display (struct _GR_context *ctx);
	GrColor	getStatusColor() { return statusColor_; }
private:
	GrColor statusColor_;
	pl_Float Xp_;
	pl_Float Yp_;
	pl_Float Zp_;
	pl_Float Xa_;
	pl_Float Ya_;
	pl_Float Za_;
	std::string status_;
	float fps_;
	std::list<float> fpsQ_;
};

} // scene

#endif
