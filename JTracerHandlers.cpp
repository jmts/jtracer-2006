
#include "JTracerHandlers.h"
#include "RenderThread.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Primitive.h"
#include "PointLight.h"
#include <cmath>
#include <vector>

//////////////////////////////////////////////////////////////////////

HWND g_hImage;
HWND g_hStartStop;
BOOL g_bRunning;

HBITMAP g_hbmRaster;
int g_nLinesUpdated;
int g_nRasterWidth;
int g_nRasterHeight;

RenderThread g_tRender;

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

std::vector<Primitive*>g_vPrimitives;

std::vector<PointLight*>g_vLights;

/*
int LoadScene()
{
	Scene s;
	s.setAmbientLight(Color(1.0, 1.0, 1.0));

	Color cColor;
	Material mMaterial;
	Primitive *pPrimitive;

	// Red Sphere
	mMaterial = Material(Color(1.0, 0.0, 0.0), 0.1, 1.0, 1.0);
	pPrimitive = new Sphere(Vector(-1, 0, 0), 0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);
	
	// Green Sphere
	mMaterial = Material(Color(0.0, 1.0, 0.0), 0.1, 1.0, 1.0);
	pPrimitive = new Sphere(Vector(0, 0, 0), 0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);

	// Blue Sphere
	mMaterial = Material(Color(0.0, 0.0, 1.0), 0.1, 1.0, 1.0);
	pPrimitive = new Sphere(Vector(1, 0, 0), 0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);

	// White Plane
	mMaterial = Material(Color(1.0, 1.0, 1.0), 0.1, 1.0, 1.0);
	pPrimitive = new Plane(Vector(0, 1, 0), -0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);

	// Light
	PointLight *lLight = new PointLight(Color(1.0, 1.0, 1.0), Vector(0.0, 5.0, -15.0));
	s.addLight(lLight);
	g_vLights.push_back(lLight);

	lLight = new PointLight(Color(1.0, 1.0, 1.0), Vector(15.0, 5.0, 0.0));
	s.addLight(lLight);
	g_vLights.push_back(lLight);

	g_tRender.setScene(s);

	// Set Camera
	Vector vPosition(1.0f, 0.75f, -5.0f);
	Vector vLookAt(0.0f, 0.0f, 0.0f);
	Vector vLook = (vLookAt - vPosition).unit();
	float fAspect = 4.0f/3.0f;
	float fAngleOfView = M_PI/3.4f;
	Camera cCamera(vPosition, vLook, fAspect, fAngleOfView);
	g_tRender.setCamera(cCamera);

	return 0;
}
*/

int LoadScene()
{
	Scene s;
	s.setAmbientLight(Color(1.0, 1.0, 1.0));

	Color cColor;
	Material mMaterial;
	Primitive *pPrimitive;

	// Red Sphere
	mMaterial = Material(Color(1.0, 0.0, 0.0), 0.1, 0.6, 1.0);
	pPrimitive = new Sphere(Vector(-1, 0, 0), 0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);
	
	// Green Sphere
	mMaterial = Material(Color(0.0, 1.0, 0.0), 0.1, 0.6, 1.0);
	pPrimitive = new Sphere(Vector(0, 0, 0), 0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);

	// Blue Sphere
	mMaterial = Material(Color(0.0, 0.0, 1.0), 0.1, 0.6, 1.0);
	pPrimitive = new Sphere(Vector(1, 0, 0), 0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);

	mMaterial = Material(Color(1.0, 1.0, 1.0), 0.1, 0.6, 1.0);
	pPrimitive = new Plane(Vector(0, 1, 0), -0.5);
	pPrimitive->setMaterial(mMaterial);
	s.addPrimitive(pPrimitive);
	g_vPrimitives.push_back(pPrimitive);

	// Light
	PointLight *lLight = new PointLight(Color(1.0, 1.0, 1.0), Vector(10.0, 10.0, -10.0));
	s.addLight(lLight);
	g_vLights.push_back(lLight);

	lLight = new PointLight(Color(1.0, 1.0, 1.0), Vector(-20.0, 10.0, -5.0));
	s.addLight(lLight);
	g_vLights.push_back(lLight);

	g_tRender.setScene(s);

	// Set Camera
	Vector vPosition(1.0f, 2.0f, -5.0f);
	Vector vLookAt(0.0f, 0.0f, 0.0f);
	//Vector vPosition(0.5f, 0.0f, -1.0f);
	//Vector vLookAt(0.5f, 0.0f, 0.0f);
	Vector vLook = (vLookAt - vPosition).unit();
	float fAspect = 4.0f/3.0f;
	float fAngleOfView = M_PI/4.0f;
	Camera cCamera(vPosition, vLook, fAspect, fAngleOfView);
	g_tRender.setCamera(cCamera);

	return 0;
}

int FreeScene()
{
	for (size_t i = 0; i < g_vPrimitives.size(); i++)
	{
		Primitive *p = g_vPrimitives.at(i);
		delete p;
	}

	for (size_t i = 0; i < g_vLights.size(); i++)
	{
		PointLight *l = g_vLights.at(i);
		delete l;
	}

	return 0;
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

	g_tRender.setNotifyWindow(hwnd);
	g_tRender.setDimensions(640, 480);

	g_hbmRaster = NULL;
	g_nLinesUpdated = 0;
	g_nRasterWidth = 0;
	g_nRasterHeight = 0;

	LoadScene();

	return 0;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (hwndCtl == g_hStartStop && codeNotify == BN_CLICKED)
	{
		if (!g_bRunning)
		{
			if (g_tRender.getStatus() != TS_READY)
				g_tRender.reset();

			// Start And Wait For Notify From Thread
			int ret;
			if ((ret = g_tRender.start()) == 0)
			{
				SetWindowText(g_hStartStop, _T("Starting"));

				EnableWindow(g_hStartStop, FALSE);
			}
			else
			{
				switch(ret)
				{
					case 1:  MessageBox(hwnd, _T("1!"), _T("1!"), MB_OK); break;
					case 2:  MessageBox(hwnd, _T("2!"), _T("2!"), MB_OK); break;
					default: MessageBox(hwnd, _T("Oh No!"), _T("Oh No!"), MB_OK); break;
				}
			}
		}
		else
		{
			if (g_tRender.stop() == 0)
			{
				SetWindowText(g_hStartStop, _T("Stopping"));

				EnableWindow(g_hStartStop, FALSE);
			}
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnThreadStarted(HWND hwnd)
{
	SetWindowText(g_hStartStop, _T("Stop"));

	EnableWindow(g_hStartStop, TRUE);

	g_bRunning = TRUE;

	g_nLinesUpdated = 0;

	// Check Bitmap Size
	int nWidth, nHeight;
	g_tRender.getDimensions(nWidth, nHeight);
	if (g_hbmRaster && (nWidth != g_nRasterWidth || nHeight != g_nRasterHeight))
	{
		DeleteObject(g_hbmRaster);
		g_hbmRaster = NULL;
	}

	// Create Bitmap
	if (g_hbmRaster == NULL)
	{
		HDC hdc = CreateCompatibleDC(NULL);
	
		BITMAPINFOHEADER bmih = {0};
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = nWidth;
		bmih.biHeight = nHeight;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB;

		g_hbmRaster = CreateDIBSection(hdc, (BITMAPINFO*)&bmih, DIB_RGB_COLORS, NULL, NULL, NULL);

		g_nRasterWidth = nWidth;
		g_nRasterHeight = nHeight;

		if (!g_hbmRaster)
			MessageBox(hwnd, _T("Oh Shit"), _T("Oh Shit"), MB_OK);

		DeleteDC(hdc);

		HBITMAP hbmBlah = (HBITMAP)SendMessage(g_hImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g_hbmRaster);
		if (hbmBlah != g_hbmRaster)
			DeleteObject(hbmBlah);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnThreadFinished(HWND hwnd)
{
	// Clean Up
	SetWindowText(g_hStartStop, _T("Waiting"));
	g_tRender.wait();

	// Reset Controls
	SetWindowText(g_hStartStop, _T("Start"));
	g_bRunning = FALSE;
	EnableWindow(g_hStartStop, TRUE);

	return 0;
}

LRESULT OnLineRendered(HWND hwnd)
{
	float *fRed = new float[g_nRasterWidth];
	float *fGreen = new float[g_nRasterWidth];
	float *fBlue = new float[g_nRasterWidth];

	HDC hdc = CreateCompatibleDC(NULL);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdc, g_hbmRaster);

	int nRed, nGreen, nBlue;

	int nLines = g_tRender.getLinesComplete();

	for (int y = g_nLinesUpdated; y < nLines; y++)
	{
		g_tRender.getLine(y, fRed, fGreen, fBlue, g_nRasterWidth);
		for (int x = 0; x < g_nRasterWidth; x++)
		{
			nRed   = fRed[x]   * 255.0f;
			nGreen = fGreen[x] * 255.0f;
			nBlue  = fBlue[x]  * 255.0f;
			SetPixel(hdc, x, y, RGB(nRed, nGreen, nBlue));
		}
	}

	g_nLinesUpdated = nLines;

	SelectObject(hdc, hbmOld);
	DeleteDC(hdc);

	delete [] fBlue;
	delete [] fGreen;
	delete [] fRed;

	HBITMAP hbmBlah = (HBITMAP)SendMessage(g_hImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g_hbmRaster);
	if (hbmBlah != g_hbmRaster)
		DeleteObject(hbmBlah);

	return 0;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnClose(HWND hwnd)
{
	if (g_tRender.getStatus() == TS_RUNNING || g_tRender.getStatus() == TS_STOPPING)
	{
		MessageBox(hwnd, _T("Thread Still Running"), _T("Thread Still Running"), MB_OK);

		return 1;
	}

	DestroyWindow(hwnd);

	return 0;
}

//////////////////////////////////////////////////////////////////////

LRESULT OnDestroy(HWND hwnd)
{
	FreeScene();

	if (g_hbmRaster)
		DeleteObject(g_hbmRaster);

	PostQuitMessage(0);

	return 0;
}

//////////////////////////////////////////////////////////////////////
