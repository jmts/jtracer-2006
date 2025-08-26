
#include "Primitive.h"
#include "PointLight.h"
#include <vector>

#ifndef _SCENE_H_
#define _SCENE_H_

class Scene
{
	private:
	std::vector<Primitive*> m_vPrimitives;
	std::vector<PointLight*> m_vLights;
	Color m_cAmbient;

	public:
	Scene();
	Scene(const Scene &s) : m_vPrimitives(s.m_vPrimitives), m_cAmbient(s.m_cAmbient) {}

	int addPrimitive(Primitive *p);
	int getNumPrimitives();
	Primitive* getPrimitive(int i);

	int addLight(PointLight *p);
	int getNumLights();
	PointLight* getLight(int i);

	int setAmbientLight(Color &c);
	int getAmbientLight(Color &c);
	const Color getAmbientLight();
};

#endif
