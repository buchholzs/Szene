// Copyright (c) 2024, Steffen Buchholz

#include <X11/Xlib.h>
#include "ScreenResolution.h"

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
