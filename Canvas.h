
#include "Color.h"

#ifndef _CANVAS_H_
#define _CANVAS_H_

class Canvas
{
	private:
	int m_nWidth;
	int m_nHeight;

	float *m_fRed;
	float *m_fGreen;
	float *m_fBlue;

	int allocate();
	int deallocate();

	public:
	Canvas();
	Canvas(int nWidth, int nHeight);

	int getWidth();
	int getHeight();

	int getDimensions(int &nWidth, int &nHeight);
	int setDimensions(int nWidth, int nHeight);

	int setPixel(int x, int y, Color &c);
	int getPixel(int x, int y, Color &c);

	int clear(Color &c);
};

#endif
