
#include "Globals.h"
#include <windows.h>

#ifndef _JTRACERWINDOW_H_
#define _JTRACERWINDOW_H_

#define JTRACERWINDOWCLASS _T("JTracer")

ATOM InitJTracerWindow();
HWND CreateJTracerWindow();
static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
