#include "Vector.h"
#include <cmath>

Vector::Vector(const Vector &u)
{
	x = u.x;
	y = u.y;
	z = u.z;
}

Vector& Vector::operator=(const Vector& blah)
{
	if (this == &blah)
		return *this;
	
	x = blah.x;
	y = blah.y;
	z = blah.z;
	
	return *this;
}

Vector& Vector::operator*=(float factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	
	return *this;
}

Vector& Vector::operator/=(float factor)
{
	x /= factor;
	y /= factor;
	z /= factor;
	
	return *this;
}

Vector& Vector::operator+=(const Vector &u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	
	return *this;
}

Vector& Vector::operator-=(const Vector &u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	
	return *this;
}

const Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
}

const Vector Vector::operator+(const Vector &other) const
{
	return Vector(*this) += other;
}

const Vector Vector::operator-(const Vector &other) const
{
	return Vector(*this) -= other;
}

const Vector Vector::operator*(float factor) const
{
	return Vector(*this) *= factor;
}

const Vector Vector::operator/(float factor) const
{
	return Vector(*this) /= factor;
}

float Vector::dot(const Vector &u) const
{
	return x*u.x + y*u.y + z*u.z;
}

const Vector Vector::cross(const Vector &u) const
{
	return Vector(y*u.z - z*u.y, z*u.x - x*u.z, x*u.y - y*u.x);
}

float Vector::length() const
{
	return std::sqrt(lengthSquared());
}

float Vector::lengthSquared() const
{
	return x*x + y*y + z*z;
}

const Vector Vector::unit() const
{
	float len = lengthSquared();
	
	if (len == 1.0f)
		return Vector(*this);
	
	return Vector(*this)/std::sqrt(len);
}

Vector Vector::reflect(const Vector& n) const
{
	return Vector( *this - ( n * 2.0f * this->dot(n) ) );
}
