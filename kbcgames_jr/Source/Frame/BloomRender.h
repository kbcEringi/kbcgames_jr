#pragma once

#include"RenderTarget.h"
#include"C2DObject.h"
using namespace Frame;

class BloomRender
{
public:
	BloomRender();
	~BloomRender();
	void Render();
	void Create(bool);
private:
	void UpdateWeight(float);
private:
	static const int NUM_WEIGHTS = 8;
	ID3DXEffect* m_pEffect;
	CRenderTarget m_luminanceRenderTarget;
	CRenderTarget m_downSamplingRenderTarget[4];
	bool m_isEnable;
	float m_weights[NUM_WEIGHTS];
	C2DObject fullscreen;
};