
#include "PointLight.h"

int PointLight::setColor(Color &c)
{
	m_cColor = c;

	return 0;
}

const Color PointLight::getColor()
{
	return m_cColor;
}

int PointLight::setPosition(Vector &p)
{
	m_vPosition = p;

	return 0;
}

const Vector PointLight::getPosition()
{
	return m_vPosition;
}
