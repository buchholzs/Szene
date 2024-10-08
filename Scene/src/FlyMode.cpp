// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.


#include "FlyMode.h"

#include "Scene.h"

namespace scene {

// ------------------------------------------------------------
FlyMode::~FlyMode ()
{}

// ------------------------------------------------------------
void FlyMode::moveForward (const float timeDiff)
{
	pl_Cam *cam = scene_->getCurrCamera();
	if (!cam) return;

	if (moveSpeed_ != 0.0) {
      cam->X -=
		  timeDiff*moveSpeed_*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
		timeDiff*moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
	  cam->Y += 
		timeDiff*moveSpeed_*sin(cam->Pitch*PL_PI/180.0);
	}	
}


// ------------------------------------------------------------
void FlyMode::moveLeft (const float timeDiff)
{
	pl_Cam *cam = scene_->getCurrCamera();
	if (!cam) return;

	if (moveSpeed_ != 0.0) {
      cam->X -=
		  timeDiff*moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
		timeDiff*moveSpeed_* -sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
	  cam->Y += 
		timeDiff*moveSpeed_*sin(cam->Pitch*PL_PI/180.0);
	}	
}


// ------------------------------------------------------------
void FlyMode::moveRight (const float timeDiff)
{
	pl_Cam *cam = scene_->getCurrCamera();
	if (!cam) return;

	if (moveSpeed_ != 0.0) {
      cam->X -=
		  timeDiff*moveSpeed_* -cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
		timeDiff*moveSpeed_* sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
	  cam->Y += 
		timeDiff*moveSpeed_*sin(cam->Pitch*PL_PI/180.0);
	}	
}


// ------------------------------------------------------------
void FlyMode::moveBackward (const float timeDiff)
{
	pl_Cam *cam = scene_->getCurrCamera();
	if (!cam) return;

	if (moveSpeed_ != 0.0) {
      cam->X -=
		  timeDiff*-moveSpeed_*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
		timeDiff*-moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
	  cam->Y += 
		timeDiff*-moveSpeed_*sin(cam->Pitch*PL_PI/180.0);
	}	
}


// ------------------------------------------------------------
void FlyMode::panView (const float pan)
{
	pl_Cam *cam = scene_->getCurrCamera();
	if (!cam) return;

    cam->Pan += pan;
}


// ------------------------------------------------------------
void FlyMode::pitchView (const float pitch)
{
	pl_Cam *cam = scene_->getCurrCamera();
	if (!cam) return;

    cam->Pitch += pitch;
}


} // scene
