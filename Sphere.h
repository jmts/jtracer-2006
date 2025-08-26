
#include "Primitive.h"
#include "Vector.h"
#include "Ray.h"

#ifndef _SPHERE_H_
#define _SPHERE_H_

class Sphere : public Primitive
{
	public:
	Vector o; // Center
	float r;  // Radius

	Sphere() : r(1.0f) {}
	Sphere(Vector _o, float _r) : o(_o), r(_r) {}
	Sphere(const Sphere &s) : o(s.o), r(s.r) {}

	virtual int intersect(const Ray &ray, float &t);

	virtual const Vector getNormalAt(const Vector &v);
};

#endif
