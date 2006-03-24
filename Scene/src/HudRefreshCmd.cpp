// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.


#include "HudRefreshCmd.h"
#include <grx20.h>
#include "Hud.h"

namespace scene {
  const int HudRefreshCmd::refresh_ivl_hud = 200; // Refresh-Interval HUD in msec

// ------------------------------------------------------------
// Konstruktor
//
HudRefreshCmd::HudRefreshCmd (Hud *hud, struct _GR_context *ctx) : 
	  elapsedTime_(0), hud_(hud), ctx_(ctx)
{
 //hudctx_ = GrCreateContext(ctx->gc_xmax + 1,ctx->gc_ymax + 1, NULL, NULL);
 hudctx_ = GrCreateFrameContext(GR_frameRAM1, ctx->gc_xmax + 2 /* sonst array bound read in GrBitBlt1bpp */,ctx->gc_ymax + 1, NULL, NULL);

}
// ------------------------------------------------------------
// Destruktor
//
HudRefreshCmd::~HudRefreshCmd ()
{
	GrDestroyContext(hudctx_);
}

void HudRefreshCmd::Execute (float timeDiff) {
	elapsedTime_+=timeDiff;

	const GrContext *oldctx = GrCurrentContext();
	if (elapsedTime_>refresh_ivl_hud) {
		elapsedTime_=0;
		GrSetContext(hudctx_);
		GrClearContext( GrBlack() );
		hud_->display(hudctx_);
	}

  /* Put the bitmap into the screen */
  GrSetContext(ctx_);
  GrBitBlt1bpp(ctx_,0,0,hudctx_,0,0,hudctx_->gc_xmax,hudctx_->gc_ymax,
	  hud_->getStatusColor(),GrNOCOLOR);
/*	GrBitBlt(ctx_,0,0,hudctx_,0,0,hudctx_->gc_xmax,hudctx_->gc_ymax,
		GrImageModeColor(GrBlack())); */

  GrSetContext(oldctx);
}

} // scene
