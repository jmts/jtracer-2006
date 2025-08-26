
#include "Globals.h"
#include <windows.h>
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"

#ifndef _RENDERTHREAD_H_
#define _RENDERTHREAD_H_

#define WM_THREADBASE     ( WM_APP        + 0x0200 )
#define WM_THREADSTARTED  ( WM_THREADBASE          )
#define WM_THREADFINISHED ( WM_THREADBASE + 0x0001 )
#define WM_LINERENDERED   ( WM_THREADBASE + 0x0002 )

typedef enum { TS_READY, TS_RUNNING, TS_STOPPING, TS_STOPPED, TS_FINISHED } ThreadStatus;

class RenderThread
{
	private:
	HWND m_hwnd;
	HANDLE m_hThread;
	ThreadStatus m_tsStatus;

	Renderer m_rRender;

	bool setStatus(ThreadStatus tsStatus);

	public:
	RenderThread();
	~RenderThread();

	ThreadStatus getStatus();

	int reset();
	int start();
	int run();
	int stop();

	int wait();

	HWND setNotifyWindow(HWND hwnd);
	HWND getNotifyWindow();

	static DWORD WINAPI ThreadProc(LPVOID lpParameter);

	int getLine(int nLine, float *fRed, float *fGreen, float *fBlue, int nSize);

	int setDimensions(int nWidth, int nHeight);
	int getDimensions(int &nWidth, int &nHeight);
	int getWidth();
	int getHeight();
	int getLinesComplete();

	RenderStatus getRenderStatus();

	int setCamera(Camera &c);
	int getCamera(Camera &c);

	int setScene(Scene &s);
	int getScene(Scene &s);
};

#endif
