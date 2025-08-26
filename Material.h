
#include "Color.h"

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class Material
{
	private:
	Color m_cPigment;
	float m_fAmbient;
	float m_fDiffuse;
	float m_fSpecular;

	public:
	Material() : m_fAmbient(0.0), m_fDiffuse(0.0), m_fSpecular(0.0) {}
	Material(const Color &cPigment, float fAmbient, float fDiffuse, float fSpecular) : m_cPigment(cPigment), m_fAmbient(fAmbient), m_fDiffuse(fDiffuse), m_fSpecular(fSpecular){}
	Material(const Material &m) : m_cPigment(m.m_cPigment), m_fAmbient(m.m_fAmbient), m_fDiffuse(m.m_fDiffuse), m_fSpecular(m.m_fSpecular){}

	int setPigment(Color &c);
	int getPigment(Color &c);
	const Color getPigment();

	int setAmbient(float fAmbient);
	float getAmbient();

	int setDiffuse(float fDiffuse);
	float getDiffuse();

	int setSpecular(float fSpecular);
	float getSpecular();
};

#endif
