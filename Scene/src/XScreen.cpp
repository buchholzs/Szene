// Copyright (c) 2024, Steffen Buchholz

#include <X11/Xlib.h>
#include <../src/include/libxwin.h>
#include "XScreen.h"
#include "scenedbg.h"

void scene::ScreenResolution(int *width, int *height)
{

    Display *display;
    Screen *screen;

    // open a display
    display = XOpenDisplay(NULL);

    // return the number of available screens
    int count_screens = ScreenCount(display);

    for (int i = 0; i < count_screens; ++i) {
        screen = ScreenOfDisplay(display, i);
        *width = screen->width;
        *height = screen->height;
        break;
    }

    // close the display
    XCloseDisplay(display);
}

bool scene::FullScreen(bool fullscreen) {
    // Benötigte Atome bestimmen
    Atom wm_state = XInternAtom(_XGrDisplay, "_NET_WM_STATE", False);
    Atom wm_fullscreen = XInternAtom(_XGrDisplay, "_NET_WM_STATE_FULLSCREEN", False);

    // Überprüfen, ob die benötigten Atome vorhanden sind
    if(wm_state == None || wm_fullscreen == None) {
        DBGPRINTF(("Fenstermanager unterstützt kein Vollbildmodus!"));    
        return false;
    }

    // Ein ClientMessage Event konstruieren welches das Fenster in den gewünschten Zustand bringt
    XEvent xev;
    xev.type = ClientMessage;
    xev.xclient.display = _XGrDisplay;
    xev.xclient.window = _XGrWindow;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;

    // Folgende Konstanten müssen definiert sein
    const int _NET_WM_STATE_REMOVE = 0;
    const int _NET_WM_STATE_ADD = 1;
    const int EVENT_SOURCE_APPLICATION = 1;

    if(fullscreen) {
        xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
    }
    else {
        xev.xclient.data.l[0] = _NET_WM_STATE_REMOVE;
    }
    xev.xclient.data.l[1] = wm_fullscreen;
    xev.xclient.data.l[2] = 0;
    xev.xclient.data.l[3] = EVENT_SOURCE_APPLICATION; // Bedeutet, dass das Event von der Applikation kommt
    xev.xclient.data.l[4] = 0;

    // Event Empfänger und Eventmaske setzen
    Window x11_root_window = XRootWindow(_XGrDisplay, _XGrScreen);
    long event_mask = SubstructureRedirectMask;

    // Event senden
    int evt_success = XSendEvent(_XGrDisplay, x11_root_window, False, event_mask, &xev);

    // Überprüfen, ob das Event erfolgreich gesendet wurde
    if(!evt_success) {
        DBGPRINTF(("set_window_scene::FullScreen: Fehler beim Versenden des X11 Events!"));

        return false;
    }

    return true;
}