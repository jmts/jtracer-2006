
#include "Vector.h"

#ifndef _RAY_H_
#define _RAY_H_

class Ray
{
	public:
	Vector o; // Origin
	Vector d; // Direction

	Ray() { }
	Ray(const Vector& _o, const Vector& _d) : o(_o), d(_d) { }
	Ray(const Ray& _r);
};

#endif
