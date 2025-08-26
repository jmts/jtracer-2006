
#include "Color.h"
#include "Vector.h"

#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

class PointLight
{
	private:
	Color m_cColor;
	Vector m_vPosition;

	public:
	PointLight() {}
	PointLight(Color c, Vector p) : m_cColor(c), m_vPosition(p) {}
	PointLight(const PointLight &l) : m_cColor(l.m_cColor), m_vPosition(l.m_vPosition) {}

	int setColor(Color &c);
	const Color getColor();

	int setPosition(Vector &p);
	const Vector getPosition();
};

#endif
