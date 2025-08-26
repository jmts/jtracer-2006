
#include "Material.h"

Material::Material()
{
	m_fAmbient = 0.0f;

	m_cPigment.fRed   = 0.0f;
	m_cPigment.fGreen = 0.0f;
	m_cPigment.fBlue  = 0.0f;
}

int Material::setPigment(Color &c)
{
	m_cPigment = c;

	return 0;
}

int Material::getPigment(Color &c)
{
	c = m_cPigment;

	return 0;
}

int Material::setAmbient(float fAmbient)
{
	if (fAmbient < 0.0f || fAmbient > 1.0f)
		return 1;

	m_fAmbient = fAmbient;

	return 0;
}

float Material::getAmbient()
{
	return m_fAmbient;
}
