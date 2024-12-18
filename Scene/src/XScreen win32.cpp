// Copyright (c) 2024, Steffen Buchholz

#include <Windows.h>
#include "scenedbg.h"
#include "XScreen.h"

extern int main(int argc, char* argv[]);


void scene::ScreenResolution(int *width, int *height)
{
	*width = GetSystemMetrics(SM_CXSCREEN);
	*height = GetSystemMetrics(SM_CYSCREEN);
}

bool scene::FullScreen(bool fullscreen) {
    return true;
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return main(__argc, __argv);
}
