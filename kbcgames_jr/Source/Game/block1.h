#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

class CBlock1
{
public:
	CBlock1();
	~CBlock1();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
};
