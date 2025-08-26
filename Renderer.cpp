
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

int Renderer::renderLine()
{
	int nPrimitives = m_sScene.getNumPrimitives();
	if (nPrimitives == 0)
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

		bool bIntersection = false;
		Primitive *pClosest;
		float fTClosest;
		for (int i = 0; i < nPrimitives; i++)
		{
			Primitive *p = m_sScene.getPrimitive(i);
			float t;

			if (p->intersect(r, t))
			{
				if (bIntersection == false)
				{
					pClosest = p;
					fTClosest = t;
					bIntersection = true;
				}
				else if (t < fTClosest)
				{
					pClosest = p;
					fTClosest = t;
				}
			}
		}

		// Draw Dot On Canvas
		if (bIntersection)
		{
			Material m = pClosest->getMaterial();
			Color cAmbient   = m.getPigment() * m_sScene.getAmbientLight() * m.getAmbient();

			Color cDiffuse;
			Vector vIntersect = r.o + (r.d*fTClosest);
			for (int iLight = 0; iLight < m_sScene.getNumLights(); iLight++)
			{
				PointLight *lLight = m_sScene.getLight(iLight);
				Vector vLight = (lLight->getPosition() - vIntersect).unit();
				Vector vNormal = pClosest->getNormalAt(vIntersect);
				
				float fDot = vLight.dot(vNormal);
				{
					if (fDot > 0)
						cDiffuse += m.getPigment() * lLight->getColor() * fDot * m.getDiffuse();
				}
			}

			Color cPixel = cAmbient + cDiffuse;

			m_cCanvas.setPixel(x, m_nNextLine, cPixel);
		}
		else
		{
			m_cCanvas.setPixel(x, m_nNextLine, m_cColor);
		}
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
