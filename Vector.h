
#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector
{
	public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float val[3];
	};
	
	Vector() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector(const Vector &u);
	
	Vector& operator=(const Vector& blah);
	
	Vector& operator*=(float factor);
	Vector& operator/=(float factor);
	Vector& operator+=(const Vector &u);
	Vector& operator-=(const Vector &u);
	
	const Vector operator-() const;
	
	const Vector operator*(float factor) const;
	const Vector operator/(float factor) const;
	const Vector operator+(const Vector &other) const;
	const Vector operator-(const Vector &other) const;
	
	//float& operator[](size_t index) { return val[index]; }
	//const float& operator[](size_t index) const { return val[index]; }
	
	const Vector cross(const Vector &u) const;
	float dot(const Vector &u) const;
	float length() const;
	float lengthSquared() const;
	const Vector unit() const;
	Vector reflect(const Vector& n) const;
};

#endif
