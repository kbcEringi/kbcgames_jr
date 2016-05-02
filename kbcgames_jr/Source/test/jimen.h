#pragma once

#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

class CTestjimen
{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;

	D3DXVECTOR3 vecTrans;
	D3DXMATRIX matTrans, m_projMatrix;
};