// Copyright (c) 2006, Steffen Buchholz

// NOTE: please use a PRESERVE:BEGIN/PRESERVE:END comment block
//       to preserve your hand-coding across code generations.

#ifndef _App_H_
#define _App_H_

#include <string>
#include "Desktop.h"
#include "Hud.h"

namespace scene {

class App {
public:
	// Konstruktor
	App(std::string filename);
	// Destruktor
	virtual ~App ();
	// Ausgabe der Szene und der GUI
	void	run ();
	// Szene neu laden
	void loadScene(const std::string &filename);
private:
	Desktop	desktop_;
	Hud hud_;
	std::string filename_;
};

} // scene
#endif
