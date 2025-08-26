
#include "Ray.h"
#include "Material.h"

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

class Primitive
{
	private:
	Material m_mMaterial;

	public:
	Primitive() {}
	Primitive(const Primitive &p) : m_mMaterial(p.m_mMaterial) {}
	int setMaterial(Material &m);
	int getMaterial(Material &m);
	const Material getMaterial();

	virtual int intersect(const Ray& ray, float &t) = 0;
	virtual const Vector getNormalAt(const Vector &v) = 0;
};

#endif
