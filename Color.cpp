#include "Color.h"

Color& Color::operator*=(const Color &c)
{
	fRed   *= c.fRed;
	fGreen *= c.fGreen;
	fBlue  *= c.fBlue;
	
	return *this;
}

const Color Color::operator*(const Color &c) const
{
	return Color(*this) *= c;
}

Color& Color::operator*=(float x)
{
	fRed   *= x;
	fGreen *= x;
	fBlue  *= x;
	
	return *this;
}

const Color Color::operator*(float x) const
{
	return Color(*this) *= x;
}

Color& Color::operator+=(const Color &c)
{
	fRed   += c.fRed;
	fGreen += c.fGreen;
	fBlue  += c.fBlue;

	fRed   = fmid(0.0f, fRed, 1.0f);
	fGreen = fmid(0.0f, fGreen, 1.0f);
	fBlue  = fmid(0.0f, fBlue, 1.0f);
	
	return *this;
}

const Color Color::operator+(const Color &c) const
{
	return Color(*this) += c;
}
