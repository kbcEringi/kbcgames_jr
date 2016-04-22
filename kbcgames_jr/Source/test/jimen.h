#pragma once

#include"..\DXCommon.h"
#include"..\C3DObject.h"

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
	D3DXMATRIX matTrans;
};