
#include "Renderer.h"
#include "Color.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////

Renderer::Renderer()
{
	m_nNextLine = 0;

	m_rsStatus = RS_READY;

	m_cColor.fRed = 0.0f;
	m_cColor.fGreen = 0.0f;
	m_cColor.fBlue = 0.0f;

	m_cCanvas.clear(m_cColor);
}

//////////////////////////////////////////////////////////////////////

int Renderer::setBackgroundColor(Color &c)
{
	m_cColor = c;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getBackgroundColor(Color &c)
{
	c = m_cColor;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::reset()
{
	m_nNextLine = 0;

	m_rsStatus = RS_READY;

	m_cCanvas.clear(m_cColor);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::renderLine()
{
	int nHeight = m_cCanvas.getHeight();
	int nWidth = m_cCanvas.getWidth();

	if (m_nNextLine >= nHeight || m_nNextLine < 0 || getStatus() == RS_COMPLETE)
		return 1;

	if (getStatus() == RS_READY)
		setStatus(RS_INCOMPLETE);

	float pi50 = M_PI / 50.0f;

	Color c;
	float fY = (std::sin(pi50 * (float)m_nNextLine) * 0.5f) + 0.5f;
	for (int x = 0; x < nWidth; x++)
	{
		c.fRed   = ((std::sin(pi50 * (float)x) * 0.5f)+0.5f) * fY;
		c.fGreen = c.fRed;
		c.fBlue  = c.fRed;
		
		m_cCanvas.setPixel(x, m_nNextLine, c);
	}

	m_nNextLine++;

	if (m_nNextLine == nHeight)
		setStatus(RS_COMPLETE);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getLine(int nLine, float *fRed, float *fGreen, float *fBlue, int nSize)
{
	int nWidth = m_cCanvas.getWidth();
	int nHeight = m_cCanvas.getHeight();

	if (nSize != nWidth)
		return 1;

	if (!fRed || !fGreen || !fBlue)
		return 2;

	if (nLine < 0 || nLine >= nHeight)
		return 3;

	Color c;
	for (int x = 0; x < nSize; x++)
	{
		m_cCanvas.getPixel(x, nLine, c);

		fRed[x]   = c.fRed;
		fGreen[x] = c.fGreen;
		fBlue[x]  = c.fBlue;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::setDimensions(int nWidth, int nHeight)
{
	if (nWidth < 1 || nHeight < 1)
		return 1;

	m_cCanvas.setDimensions(nWidth, nHeight);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getDimensions(int &nWidth, int &nHeight)
{
	m_cCanvas.getDimensions(nWidth, nHeight);
	
	return 0;
}

int Renderer::getWidth()
{
	return m_cCanvas.getWidth();
}

int Renderer::getHeight()
{
	return m_cCanvas.getHeight();
}

int Renderer::getLinesComplete()
{
	return m_nNextLine;
}

//////////////////////////////////////////////////////////////////////

RenderStatus Renderer::getStatus()
{
	return m_rsStatus;
}

//////////////////////////////////////////////////////////////////////

int Renderer::setStatus(RenderStatus rsStatus)
{
	m_rsStatus = rsStatus;

	return 0;
}

//////////////////////////////////////////////////////////////////////
