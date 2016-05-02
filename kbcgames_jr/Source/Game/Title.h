#pragma once

#include"..\Frame\C2DObject.h"
#include"..\Frame\Input.h"


class CTitle
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	C2DObject m_2Dobj;

	D3DXVECTOR3 vec3Position;
	D3DXVECTOR3 vec3Scale;

	BYTE diks[256];

};