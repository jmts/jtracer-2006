
#include "Renderer.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////

Renderer::Renderer()
{
	m_nNextLine = 0;

	m_rsStatus = RS_READY;

	m_cColor.fRed = 0.0f;
	m_cColor.fGreen = 0.0f;
	m_cColor.fBlue = 0.0f;

	m_cCanvas.clear(m_cColor);
}

//////////////////////////////////////////////////////////////////////

int Renderer::setBackgroundColor(Color &c)
{
	m_cColor = c;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getBackgroundColor(Color &c)
{
	c = m_cColor;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::reset()
{
	m_nNextLine = 0;

	m_rsStatus = RS_READY;

	m_cCanvas.clear(m_cColor);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::findIntersection(Ray &r, float &t, Primitive **p)
{
	bool bIntersection = false;
	Primitive *pClosest;
	float fTClosest;
	int nPrimitives = m_sScene.getNumPrimitives();
	for (int i = 0; i < nPrimitives; i++)
	{
		Primitive *pCurrent = m_sScene.getPrimitive(i);

		float fTCurrent;
		if (pCurrent->intersect(r, fTCurrent))
		{
			if (bIntersection == false)
			{
				pClosest = pCurrent;
				fTClosest = fTCurrent;
				bIntersection = true;
			}
			else if (fTCurrent < fTClosest)
			{
				pClosest = pCurrent;
				fTClosest = fTCurrent;
			}
		}
	}

	if (bIntersection)
	{
		t = fTClosest;
		*p = pClosest;
		return 1;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::findShadowCaster(Ray &r, Primitive *p)
{
	bool bShadow = false;
	int nPrimitives = m_sScene.getNumPrimitives();

	float t;
	for (int i = 0; i < nPrimitives && !bShadow; i++)
	{
		Primitive *pCurrent = m_sScene.getPrimitive(i);
		if (pCurrent != p && pCurrent->intersect(r, t) && t > 0.0 && t < 1.0)
			bShadow = true;
	}

	if (bShadow)
		return 1;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::raytrace(Ray r, Color &c, int nRecursions)
{
	Primitive *pClosest;
	float fTClosest;
	if (findIntersection(r, fTClosest, &pClosest))
	{
		Material m = pClosest->getMaterial();

		Color cAmbient;
		Color cDiffuse;
		Color cSpecular;
		Color cReflect;

		cAmbient = m.getPigment() * m_sScene.getAmbientLight() * m.getAmbient();

		Vector vIntersect = r.o + (r.d * fTClosest);
		Vector vNormal = pClosest->getNormalAt(vIntersect);
		Vector vView = r.d;

		int nLights = m_sScene.getNumLights();
		for (int i = 0; i < nLights; i++)
		{
			PointLight *lLight = m_sScene.getLight(i);
			Ray rShadow(vIntersect, (lLight->getPosition() - vIntersect));

			if (!findShadowCaster(rShadow, pClosest))
			{
				Vector vLight = (lLight->getPosition() - vIntersect).unit();
				Vector vReflect = (vLight).reflect(vNormal);

				float fDot;
				fDot = vLight.dot(vNormal);
				if (fDot > 0)
					cDiffuse += m.getPigment() * lLight->getColor() * fDot * m.getDiffuse();

				fDot = vReflect.dot(vView);
				if (fDot > 0)
					cSpecular += lLight->getColor() * m.getSpecular() * std::pow(fDot, 8);
			}
		}

		if (nRecursions > 0)
		{
			Ray rReflect(vIntersect, vView.reflect(vNormal));
			if (raytrace(rReflect, cReflect, nRecursions-1))
			{
				cReflect *= 0.8;
			}
		}

		c = cAmbient + cDiffuse + cSpecular + cReflect;
	}
	else
	{
		return 0;
	}

	return 1;
}

//////////////////////////////////////////////////////////////////////

int Renderer::renderLine()
{
	if (m_sScene.getNumPrimitives() == 0 || m_sScene.getNumLights() == 0)
		return 1;

	int nHeight = m_cCanvas.getHeight();
	int nWidth = m_cCanvas.getWidth();

	if (m_nNextLine >= nHeight || m_nNextLine < 0 || getStatus() == RS_COMPLETE)
		return 1;

	if (getStatus() == RS_READY)
		setStatus(RS_INCOMPLETE);

	// Render Code
	Color c;
	float fy = (float)m_nNextLine / (float)nHeight;
	for (int x = 0; x < nWidth; x++)
	{
		float fx = (float)x / (float)nWidth;

		Ray r = m_cCamera.getRay(fx, fy);

		if (raytrace(r, c, 5))
			m_cCanvas.setPixel(x, m_nNextLine, c);
		else
			m_cCanvas.setPixel(x, m_nNextLine, m_cColor);
	}
	// End Render Code

	m_nNextLine++;

	if (m_nNextLine == nHeight)
		setStatus(RS_COMPLETE);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getLine(int nLine, float *fRed, float *fGreen, float *fBlue, int nSize)
{
	int nWidth = m_cCanvas.getWidth();
	int nHeight = m_cCanvas.getHeight();

	if (nSize != nWidth)
		return 1;

	if (!fRed || !fGreen || !fBlue)
		return 2;

	if (nLine < 0 || nLine >= nHeight)
		return 3;

	Color c;
	for (int x = 0; x < nSize; x++)
	{
		m_cCanvas.getPixel(x, nLine, c);

		fRed[x]   = c.fRed;
		fGreen[x] = c.fGreen;
		fBlue[x]  = c.fBlue;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::setDimensions(int nWidth, int nHeight)
{
	if (nWidth < 1 || nHeight < 1)
		return 1;

	m_cCanvas.setDimensions(nWidth, nHeight);

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getDimensions(int &nWidth, int &nHeight)
{
	m_cCanvas.getDimensions(nWidth, nHeight);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getWidth()
{
	return m_cCanvas.getWidth();
}

//////////////////////////////////////////////////////////////////////

int Renderer::getHeight()
{
	return m_cCanvas.getHeight();
}

//////////////////////////////////////////////////////////////////////

int Renderer::getLinesComplete()
{
	return m_nNextLine;
}

//////////////////////////////////////////////////////////////////////

RenderStatus Renderer::getStatus()
{
	return m_rsStatus;
}

//////////////////////////////////////////////////////////////////////

int Renderer::setStatus(RenderStatus rsStatus)
{
	m_rsStatus = rsStatus;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::setCamera(Camera &c)
{
	m_cCamera = c;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getCamera(Camera &c)
{
	c = m_cCamera;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::setScene(Scene &s)
{
	m_sScene = s;

	return 0;
}

//////////////////////////////////////////////////////////////////////

int Renderer::getScene(Scene &s)
{
	s = m_sScene;

	return 0;
}

//////////////////////////////////////////////////////////////////////
