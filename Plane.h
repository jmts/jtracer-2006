
#include "Primitive.h"
#include "Vector.h"

#ifndef _PLANE_H_
#define _PLANE_H_

class Plane : public Primitive
{
	private:
	Vector m_vNormal;
	float  m_fD;

	public:
	Plane() : m_vNormal(Vector(0, 1, 0)), m_fD(0.0f) {}
	Plane(Vector _n, float d);
	Plane(const Plane &p) : m_vNormal(p.m_vNormal), m_fD(p.m_fD) {}

	virtual int intersect(const Ray &ray, float &t);
	virtual const Vector getNormalAt(const Vector &v);
};

#endif
