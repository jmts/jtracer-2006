
#include "Sphere.h"
#include <cmath>

int Sphere::intersect(const Ray &ray, float &t)
{
	Vector dst = ray.o - o;

	float B = dst.dot(ray.d);

	float C = dst.dot(dst) - (r * r);

	float D = B*B - C;

	if (D > 0)
	{
		t = -B - std::sqrt(D);
		return 1;
	}

	return 0;
}
