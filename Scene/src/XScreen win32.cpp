// Copyright (c) 2024, Steffen Buchholz

#include <Windows.h>
extern "C" {
#include <../src/include/libwin32.h>
}
#include "scenedbg.h"
#include "XScreen.h"

extern int main(int argc, char* argv[]);


void scene::ScreenResolution(int *width, int *height)
{
	*width = GetSystemMetrics(SM_CXSCREEN);
	*height = GetSystemMetrics(SM_CYSCREEN);
}

bool scene::FullScreen(bool fullscreen) {
    LONG lStyle = GetWindowLong(hGRXWnd, GWL_STYLE);
    lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
    SetWindowLong(hGRXWnd, GWL_STYLE, lStyle);
    LONG lExStyle = GetWindowLong(hGRXWnd, GWL_EXSTYLE);
    lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
    SetWindowLong(hGRXWnd, GWL_EXSTYLE, lExStyle);
    SetWindowPos(hGRXWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    return true;
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return main(__argc, __argv);
}
