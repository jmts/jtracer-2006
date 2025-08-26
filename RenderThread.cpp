
#include "RenderThread.h"

//////////////////////////////////////////////////////////////////////

RenderThread::RenderThread()
{
	m_hThread = NULL;
	m_hwnd = NULL;

	setStatus(TS_READY);
}

//////////////////////////////////////////////////////////////////////

RenderThread::~RenderThread()
{
	if (m_hThread)
		CloseHandle(m_hThread);
}

//////////////////////////////////////////////////////////////////////

bool RenderThread::setStatus(ThreadStatus tsStatus)
{
	m_tsStatus = tsStatus;

	return true;
}

//////////////////////////////////////////////////////////////////////

ThreadStatus RenderThread::getStatus()
{
	return m_tsStatus;
}

//////////////////////////////////////////////////////////////////////

int RenderThread::reset()
{
	if (getStatus() != TS_STOPPED && getStatus() != TS_FINISHED)
		return 1;

	if (m_hThread)
		CloseHandle(m_hThread);

	setStatus(TS_READY);

	m_rRender.reset();

	return 0;
}

//////////////////////////////////////////////////////////////////////

int RenderThread::start()
{
	if (getStatus() != TS_READY)
		return 1;

	m_hThread = CreateThread(NULL, 0, RenderThread::ThreadProc, (LPVOID)this, 0, NULL);
	if (!m_hThread)
		return 2;

	return 0;
}

//////////////////////////////////////////////////////////////////////

DWORD WINAPI RenderThread::ThreadProc(LPVOID lpParameter)
{
	RenderThread *rt = (RenderThread*)lpParameter;

	HWND hNotifyWindow = rt->getNotifyWindow();

	if (hNotifyWindow)
		PostMessage(hNotifyWindow, WM_THREADSTARTED, 0, 0);

	rt->setStatus(TS_RUNNING);

	int ret = rt->run();

	if (hNotifyWindow)
		PostMessage(hNotifyWindow, WM_THREADFINISHED, 0, 0);

	rt->setStatus(TS_FINISHED);

	return (DWORD)ret;
}

//////////////////////////////////////////////////////////////////////

int RenderThread::run()
{
	while(getStatus() != TS_STOPPING && getRenderStatus() != RS_COMPLETE)
	{
		m_rRender.renderLine();

		if (getNotifyWindow())
			PostMessage(getNotifyWindow(), WM_LINERENDERED, 0, 0);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////

int RenderThread::stop()
{
	if (getStatus() != TS_RUNNING)
		return 1;

	setStatus(TS_STOPPING);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int RenderThread::wait()
{
	WaitForSingleObject(m_hThread, INFINITE);

	return 0;
}

//////////////////////////////////////////////////////////////////////

HWND RenderThread::setNotifyWindow(HWND hwnd)
{
	HWND hOld = m_hwnd;

	m_hwnd = hwnd;

	return hOld;
}

//////////////////////////////////////////////////////////////////////

HWND RenderThread::getNotifyWindow()
{
	return m_hwnd;
}

//////////////////////////////////////////////////////////////////////


int RenderThread::getLine(int nLine, float *fRed, float *fGreen, float *fBlue, int nSize)
{
	return m_rRender.getLine(nLine, fRed, fGreen, fBlue, nSize);
}

//////////////////////////////////////////////////////////////////////

int RenderThread::setDimensions(int nWidth, int nHeight)
{
	return m_rRender.setDimensions(nWidth, nHeight);
}

//////////////////////////////////////////////////////////////////////

int RenderThread::getDimensions(int &nWidth, int &nHeight)
{
	return m_rRender.getDimensions(nWidth, nHeight);
}

//////////////////////////////////////////////////////////////////////

int RenderThread::getWidth()
{
	return m_rRender.getWidth();
}

//////////////////////////////////////////////////////////////////////

int RenderThread::getHeight()
{
	return m_rRender.getHeight();
}

//////////////////////////////////////////////////////////////////////

int RenderThread::getLinesComplete()
{
	return m_rRender.getLinesComplete();
}

//////////////////////////////////////////////////////////////////////

RenderStatus RenderThread::getRenderStatus()
{
	return m_rRender.getStatus();
}

//////////////////////////////////////////////////////////////////////

int RenderThread::setCamera(Camera &c)
{
	return m_rRender.setCamera(c);
}

//////////////////////////////////////////////////////////////////////

int RenderThread::getCamera(Camera &c)
{
	return m_rRender.getCamera(c);
}

//////////////////////////////////////////////////////////////////////

int RenderThread::setScene(Scene &s)
{
	return m_rRender.setScene(s);
}

//////////////////////////////////////////////////////////////////////

int RenderThread::getScene(Scene &s)
{
	return m_rRender.getScene(s);
}
