// Copyright (c) 2006 Steffen Buchholz


/*
 * Applikation zum Editieren von Materialeigenschaften
 */
class MatEdit {
public:
	// Konstruktor
	MatEdit(string filename);
	// Ausgabe der Szene und der GUI
	void run();
	// Szene löschen
	void newScene();
	// Szene neu laden
	void loadScene(const string &filename);
	// Textur des ausgeählten Materials neu laden
	void loadTexture(const string &filename);
private:
	// erzeugt ein Fenster mit dem Materialeditor
	void createMatWin(MxDesktop *desktop);
	// Erzeugt den Desktop
	int createDesktop(MxDesktop *desktop);
	// Ausgabe von Zusatzinfos
	void printLines(const pl_Cam *cam, const list<string> &lines);
	// Ausgabe der Materialien in eine Liste
	void dumpMaterial(pl_Mat *mat, list<string> &l);
	// Palette neu laden
	void reloadPalette();
	// MatEdit aktualisieren
	void updateMatWin();
	// MatWin aktualisieren
	void OnChangedScene();	
	friend void *MatWinHandler(MxObject * object, const MxEvent * const event);

	string filename; // Filename der Szene
	Scene scene; // Szene
	bool matChanged; // material changed

	char lastmessage[256]; // Message for Alert
	MxAlertArgs msgOk; // Alert

	pl_Cam *cam; // Kamera
	pl_Mat *mat; // Materialien
	pl_Obj *obj; // selektiertes Object

	int lastNewTexture_; // letzte erzeugte Texture

	MxDesktop desktop;
	MxWindow *matWin;
	MxSlider *sliderAmbient[3];
	MxSlider *sliderDiffuse[3];
	MxSlider *sliderSpecular[3];
	MxSlider *sliderShininess;
	MxSlider *sliderTransparent;

	MxStatictext *staticTextTexture;
};

