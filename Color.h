
#ifndef _COLOR_H_
#define _COLOR_H_

typedef struct tagColor
{
	float fRed;
	float fGreen;
	float fBlue;
} Color;

inline float fmid (float min, float mid, float max)
{
	if (mid >= min && mid <= max)
		return mid;
	else if (mid < min)
		return min;

	return max;
}

#endif
