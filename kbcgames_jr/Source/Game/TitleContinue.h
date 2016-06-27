#pragma once

#include"..\Frame\C2DObject.h"
#include"..\Frame\Input.h"

const float MAXC = 230.0f;
const float MINC = 180.0f;

class CTitleContinue
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Scale();
private:
	C2DObject m_2Dobj;

	D3DXVECTOR3 vec3Position;
	D3DXVECTOR3 vec3Scale;

	BYTE diks[256];

	float scale;
};