// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.


#include "Hud.h"
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

namespace scene {

const int avgSize = 5;

// ------------------------------------------------------------
// Konstruktor
//
Hud::Hud(GrColor statusColor) :
	statusColor_(statusColor), 
	Xp_(0),
	Yp_(0),
	Zp_(0),
	Xa_(0),
	Ya_(0),
	Za_(0),
	fps_(0)
{}

// ------------------------------------------------------------
// display hud in graphic context
//
void Hud::display (GrContext* ctx)
{
  std::ostringstream str;
  int yinc = 12;
  int ypos = ctx->gc_ymax - 36;
  int sizex = ctx->gc_xmax + 1;
  int sizey = ctx->gc_ymax + 1;

  GrContext oldctx;
  GrSaveContext(&oldctx);

  GrSetContext(ctx);
  //GrClearContext( GrBlack() );

  str << setprecision(1) << fixed << "FPS=" << fps_;
  GrTextXY(5, ypos , (char*)str.str().c_str(), statusColor_, GrNOCOLOR);
  ypos += yinc;

  str.str("");
  str << setprecision(2) << "Xp=" << Xp_ << " Yp=" << setprecision(2) << Yp_ << " Zp=" << Zp_
	  << " Xa=" << Xa_ << " Ya=" << Ya_ << " Za=" << Za_; 
  GrTextXY(5, ypos , (char*)str.str().c_str(), statusColor_, GrNOCOLOR );
  ypos += yinc;

  GrTextXY(5, ypos , (char*)status_.c_str(), statusColor_, GrNOCOLOR );
  ypos += yinc;

  // cross
  GrLine(sizex/2 - 10, sizey/2, sizex/2 + 10, sizey/2, statusColor_);
  GrLine(sizex/2, sizey/2 - 10, sizex/2, sizey/2 + 10, statusColor_);

  GrSetContext(&oldctx);
}


} // scene
