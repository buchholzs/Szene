// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#include <chrono>
#include "Scene.h"
#include "WalkMode.h"


namespace scene {

  // ------------------------------------------------------------
  WalkMode::~WalkMode ()
  {}

  // ------------------------------------------------------------
  void WalkMode::moveForward (const std::chrono::milliseconds timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff.count() *moveSpeed_*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff.count() *moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
    }	
  }


  // ------------------------------------------------------------
  void WalkMode::moveLeft (const std::chrono::milliseconds timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff.count() *moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff.count() *moveSpeed_* -sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
    }	
  }


  // ------------------------------------------------------------
  void WalkMode::moveRight (const std::chrono::milliseconds timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff.count() *moveSpeed_* -cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff.count() *moveSpeed_* sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
    }	
  }


  // ------------------------------------------------------------
  void WalkMode::moveBackward (const std::chrono::milliseconds timeDiff)
  {
    pl_Cam *cam = scene_->getCurrCamera();
    if (!cam) return;

    if (moveSpeed_ != 0.0) {
      cam->X -=
        timeDiff.count() *-moveSpeed_*sin(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
      cam->Z += 
        timeDiff.count() *-moveSpeed_*cos(cam->Pan*PL_PI/180.0)*cos(cam->Pitch*PL_PI/180.0);
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
