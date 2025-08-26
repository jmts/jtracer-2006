
#include "Canvas.h"

//////////////////////////////////////////////////////////////////////

Canvas::Canvas()
{
	m_nWidth = 1;
	m_nHeight = 1;

	allocate();
}

//////////////////////////////////////////////////////////////////////

Canvas::Canvas(int nWidth, int nHeight)
{
	m_nWidth = (nWidth > 0) ? nWidth : 1;
	m_nHeight = (nHeight > 0) ? nHeight : 1;

	allocate();
}

//////////////////////////////////////////////////////////////////////

int Canvas::allocate()
{
	if (m_nWidth <= 0 || m_nHeight <= 0)
		return 1;
	
	int size = m_nWidth * m_nHeight;

	m_fRed = new float[size];
	m_fGreen = new float[size];
	m_fBlue = new float[size];

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Canvas::deallocate()
{
	if (m_fRed)
		delete [] m_fRed;

	if (m_fGreen)
		delete [] m_fGreen;

	if (m_fBlue)
		delete [] m_fBlue;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Canvas::getWidth()
{
	return m_nWidth;
}

//////////////////////////////////////////////////////////////////////

int Canvas::getHeight()
{
	return m_nHeight;
}

//////////////////////////////////////////////////////////////////////

int Canvas::getDimensions(int &nWidth, int &nHeight)
{
	nWidth = m_nWidth;
	nHeight = m_nHeight;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Canvas::setDimensions(int nWidth, int nHeight)
{
	if (nWidth <= 0 || nHeight <= 0)
		return 1;

	deallocate();

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	allocate();

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Canvas::setPixel(int x, int y, Color &c)
{
	if (x < 0 || x >= m_nWidth || y < 0 || y >= m_nHeight)
		return 1;

	int offset = (y * m_nWidth) + x;

	m_fRed[offset]   = fmid(0.0f, c.fRed,   1.0f);
	m_fGreen[offset] = fmid(0.0f, c.fGreen, 1.0f);
	m_fBlue[offset]  = fmid(0.0f, c.fBlue,  1.0f);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Canvas::getPixel(int x, int y, Color &c)
{
	if (x < 0 || x >= m_nWidth || y < 0 || y >= m_nHeight)
		return 1;

	int offset = (y * m_nWidth) + x;

	c.fRed   = fmid(0.0f, m_fRed[offset],   1.0f);
	c.fGreen = fmid(0.0f, m_fGreen[offset], 1.0f);
	c.fBlue  = fmid(0.0f, m_fBlue[offset],  1.0f);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Canvas::clear(Color &c)
{
	int size     = m_nWidth * m_nHeight;
	float fRed   = fmid(0.0f, c.fRed,   1.0f);
	float fGreen = fmid(0.0f, c.fGreen, 1.0f);
	float fBlue  = fmid(0.0f, c.fBlue,  1.0f);
	
	for (int i = 0; i < size; i++)
	{
		m_fRed[i]   = fRed;
		m_fGreen[i] = fGreen;
		m_fBlue[i]  = fBlue;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////
