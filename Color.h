
#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
	public:
	Color() : fRed(0.0f), fGreen(0.0f), fBlue(0.0f) {}
	Color(float r, float g, float b) : fRed(r), fGreen(g), fBlue(b) {}
	Color(const Color& c) : fRed(c.fRed), fGreen(c.fGreen), fBlue(c.fBlue) {}

	Color& operator*=(const Color &c);
	const Color operator*(const Color &c) const;

	Color& operator*=(float x);
	const Color operator*(float x) const;

	Color& operator+=(const Color &c);
	const Color operator+(const Color &c) const;

	float fRed;
	float fGreen;
	float fBlue;

	
};

inline float fmid (float min, float mid, float max)
{
	if (mid >= min && mid <= max)
		return mid;
	else if (mid < min)
		return min;

	return max;
}

#endif
