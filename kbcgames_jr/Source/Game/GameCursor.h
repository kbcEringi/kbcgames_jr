#pragma once

#include"..\Frame\C2DObject.h"
#include"..\Frame\Input.h"


class CGameCursor
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Move();
	D3DXVECTOR3 GetPosition()
	{
		return vec3Position;
	}

private:
	C2DObject m_2Dobj;

	D3DXVECTOR3 vec3Position;
	D3DXVECTOR3 vec3Scale;

	BYTE diks[256];

};