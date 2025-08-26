
#include "Sphere.h"
#include <cmath>

int Sphere::intersect(const Ray &ray, float &t)
{
	Vector dst = ray.o - o;

	float fLen = ray.d.length();

	Vector dir = ray.d / fLen;

	float B = dst.dot(dir);

	float C = dst.dot(dst) - (r * r);

	float D = B*B - C;

	if (D > 0)
	{
		t = (-B - std::sqrt(D)) / fLen;
		return 1;
	}

	return 0;
}

const Vector Sphere::getNormalAt(const Vector &v)
{
	return (v - o).unit();
}
