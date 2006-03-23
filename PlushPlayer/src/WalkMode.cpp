// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.


#include "WalkMode.h"

#include "Scene.h"

namespace scene {

  // ------------------------------------------------------------
  WalkMode::~WalkMode ()
  {}

  // ------------------------------------------------------------
  void WalkMode::moveForward (const float timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff*moveSpeed_*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff*moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
    }	
  }


  // ------------------------------------------------------------
  void WalkMode::moveLeft (const float timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff*moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff*moveSpeed_* -sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
    }	
  }


  // ------------------------------------------------------------
  void WalkMode::moveRight (const float timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff*moveSpeed_* -cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff*moveSpeed_* sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
    }	
  }


  // ------------------------------------------------------------
  void WalkMode::moveBackward (const float timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff*-moveSpeed_*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff*-moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
    }	
  }

  // ------------------------------------------------------------
  void WalkMode::panView (const float pan)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    cam->Pan += pan;
  }


  // ------------------------------------------------------------
  void WalkMode::pitchView (const float pitch)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    cam->Pitch += pitch;
  }


} // scene
