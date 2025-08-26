
#include "JTracerWindow.h"
#include "JTracerHandlers.h"
#include "RenderThread.h"

ATOM InitJTracerWindow()
{
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = JTRACERWINDOWCLASS;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wc);
}

HWND CreateJTracerWindow()
{
	InitJTracerWindow();

	RECT rcWindow = {0};
	rcWindow.right = 770;
	rcWindow.bottom = 522;

	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION;

	AdjustWindowRectEx(&rcWindow, dwStyle, FALSE, dwExStyle);

	HWND hwnd = CreateWindowEx(dwExStyle, JTRACERWINDOWCLASS, _T("JTracer v0.2"),
		dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rcWindow.right-rcWindow.left, rcWindow.bottom - rcWindow.top,
		NULL, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);

	return hwnd;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CREATE: return OnCreate(hwnd, (LPCREATESTRUCT)lParam);

		case WM_COMMAND: return OnCommand(hwnd, (int)LOWORD(wParam), (HWND)lParam, (UINT)HIWORD(wParam));

		case WM_THREADSTARTED: return OnThreadStarted(hwnd);

		case WM_THREADFINISHED: return OnThreadFinished(hwnd);

		case WM_LINERENDERED: return OnLineRendered(hwnd);

		case WM_CLOSE: return OnClose(hwnd);

		case WM_DESTROY: return OnDestroy(hwnd);

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
