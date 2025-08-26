
#include "Canvas.h"
#include "Color.h"
#include "Camera.h"
#include "Scene.h"

#ifndef _RENDERER_H_
#define _RENDERER_H_

typedef enum { RS_READY, RS_INCOMPLETE, RS_COMPLETE } RenderStatus;

class Renderer
{
	private:
	int m_nNextLine;

	RenderStatus m_rsStatus;

	Color m_cColor;

	Canvas m_cCanvas;

	Camera m_cCamera;

	Scene m_sScene;

	public:
	Renderer();

	int reset();

	int renderLine();

	int getLine(int nLine, float *fRed, float *fGreen, float *fBlue, int nSize);

	int setDimensions(int nWidth, int nHeight);
	int getDimensions(int &nWidth, int &nHeight);
	int getWidth();
	int getHeight();

	int getLinesComplete();

	RenderStatus getStatus();
	int setStatus(RenderStatus rsStatus);

	int setCamera(Camera &c);
	int getCamera(Camera &c);

	int setScene(Scene &s);
	int getScene(Scene &s);

	int setBackgroundColor(Color &c);
	int getBackgroundColor(Color &c);
};

#endif
