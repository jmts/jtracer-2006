
#include "Camera.h"
#include <cmath>

Camera::Camera()
{
	m_vPosition = Vector(0.0f, 0.0f, -5.0f);
	m_vLook = Vector(0.0f, 0.0f, 1.0f);
	m_fAspect = 4.0f/3.0f;
	m_fAngleOfView = M_PI/4.0f;

	m_vSky = Vector(0.0f, 1.0f, 0.0f); // Y-Axis

	m_vRight = m_vSky.cross(m_vLook).unit() * m_fAspect; // Right Vector
	m_vUp = m_vLook.cross(m_vRight).unit(); // Up Vector

	m_vDirection = m_vLook * (0.5f * 1.0f/std::tan(m_fAngleOfView / 2.0f));
}

Camera::Camera(Vector vPosition, Vector vLook, float fAspect, float fAngle)
{
	m_vPosition = vPosition;
	m_vLook = vLook.unit();
	m_fAspect = fAspect;
	m_fAngleOfView = fAngle;

	m_vSky = Vector(0.0f, 1.0f, 0.0f); // Y-Axis

	m_vRight = m_vSky.cross(m_vLook).unit() * m_fAspect; // Right Vector
	m_vUp = m_vLook.cross(m_vRight).unit(); // Up Vector

	m_vDirection = m_vLook * (0.5f * 1.0f/std::tan(m_fAngleOfView / 2.0f));
}

int Camera::getRay(float x, float y, Ray &ray)
{
	if (x < 0.0f || x > 1.0f || y < 0.0f || y > 1.0f)
		return 0;

	x -= 0.5f;
	y -= 0.5f;

	Vector vDirection = m_vDirection + (m_vRight * x) + (m_vUp * -y);
	vDirection = vDirection.unit();

	ray = Ray(m_vPosition, vDirection);

	return 1;
}