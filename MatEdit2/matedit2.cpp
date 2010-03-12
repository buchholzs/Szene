#pragma warning (disable : 4786)

#include "matedit2.h"

#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#include "depui/graphics/clip.h"
#define GrContext GrContext2
#define GrFont GrFont2
#include <grx20.h>
#include <grxkeys.h>
#undef GrContext 
#undef GrFont 
#include "Scene.h"

using namespace std;
using namespace scene;

#ifdef WIN32
const int screen_w = 640;
const int screen_h = 480;
#else
const int screen_w = 640;
const int screen_h = 480;
#endif
//////////////////////////////////////////////////////////////////////////////
// Forward declarations
//
static void fileNewHandler(MxObject * object, void *data, unsigned int selected);
static void fileOpenHandler(MxObject * object, void *data, unsigned int selected);
static void fileExitHandler(MxObject * object, void *data, unsigned int selected);
static void *fileOpenOKSelectedHandler(struct MxObject * object, const MxEvent * const event);
static void resizeFileSelector(MxFileselector *fs);

//////////////////////////////////////////////////////////////////////////////
// Konstanten und Statische Variablen
//
const int BPP = 8;
const char *WINTITLE="Plush Material Editor";
const char *defFileName = "standard.scx";
const char *CStdMat= "stdmat";
const char *CStdObj = "stdobj";

const int texTextLen = 22;
const int CTextColor = 9;	// Idx of text color
const int CWinColors = 20;	// Readonly colors
const int CFixColors = CWinColors + 3;	// used for text and background

enum MatEditEventType {
	MatEditSceneChanged = MxEventUserType + 1
};

enum ega_colors { 
  BLACK        =0, 
  BLUE         =1,
  GREEN        =2,
  CYAN         =3,
  RED          =4,
  MAGENTA      =5,
  BROWN        =6,
  LIGHTGRAY    =7,
  DARKGRAY     =8,
  LIGHTBLUE    =9,
  LIGHTGREEN   =10,
  LIGHTCYAN    =11,
  LIGHTRED     =12,
  LIGHTMAGENTA =13,
  YELLOW       =14,
  WHITE        =15};

const int refresh_ivl = 200; // Refresh-Inteval in msec

static pl_uChar ThePalette[768];
static MxImage *ctx;
static MatEdit *matedit; // Application

/* The menu definitions */
static MxMenuDef fileMenu[] = {
	 {"New", fileNewHandler, 0, 0, 0, 0, 0, 0},
	 {"Open", fileOpenHandler, 0, 0, 0, 0, 0, 0},
	 {"Exit", fileExitHandler, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

static MxMenuDef mainMenu[] = {
	 {"File", 0, fileMenu, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}
};

inline int GrWidth(struct MxImage *ctx) {
  return ((GrContext2 *)ctx)->gc_xmax + 1;
}

inline int GrHeight(struct MxImage *ctx) {
  return ((GrContext2 *)ctx)->gc_ymax + 1;
}

//////////////////////////////////////////////////////////////////////////////
// Depui-Handler
//
static void fileNewHandler(MxObject * object, void *data, unsigned int selected) {
	matedit->newScene();
}

static void fileOpenHandler(MxObject * object, void *data, unsigned int selected) {

  /* text for filename */
  MxStatictextArgs textargs;
  MxArgsInit(&textargs);
  textargs.caption = (const char *)MxMalloc(MX_MAX_PATH);
  strcpy((char *)textargs.caption, "");
  textargs.len = 0;
  textargs.ownscaption = 1;
  MxStatictext *okSel = MxStatictextNew(object, 0, 0, 0, 0, &textargs);
  okSel->base.object.handler = fileOpenOKSelectedHandler;
  MxHide(&okSel->base.object, MxTrue);

  /* Setup the file selector arguments */
  MxFileselectorArgs args;

  MxArgsInit(&args);
  args.file = (char *)textargs.caption;
  strcpy(args.file, "");
  args.pattern = "*.SCX;*.scx";
  args.attrib = FA_RDONLY | FA_DIREC;
  args.window.caption = "Select scene file";

  /* Start the file selector */
  MxFileselector *fs = MxFileselectorStart(&args, MxParent(object), &okSel->base.object);
  resizeFileSelector(fs);
}

static void resizeFileSelector(MxFileselector *fs) {
  /* Change the window size to fit the desktop size */
   MxObject *parent = MxParent(&fs->base.object);
  MxGeomSize(&fs->base.object, MxW(&fs->base.object), MxH(parent)/2);
  MxGeomPosition(&fs->base.object, fs->base.object.position.x1, MxH(parent)/4);
  MxEventSendSimple(&fs->base.object, MxEventGeomChanged);
  MxEnqueueRefresh(&fs->base.object, MxTrue);
}

static void fileExitHandler(MxObject * object, void *data, unsigned int selected) {
	if (selected) {
		MxEventSendSimple(MxParent(object), MxEventExit);
	}
}

// File | Open Filedialog OK selected
static void *fileOpenOKSelectedHandler(struct MxObject * object, const MxEvent * const event) {
  MxFileselector *sel = (MxFileselector *)event->object.object;
  MxStatictext *okSel	= (MxStatictext *)object;

  switch (event->type) {
  case MxEventOk: 
	  {
		// change dir
#ifdef WIN32
		char *lbs = strrchr((char *)okSel->caption, '/');
		if (lbs != NULL) {
			  *lbs='\0';
		}
		char *newDir= lbs == NULL ? NULL : strdup(okSel->caption);
		const char *fileName = lbs == NULL ? okSel->caption : ++lbs;
#else
		char *newDir = dirname(okSel->caption);
		const char *fileName = basename(okSel->caption);
#endif
		if (newDir != NULL) {
		  chdir(newDir);
		  free(newDir);
		}
		matedit->loadScene(fileName);
		MxDestroy(object);	// destroy okSel
	  }
	break;
  default:
	return MxStatictextHandler(object, event);
  }
  return 0;
}

static void *MatEditHandler(MxObject * object, const MxEvent * const event)
{
  switch (event->type) {

  case MxEventExpose:
    {

      /* Blit the Szene */
      for (int i = 0; i < MxRegionNumber(mx_region); i++) {
	const MxRect *const s = MxRegionRect(mx_region, i);

	int x1 = s->x1, y1 = s->y1, x2 = s->x2, y2 = s->y2;
	if (!MxClipRect(0, 0, 
			GrWidth(ctx) - 1,
			GrHeight(ctx) - 1,
			x1, y1, x2, y2)) {

	  MxBlitToScreenFast(ctx, NULL, 
			     x1, y1, x1, y1,
			     x2 - x1 + 1, y2 - y1 + 1);
	}
      }
      /* Fill the other side of screen */
      MxScreenRectFill(0, 
		       GrWidth(ctx),
		       object->position.y1, 
		       object->position.x2 - 1, 
		       object->position.y2 - 1,
		       MxColorDesktop);

    }
    break;

    /* Otherwise behave just as a regular desktop */
  default:
    return MxDesktopHandler(object, event);
  }
  return 0;
}

void *MatWinHandler(MxObject * object, const MxEvent * const event)
{
  switch (event->type) {

  case MatEditSceneChanged:
	matedit->OnChangedScene();

    break;

    /* Otherwise behave just as a regular window */
  default:
    return MxWindowHandler(object, event);
  }
  return 0;
}

static void *MxSliderStaticTextHandler(MxObject * object, const MxEvent * const event) {
  if (event->type == MxEventSlider) {
    static char buffer[10];
    char *caption = NULL;

    MxStatictext *st = (MxStatictext *)object;
    MxSlider *sl = ((MxEventSlidermove *)event)->source;
    itoa(sl->index, buffer, 10);

    caption = (char *)MxMalloc(strlen(buffer)+1);
    strcpy(caption, buffer);
    MxStatictextSet(st, caption, 1);

    MxEnqueueRefresh(&st->base.object, MxFalse);
  }
  /* Otherwise act just like a normal static text */
  return MxStatictextHandler(object, event);
}

// Texturefile selected
static void *TextureOKSelectedHandler(struct MxObject * object, const MxEvent * const event) {
  MxFileselector *sel = (MxFileselector *)event->object.object;
  MxStatictext *okSel	= (MxStatictext *)object;

  switch (event->type) {
  case MxEventOk:    
    matedit->loadTexture(okSel->caption);
    MxDestroy(object);	// destroy okSel
	break;
  default:
	return MxStatictextHandler(object, event);
  }
  return NULL;
}

// Button "Texture" pressed
static void TextureButtonHandler(MxObject * object, void *data, unsigned int selected) {
  MxButton *btn = (MxButton *) object;

  if (!selected)
    return;

  /* Text for filename */
  MxStatictextArgs textargs;
  MxArgsInit(&textargs);
  textargs.caption = (const char *)MxMalloc(MX_MAX_PATH);
  strcpy((char *)textargs.caption, "");
  textargs.len = 0;
  textargs.ownscaption = 1;
  MxStatictext *okSel = MxStatictextNew(&btn->base.object, 0, 0, 0, 0, &textargs);
  okSel->base.object.handler = TextureOKSelectedHandler;
  MxHide(&okSel->base.object, MxTrue);

  /* Setup the file selector arguments */
  MxFileselectorArgs args;

  MxArgsInit(&args);
  args.file = (char *)textargs.caption;
  strcpy(args.file, "");
  args.pattern = "*.pcx";
  args.attrib = FA_RDONLY | FA_DIREC;
  args.window.caption = "File Selector";

  /* Start the file selector */
  MxFileselector *fs = MxFileselectorStart(&args, MxParent(&btn->base.object), &okSel->base.object);
  resizeFileSelector(fs);
}

// Button "Reset Texture" pressed
static void ResetTextureButtonHandler(MxObject * object, void *data, unsigned int selected) {
  MxButton *btn = (MxButton *) object;

  if (!selected)
    return;
  matedit->resetTexture();
}

// Materialliste selektiert
static void MatSelectHandler(MxObject * object, void *data, unsigned int selected) {
  if (!selected)
    return;
  matedit->setMaterial((pl_Mat *)data);
  matedit->OnChangedScene();
}
//////////////////////////////////////////////////////////////////////////////
// Methoden
//

// Konstruktor
MatEdit::MatEdit(string filename) :
  filename(filename),
  scene(screen_w / 2, screen_h),
  matChanged(false),
  cam( NULL ),
  mat( NULL ),
  obj( NULL ),
  lastNewTexture_( 0 ) { 

    lastmessage[0] = '\0';
    MxAlertArgs args = { "Alert", lastmessage,
			 {"Ok", 0, MxFalse},
			 {NULL, 0, MxFalse},
			 {NULL, 0, MxFalse} };
    msgOk = args;

    // construct desktop
    createDesktop(&desktop);

    /* create the material editor */
    createMatWin(&desktop);

    // create image for scene
    char *memory[4] = {(char *)scene.getFrameBuffer(),0,0,0};
    ctx = (MxImage*)GrCreateContext(screen_w / 2,screen_h,memory,NULL);  
  }

// Erzeugt den Desktop
int MatEdit::createDesktop(MxDesktop *desktop)
{
  static MxButton button;
  /* Create some drivers specific to the system */
  static MxDriverSystem system = MxDriverSystemDefault;
  static MxDriverOutput output = MxDriverOutputDefault;
  static MxDriverInput input = MxDriverInputDefault;

  static MxDesktopArgs desktopargs;
  MxArgsInit(&desktopargs);

  desktopargs.desktop_w = screen_w;
  desktopargs.desktop_h = screen_h;
  desktopargs.desktop_c = 8;
  desktopargs.system = &system;
  desktopargs.output = &output;
  desktopargs.input = &input;
  desktopargs.window.caption = "";

  /* Initialize the library */
  MxDesktopConstruct(desktop, 0, 0, 0, 0, &desktopargs);
  if (!desktop->ok)
    return 1;

  GrResetColors(); // Palette mode
  GrColor *egacolors = GrAllocEgaColors();


  MxColorFore = egacolors[BLACK];
  MxColorBack = egacolors[LIGHTGRAY];
  MxColorObjectFore = egacolors[LIGHTBLUE];
  MxColorObjectBack = egacolors[BLUE];

  MxColorSelectedFore = egacolors[BLACK];
  MxColorSelectedBack = egacolors[LIGHTBLUE];

  MxColorLight = egacolors[WHITE];
  MxColorMed = egacolors[LIGHTGRAY];
  MxColorDark = egacolors[DARKGRAY];
  MxColorDesktop = egacolors[BLUE];
  MxColorFocus = egacolors[LIGHTBLUE];
  MxColorDisabled = egacolors[DARKGRAY];

  /* Tell the desktop to use our handler */
  desktop->base.object.handler = MatEditHandler;

  /* Make the menu */  
  MxMenuArgs menuargs;
  MxArgsInit(&menuargs);
  menuargs.listarea.def = mainMenu;
  MxMenu *menu = MxMenuNew(&desktop->base.object, 0, 0, MxDefault, MxDefault, &menuargs);
  MxResize(&menu->base.object, MxW(&desktop->base.object) - 2, MxDefault);
  return 0;
}

// erzeugt ein Fenster mit Slidern
void MatEdit::createMatWin(MxDesktop *desktop) {
  static char buffer[10];
  MxSlider *slider;
  MxStatictext *staticTextForSlider;

  MxWindowArgs windowargs;
  MxSliderArgs sliderargs;
  MxStatictextArgs textargs;
  MxRadioGroupArgs rbgargs;
  MxButtonArgs btnargs;
  MxButton *button;

  int col, row;
  int f_x1, f_w, f_y1, f_h;
  const char *sl_grp[] = {"Ambient", "Diffuse", "Specular"};

  /* Prepare some window arguments */
  MxArgsInit(&windowargs);
  windowargs.caption = "Material";
  windowargs.unresizeable = MxTrue;

  /* Add our window to the desktop  */
  matWin = MxWindowNew(&desktop->base.object, screen_w / 2, 0, screen_w / 2, screen_h, &windowargs);
  matWin->base.object.handler = MatWinHandler;

  /* Make some sliders */
  MxArgsInit(&sliderargs);
  sliderargs.range = 256;
  sliderargs.index = 126;
  sliderargs.thumb = 1;
  for (row = 0; row < 3; row++) {
    MxArgsInit(&rbgargs);
    rbgargs.caption = sl_grp[row];
    rbgargs.len = strlen(rbgargs.caption);
    f_x1 = 5;
    f_w = 100;
    f_y1 = 5 + (145*row);
    f_h = 135;
    MxRadioGroupNew(matWin->client, f_x1, f_y1, f_w, f_h, &rbgargs);
    for (col = 0; col < 3; col++) {
      slider = MxSliderVNew(matWin->client, 15 + (30*col), 20 + (145*row), MxDefault, 90, &sliderargs);

      switch (row) {
      case 0:
	sliderAmbient[col] = slider;
	break;
      case 1:
	sliderDiffuse[col] = slider;
	break;
      case 2:
	sliderSpecular[col] = slider;
	break;
      default:
	assert (row<3);
      }

      /* Display the count */
      MxArgsInit(&textargs);
      sprintf(buffer,"%3d",slider->index); 
      textargs.caption = (const char *)MxMalloc(strlen(buffer)+1);
      strcpy((char *)textargs.caption, buffer);
      textargs.ownscaption = 1;
      textargs.len = strlen(textargs.caption);
      textargs.just = (MxStatictextJustify) (MxJustifyVCenter | MxJustifyHCenter);
      staticTextForSlider = MxStatictextNew(matWin->client, 7 + (30*col), 115 + (145*row), MxDefault, MxDefault, &textargs);

      /* Make the slider call the text update handler */
      slider->target = &staticTextForSlider->base.object;   // send MxEventSlider to target staticTextForSlider
      staticTextForSlider->base.object.handler = MxSliderStaticTextHandler;
    }
  }

  // Shininess / Transparent
  const char *sl_grp2[] = {"Shin Transp", "Fad TxSc Per"};
  MxSlider **sliderInit[2][3] = {
	  {&sliderShininess, &slider, &sliderTransparent},
	  {&sliderFadeDist, &sliderTexScaling, &sliderPerspectiveCorrect}
	};
  for (row = 0; row < 2; row++) {
    MxArgsInit(&rbgargs);
    rbgargs.caption = sl_grp2[row];
    rbgargs.len = strlen(rbgargs.caption);
    f_x1 = 110;
    f_y1 = 5 + (145*row);
    MxRadioGroupNew(matWin->client, f_x1, f_y1, f_w, f_h, &rbgargs);
    for (col = 0; col < 3; col++) {
		if (row==0 && col == 1)
			continue;
		if (col==0 && row==1) {
		  sliderargs.range = 10000;
		} else {
		  sliderargs.range = 0;
		}
		slider = MxSliderVNew(matWin->client, 125 + (30*col), 20 + (145*row), MxDefault, 90, &sliderargs);
		*sliderInit[row][col] = slider;

		/* Display the count */
		MxArgsInit(&textargs);
		sprintf(buffer,"%3d",slider->index); 
		textargs.caption = (const char *)MxMalloc(strlen(buffer)+1);
		strcpy((char *)textargs.caption, buffer);
		textargs.ownscaption = 1;
		textargs.len = strlen(textargs.caption);
		textargs.just = (MxStatictextJustify) (MxJustifyVCenter | MxJustifyHCenter);
		staticTextForSlider = MxStatictextNew(matWin->client, 117 + (30*col), 115 + (145*row), MxDefault, MxDefault, &textargs);

		/* Make the slider call the text update handler */
		slider->target = &staticTextForSlider->base.object;   // send MxEventSlider to target staticTextForSlider
		staticTextForSlider->base.object.handler = MxSliderStaticTextHandler;
	}
  }

  // Shade modes
  const char *sl_grp3[] = {"None", "Flat", "Flt Dist", "Gouraud", "Grd Dist"};
  MxButton **btnInit[] = {
	  &radioNone, &radioFlat, &radioFlatDistance, &radioGouraud, &radioGouraudDistance
  };
  MxArgsInit(&btnargs);
  MxArgsInit(&rbgargs);
  rbgargs.caption = "Shade modes";
  rbgargs.len = strlen(rbgargs.caption);
  f_x1 = 215;
  f_y1 = 5;
  MxRadioGroup *group = MxRadioGroupNew(matWin->client, f_x1, f_y1, f_w, f_h, &rbgargs);
  for (row = 0; row < 5; row++) {
	btnargs.stext.caption = sl_grp3[row];
	*btnInit[row] = MxRadioButtonNew(&group->base.object, 10, 16 + (row*25), MxDefault, MxDefault, &btnargs);
  }

  // Materialienliste
  MxListArgs listargs;
  MxArgsInit(&listargs);
  matList = MxListNew(matWin->client, 215, 150, f_w, f_h, &listargs);

  // Textures
  // Button
  MxArgsInit(&btnargs);
  btnargs.stext.caption = "Texture";
  btnargs.callback = TextureButtonHandler;
  button = MxPushButtonNew(matWin->client, 110, 301, MxDefault, MxDefault, &btnargs);
  // Text
  MxArgsInit(&textargs);
  textargs.caption = strdup(string(texTextLen,' ').c_str());
  textargs.len = strlen(textargs.caption);
  textargs.ownscaption = MxTrue;
  textargs.just = (MxStatictextJustify) (MxJustifyVCenter | MxJustifyHCenter);
  staticTextTexture = MxStatictextNew(matWin->client, 115, 326, 200, MxDefault, &textargs);
  // Reset Button
  MxArgsInit(&btnargs);
  btnargs.stext.caption = "Reset";
  btnargs.callback = ResetTextureButtonHandler;
  button = MxPushButtonNew(matWin->client, 220, 301, MxDefault, MxDefault, &btnargs);
}

// MatEdit aktualisieren nach GUI Änderungen
//
void MatEdit::updateMatWin() {
  if (mat) {
	  for (int col=0; col<3; col++) {
		matChanged |= (mat->Ambient[col] != sliderAmbient[col]->index);
		mat->Ambient[col] = sliderAmbient[col]->index;

		matChanged |= (mat->Diffuse[col] != sliderDiffuse[col]->index);
		mat->Diffuse[col] = sliderDiffuse[col]->index;

		matChanged |= (mat->Specular[col] != sliderSpecular[col]->index);
		mat->Specular[col] = sliderSpecular[col]->index;
	  }

	  matChanged |= (mat->Shininess != sliderShininess->index);
	  mat->Shininess = sliderShininess->index;

	  matChanged |= (mat->Transparent != sliderTransparent->index);
	  mat->Transparent = sliderTransparent->index;

	  matChanged |=  (mat->FadeDist != sliderFadeDist->index);
	  mat->FadeDist = sliderFadeDist->index;

	  matChanged |=  (mat->TexScaling != sliderTexScaling->index);
	  mat->TexScaling = sliderTexScaling->index;

	  matChanged |=  (mat->PerspectiveCorrect != sliderPerspectiveCorrect->index);
	  mat->PerspectiveCorrect = sliderPerspectiveCorrect->index;

	  int shadeType = radio2ShadeType();
	  matChanged |= (mat->ShadeType != shadeType);
	  mat->ShadeType = shadeType;
  }

  if (matChanged) {
    matChanged = false;
	if (mat) {
		plMatInit(mat);
		reloadPalette();
	}
	if (cam) {
		scene.render();
		list<string> l;
		dumpMaterial(mat, l);
		printLines(cam, l);		
		plTextPrintf(cam,cam->ClipLeft+5,cam->ClipBottom-15, 0.0,CTextColor,
		 (pl_sChar *)lastmessage);
	} else {
	  GrSetContext((GrContext2*)ctx);
	  GrClearContext( MxColorDesktop );
	  GrTextXY(5,((GrContext2*)ctx)->gc_ymax-15,lastmessage,GrBlack(),MxColorDesktop);
	  GrSetContext(NULL);
	}
    MxRefresh(&desktop.base.object);
  }
}

// MatWin aktualisieren nach Scene Änderungen
//
void MatEdit::OnChangedScene() {
    MxEvent event;
    event.type = MxEventSlider;
    event.slider.offset = 0;
  
    for (int col = 0; col < 3; col++) {
		mx_slider_scroll_to(sliderAmbient[col], mat ? mat->Ambient[col] : 126);
		mx_slider_scroll_to(sliderDiffuse[col], mat ? mat->Diffuse[col] : 126);
		mx_slider_scroll_to(sliderSpecular[col], mat ? mat->Specular[col] : 126);
    }
	mx_slider_scroll_to(sliderShininess, mat ? mat->Shininess : 126);
	mx_slider_scroll_to(sliderTransparent, mat ? mat->Transparent : 126);
	mx_slider_scroll_to(sliderFadeDist, mat ? (int)mat->FadeDist : 10000);
	mx_slider_scroll_to(sliderTexScaling, mat ? (int)mat->TexScaling : 0);
	mx_slider_scroll_to(sliderPerspectiveCorrect, mat ? mat->PerspectiveCorrect : 0);
	if (mat) {
		shadeType2Radio(mat->ShadeType);
	}
	if (!mat) {
		MxListDefSet(&matList->listarea, 0, MxFalse);;
	}
	if (mat) {
		reloadPalette();
	}
	if (cam) {
		scene.render();
		list<string> l;
		dumpMaterial(mat, l);
		printLines(cam, l);		
		plTextPrintf(cam,cam->ClipLeft+5,cam->ClipBottom-15, 0.0,CTextColor,
		 (pl_sChar *)lastmessage);
	}
	MxRefresh(&desktop.base.object);
}

//
// shadeType -> Radio
void MatEdit::shadeType2Radio(int shadeType) {
	MxButton *btn = NULL;
	switch (shadeType) {
		case PL_SHADE_NONE:
			btn = radioNone;
			break;
		case PL_SHADE_FLAT:
			btn = radioFlat;
			break;
		case PL_SHADE_FLAT_DISTANCE:
			btn = radioFlatDistance;
			break;
		case PL_SHADE_GOURAUD:
			btn = radioGouraud;
			break;
		case PL_SHADE_GOURAUD_DISTANCE:
			btn = radioGouraudDistance;
			break;
	}
    MxEventSendSimple(&btn->base.object, MxEventSelect);
}

// Radio -> shadeType
int MatEdit::radio2ShadeType() {
	int shadeType;
	if (radioNone->pressed)
		shadeType = PL_SHADE_NONE;
	else if (radioFlat->pressed)
		shadeType = PL_SHADE_FLAT;
	else if (radioFlatDistance->pressed)
		shadeType = PL_SHADE_FLAT_DISTANCE;
	else if (radioGouraud->pressed)
		shadeType = PL_SHADE_GOURAUD;
	else if (radioGouraudDistance->pressed) 
		shadeType = PL_SHADE_GOURAUD_DISTANCE;
	return shadeType;
}


inline void checkPal() {
#if 0
  int r,g,b;
  for (int i = CWinColors; i < 256; ++i) {
    GrQueryColor(i,&r,&g,&b);
    assert(!(r==255 && g==0 && b==0));
  }
#endif
}
void MatEdit::printLines(const pl_Cam *cam, const list<string> &lines)
{
  list<string>::const_iterator it;
  int i;
  for (it = lines.begin(), i = 0; it != lines.end(); ++it, i += 11) {
    plTextPutStr(const_cast<pl_Cam *>(cam), 5, 20 + i, 0.0, 
		 CTextColor, (pl_sChar *)it->c_str());
  }
}

void MatEdit::dumpMaterial(pl_Mat *mat, list<string> &l) {
  ostringstream buf;

  l.clear();
  if (mat) {
    buf << "A:" << setw(4) << mat->Ambient[0] << setw(4) << mat->Ambient[1] << setw(4) << mat->Ambient[2] << ends;
    l.push_back(buf.str()); buf.seekp(0);
    buf << "D:" << setw(4) << mat->Diffuse[0] << setw(4) << mat->Diffuse[1] << setw(4) << mat->Diffuse[2] << ends;
    l.push_back(buf.str()); buf.seekp(0);
    buf << "S:" << setw(4) << mat->Specular[0] << setw(4) << mat->Specular[1] << setw(4) << mat->Specular[2] << ends;
    l.push_back(buf.str()); buf.seekp(0);
    buf << "Shininess:" << setw(4) << mat->Shininess << ends;
    l.push_back(buf.str()); buf.seekp(0);
    buf << "Transparent:" << setw(4) << (int)mat->Transparent << ends;
    l.push_back(buf.str()); buf.seekp(0);
    buf << "FadeDistance:" << setw(4) << (int)mat->FadeDist << ends;
    l.push_back(buf.str()); buf.seekp(0);
    buf << "TexScaling:" << setw(4) << (int)mat->TexScaling << ends;
    l.push_back(buf.str()); buf.seekp(0);
    buf << "PerspectiveCorrect:" << setw(4) << (int)mat->PerspectiveCorrect << ends;
    l.push_back(buf.str()); buf.seekp(0);
  } else {
    buf << "Kein Material ausgewählt." << ends;
    l.push_back(buf.str()); buf.seekp(0);
  }
}

// Palette neu laden
void MatEdit::reloadPalette() 
{
  int i;
  // Fixed colors
  for (i = CWinColors; i < CFixColors; ++i) {
    GrSetColor(i, 0, 0, 0);
  }
  GrSetColor(CTextColor, 0, 192, 0); // Textcolor
  checkPal();

  scene.makePalette(ThePalette, CFixColors, 255);
  for (i = CFixColors; i < 256; i++) {
    GrSetColor(i, ThePalette[ i*3 ], ThePalette[ i*3 + 1], ThePalette[ i*3 + 2 ]);
    checkPal();
  }
}

// Szene löschen
void MatEdit::newScene() {
	scene.clear();
	filename = "unnamed";
	cam =  NULL;
	mat = NULL;
	obj = NULL;


    MxEventSendSimple(&matWin->base.object, (MxEventType)MatEditSceneChanged);
	matChanged = true;
	strcpy(lastmessage, "Scene cleared.");
}

// Szene neu laden
void MatEdit::loadScene(const string &filename) {
  try {
    scene.loadXML(filename);

    cam = scene.getCurrCamera();
    const Scene::ObjMap *objMap = scene.getAllObjects();

    if (objMap->empty()) {
      strcpy(lastmessage, "No objects found.");
      MxAlertStart(&msgOk, &desktop.base.object);
      return;
    }
	const Scene::MatMap *matMap = scene.getAllMaterials();
    if (matMap->empty()) {
      strcpy(lastmessage, "No materials found.");
      MxAlertStart(&msgOk, &desktop.base.object);
      return;
    }
    mat = matMap->begin()->second; // material of object

	MxListDef *def = (MxListDef *)malloc((matMap->size() + 1) * sizeof(MxListDef));
	memset(def, 0, (matMap->size() + 1) * sizeof(MxListDef));
	int i = 0;
	Scene::MatMap::const_iterator it;
	for (it = matMap->begin(); it != matMap->end(); ++it) {
		def[i].caption = it->first.c_str();
		def[i].data = it->second;
		def[i].callback = MatSelectHandler;
		def[i].selected = i == 0;
		i++;
	}
	MxListDefSet( &matList->listarea, def, MxTrue);
	
    this->filename = filename; // filename of scene

    MxEventSendSimple(&matWin->base.object, (MxEventType)MatEditSceneChanged);
    matChanged = true;
    strcpy(lastmessage, (string(filename) + " loaded.").c_str());
  } catch (Scene::IOError &) {
    ostringstream msg;
    msg << filename << ": file not found"; 
    strcpy(lastmessage, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop.base.object);
    return;
  } catch (Scene::ParseError &pe) {
    ostringstream msg;
    msg << filename << ':' << pe.getLine() << ": error: " << pe.what(); 
    strcpy(lastmessage, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop.base.object);
    return;
  }
}

// Textur des ausgewählten Materials neu laden
void MatEdit::loadTexture(const string &filename) {
  try {
    pl_Texture *tex = plReadPCXTex((char *)filename.c_str(), true, true);

    Scene::TextureMap *texMap= scene.getAllTextures();

    ostringstream texName;
    texName << "tex" << ++lastNewTexture_;
    texMap->insert(make_pair(texName.str(), tex));
    
    // apply to material
    if (mat) {
      mat->Texture = tex;
    }
    // update texture text
	int cutPos = MX_MAX(0,(int)(filename.length()-texTextLen));
    string texText = string(cutPos == 0 ? "" : "..") + filename.substr(cutPos);
    char *caption = (char *)MxMalloc(texText.length() + 1);
    strcpy(caption, texText.c_str());
    MxStatictextSet(staticTextTexture, caption, 1);
	MxEnqueueRefresh(&staticTextTexture->base.object, MxFalse);

    matChanged = true;
    strcpy(lastmessage, (string("Texture ") + filename + " loaded.").c_str());
  } catch (Scene::IOError &) {
    ostringstream msg;
    msg << filename << ": file not found"; 
    strcpy(lastmessage, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop.base.object);
    return;
  } catch (Scene::ParseError &pe) {
    ostringstream msg;
    msg << filename << ':' << pe.getLine() << ": error: " << pe.what(); 
    strcpy(lastmessage, msg.str().c_str());
    MxAlertStart(&msgOk, &desktop.base.object);
    return;
  }
}

// Textur des ausgewählten Materials entfernen
void MatEdit::resetTexture() {
    // apply to material
    if (mat) {
      mat->Texture = NULL;
    }
    MxStatictextSet(staticTextTexture, "", 0);
	MxEnqueueRefresh(&staticTextTexture->base.object, MxFalse);

    matChanged = true;
    strcpy(lastmessage, "Texture reset.");
}

// Ausgabe der Szene und der GUI
void MatEdit::run() {
  char lastmessage[80] = "";
  int width=screen_w, height=screen_h, bpp=BPP;
  bool sceneToLoad = filename != "";

  /* Run the desktop until it wants to exit */
  clock_t oldclk = clock();
  clock_t newclk;

  while (MxDesktopRun(&desktop)) {
    newclk = clock();  
    if (((newclk - oldclk)*1000/CLOCKS_PER_SEC) > refresh_ivl) {
      oldclk = newclk;
	  updateMatWin();
    }

	if (sceneToLoad) {
		sceneToLoad=false;
		loadScene(this->filename);
		matChanged = true; // Material wurde geändert
	}
  }
  /* Close and go home */
  MxDestroy(&desktop.base.object);
  GrSetMode( GR_default_text );
}

//////////////////////////////////////////////////////////////////////////////
// Hauptfunktion
//
extern "C" int
GRXMain(int argc, char **argv)
{
  try 
    {
      if (argc > 2) {
		cerr << "Usage: " << argv[0] << " [scene.scx]" << endl;
		return 1;
      }
      memset(ThePalette, 0, sizeof ThePalette);

      const char *filename = (argc == 2) ? argv[1] : defFileName;
      // Rendering
      cout << "Start rendering" << endl;
      matedit = new MatEdit(filename);
      matedit->run();
      delete matedit;
    }
  catch (exception &e) 
    {
      GrSetMode( GR_default_text );
      cerr << "Exception: " << e.what( ) << endl;
    };
  return 0;
}
