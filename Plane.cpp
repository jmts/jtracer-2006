
#include "Plane.h"

Plane::Plane(Vector _n, float d)
{
	Vector n = _n.unit();
	Vector p = n*d;

	m_fD = n.x*p.x + n.y*p.y + n.z*p.z;
	m_fD = -m_fD;

	m_vNormal = n;
}

int Plane::intersect(const Ray &ray, float &t)
{
	Vector n = m_vNormal;
	Vector v = ray.o;
	Vector u = ray.d;

	float fNum = -(n.x*v.x + n.y*v.y + n.z*v.z + m_fD);
	float fDenom = n.x*u.x + n.y*u.y + n.z*u.z;

	t = fNum/fDenom;

	if (t >= 0.0)
		return 1;

	return 0;
}

const Vector Plane::getNormalAt(const Vector &v)
{
	return m_vNormal;
}
