
#include "JTracerHandlers.h"

//////////////////////////////////////////////////////////////////////

HWND g_hImage;
HWND g_hStartStop;
BOOL g_bRunning;

HBITMAP g_hbmBitmap;

//////////////////////////////////////////////////////////////////////

HWND CreateWindowAdjustFontEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	RECT rcWnd = {0};
	rcWnd.right = nWidth;
	rcWnd.bottom = nHeight;

	AdjustWindowRectEx(&rcWnd, dwStyle, ((hMenu) ? TRUE : FALSE), dwExStyle);

	HWND hwnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle,
		x + rcWnd.left, y + rcWnd.top,
		rcWnd.right - rcWnd.left,
		rcWnd.bottom - rcWnd.top,
		hWndParent, hMenu, hInstance, lpParam);

	if (hwnd)
		SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE);

	return hwnd;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	DWORD dwExStyle;
	DWORD dwStyle;

	// Create Render Display Window
	dwExStyle = WS_EX_CLIENTEDGE;
	dwStyle = WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_BITMAP;
	g_hImage = CreateWindowAdjustFontEx(dwExStyle, _T("STATIC"), _T(""), dwStyle,
		10, 10, 640, 480, hwnd, NULL, lpCreateStruct->hInstance, NULL);

	// Create Start/Stop Button
	dwExStyle = WS_EX_CLIENTEDGE;
	dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
	g_hStartStop = CreateWindowAdjustFontEx(dwExStyle, _T("BUTTON"), _T("Start"), dwStyle,
		662, 10, 100, 21, hwnd, NULL, lpCreateStruct->hInstance, NULL);

	g_bRunning = FALSE;

	// Create 'Credit' Static
	dwExStyle = 0;
	dwStyle = WS_CHILD | WS_VISIBLE | WS_DISABLED | SS_LEFT;
	CreateWindowAdjustFontEx(dwExStyle, _T("STATIC"), _T("JTracer - By Joel Sheehan"), dwStyle,
		10, 500, 200, 14, hwnd, NULL, lpCreateStruct->hInstance, NULL);

	// Load Sample Picture
	g_hbmBitmap = (HBITMAP)LoadImage(lpCreateStruct->hInstance, _T("image.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	return 0;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (hwndCtl == g_hStartStop && codeNotify == BN_CLICKED)
	{
		if (g_bRunning)
		{
			SetWindowText(g_hStartStop, _T("Start"));
			g_bRunning = FALSE;

			SendMessage(g_hImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)NULL);
		}
		else
		{
			SetWindowText(g_hStartStop, _T("Stop"));
			g_bRunning = TRUE;

			if (g_hbmBitmap)
				SendMessage(g_hImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g_hbmBitmap);
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////

/*
LRESULT OnLineRendered(HWND hwnd)
{
	UpdateRaster();

	hbmOldRaster = (HBITMAP)SendMessage(g_hImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g_hbmRaster);
	if (hbmOldRaster != g_hbmRaster && hbmOldRaster != NULL)
	{
		DeleteObject(hbmOldRaster);
	}

	return 0;
}
*/

//////////////////////////////////////////////////////////////////////

LRESULT OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);

	return 0;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnDestroy(HWND hwnd)
{
	if (g_hbmBitmap)
		DeleteObject(g_hbmBitmap);

	PostQuitMessage(0);

	return 0;
}

//////////////////////////////////////////////////////////////////////
