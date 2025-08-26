
#include "Primitive.h"

int Primitive::setMaterial(Material &m)
{
	m_mMaterial = m;

	return 0;
}

int Primitive::getMaterial(Material &m)
{
	m = m_mMaterial;

	return 0;
}
