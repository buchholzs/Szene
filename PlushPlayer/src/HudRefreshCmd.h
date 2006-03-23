// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _HudRefreshCmd_H_
#define _HudRefreshCmd_H_

#include "Command.h"

struct _GR_context;

namespace scene {

class Hud;

class HudRefreshCmd : public Command {
  const static int refresh_ivl_hud; // Refresh-Interval HUD in msec

public:
	HudRefreshCmd(Hud *hud, struct _GR_context *ctx);
	virtual ~HudRefreshCmd ();
	void Execute (float timeDiff) ;
private:
	float elapsedTime_;
	Hud *hud_;
	struct _GR_context *ctx_;
	struct _GR_context *hudctx_;
};

} // scene

#endif
