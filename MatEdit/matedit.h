// Copyright (c) 2006 Steffen Buchholz

#include <string>
#include <list>
#include "depui/depui.h"
#include "Scene.h"

/*
 * Applikation zum Editieren von Materialeigenschaften
 */
class MatEdit {
public:
	// Konstruktor
	MatEdit(std::string filename);
	// Ausgabe der Szene und der GUI
	void run();
	// Szene l�schen
	void newScene();
	// Szene neu laden
	void loadScene(const std::string &filename);
	// Textur des ausgew�hlten Materials neu laden
	void loadTexture(const std::string &filename);
	// Textur des ausgew�hlten Materials entfernen
	void resetTexture();
	// w�hlt ein Material zur Bearbeitung aus
	void setMaterial(pl_Mat *mat) {this->mat = mat;}
	// MatWin aktualisieren
	void OnChangedScene();
	// liefert die Szene
	scene::Scene *getScene() {return &scene;}
private:
	// erzeugt ein Fenster mit dem Materialeditor
	void createMatWin(MxDesktop *desktop);
	// Erzeugt den Desktop
	int createDesktop(MxDesktop *desktop);
	// Ausgabe von Zusatzinfos
	void printLines(const pl_Cam *cam, const std::list<std::string> &lines);
	// Ausgabe der Materialien in eine Liste
	void dumpMaterial(pl_Mat *mat, std::list<std::string> &l);
	// MatEdit aktualisieren
	void updateMatWin();
	// shadeMode -> Radio
	void shadeType2Radio(int shadeType);
	// Radio -> shadeMode
	int radio2ShadeType();

	std::string filename; // Filename der Szene
	scene::Scene scene; // Szene
	bool matChanged; // material changed

	char lastmessage[256]; // Message for Alert
	MxAlertArgs msgOk; // Alert

	pl_Cam *cam; // Kamera
	pl_Mat *mat; // selektiertes Material
	pl_Obj *obj; // selektiertes Object

	int lastNewTexture_; // letzte erzeugte Texture

	MxDesktop desktop;
	MxWindow *matWin;
	MxSlider *sliderAmbient[3];
	MxSlider *sliderDiffuse[3];
	MxSlider *sliderSpecular[3];
	MxSlider *sliderShininess;
	MxSlider *sliderTransparent;
	MxSlider *sliderFadeDist;
	MxSlider *sliderTexScaling;
	MxSlider *sliderPerspectiveCorrect;

	MxButton *radioNone;
	MxButton *radioFlat;
	MxButton *radioFlatDistance;
	MxButton *radioGouraud;
	MxButton *radioGouraudDistance;

	MxStatictext *staticTextTexture;
	MxList *matList;
};

