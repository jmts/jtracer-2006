
#include "Color.h"

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class Material
{
	private:
	Color m_cPigment;
	float m_fAmbient;

	public:
	Material();
	Material(const Material &m) : m_cPigment(m.m_cPigment), m_fAmbient(m.m_fAmbient){}

	int setPigment(Color &c);
	int getPigment(Color &c);

	int setAmbient(float fAmbient);
	float getAmbient();
};

#endif
