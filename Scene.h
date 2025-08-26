
#include "Primitive.h"
#include <vector>

#ifndef _SCENE_H_
#define _SCENE_H_

class Scene
{
	private:
	std::vector<Primitive*> m_vPrimitives;
	Color m_cAmbient;

	public:
	Scene();
	Scene(const Scene &s) : m_vPrimitives(s.m_vPrimitives), m_cAmbient(s.m_cAmbient) {}

	int addPrimitive(Primitive *p);
	int getNumPrimitives();
	Primitive* getPrimitive(int i);

	int setAmbientLight(Color &c);
	int getAmbientLight(Color &c);
};

#endif
