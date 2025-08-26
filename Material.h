
#include "Color.h"

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class Material
{
	private:
	Color m_cPigment;
	float m_fAmbient;
	float m_fDiffuse;

	public:
	Material() : m_fAmbient(0.0), m_fDiffuse(0.0) {}
	Material(const Color &cPigment, float fAmbient, float fDiffuse) : m_cPigment(cPigment), m_fAmbient(fAmbient), m_fDiffuse(fDiffuse){}
	Material(const Material &m) : m_cPigment(m.m_cPigment), m_fAmbient(m.m_fAmbient), m_fDiffuse(m.m_fDiffuse){}

	int setPigment(Color &c);
	int getPigment(Color &c);
	const Color getPigment();

	int setAmbient(float fAmbient);
	float getAmbient();

	int setDiffuse(float fDiffuse);
	float getDiffuse();
};

#endif
