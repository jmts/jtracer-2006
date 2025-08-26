
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include <iostream>

int main(int argc, char **argv)
{
	Sphere sSphere(Vector(0.0, 0.0, 0.0), 0.5);
	
	Ray rRay(Vector(0.0, 0.2, -5.0), Vector(0.0, 0.0, 1.0));

	float t;
	sSphere.intersect(rRay, t);
	Vector vIntersect = rRay.o + (rRay.d*t);
	std::cout << vIntersect.x << ", " << vIntersect.y << ", " << vIntersect.z << std::endl;

	Vector vNormal = sSphere.getNormalAt(vIntersect);
	std::cout << vNormal.x << ", " << vNormal.y << ", " << vNormal.z << std::endl;

	Vector vReflect = rRay.d.reflect(vNormal);
	std::cout << vReflect.x << ", " << vReflect.y << ", " << vReflect.z << std::endl;

	Ray rReflect(vIntersect, vReflect);
	if (sSphere.intersect(rReflect, t))
	{
		std::cout << "Shite!" << t << std::endl;
	}

	return 0;
}
