
#include "Globals.h"
#include <windows.h>

#ifndef _JTRACERHANDLERS_H_
#define _JTRACERHANDLERS_H_

LRESULT OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
LRESULT OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
LRESULT OnLineRendered(HWND hwnd);
LRESULT OnClose(HWND hwnd);
LRESULT OnDestroy(HWND hwnd);

#endif
