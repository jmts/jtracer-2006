
#include "Vector.h"
#include "Ray.h"

#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera
{
	//private:
	public:
	Vector m_vPosition;
	Vector m_vLook;

	Vector m_vSky;

	Vector m_vRight;
	Vector m_vUp;

	Vector m_vDirection;

	float  m_fAspect;
	float  m_fAngleOfView;

	//public:
	Camera();
	Camera(Vector vPosition, Vector vLook, float fAspect, float fAngle);
	int getRay(float x, float y, Ray &ray);
	const Ray getRay(float x, float y);
};

#endif
