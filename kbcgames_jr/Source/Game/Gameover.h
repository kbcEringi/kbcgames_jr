#pragma once

#include"..\Frame\C2DObject.h"
#include"..\Frame\Input.h"


class CGameover
{
public:
	void Initialize();
	void Update();
	void Draw();
private:
	C2DObject m_2Dobj;
	D3DXVECTOR3 vec3Position;
	D3DXVECTOR3 vec3Scale;

	bool over;//����ł��邩�H

	BYTE diks[256];

};