#pragma once

#include"..\DXCommon.h"
#include"..\C3DObject.h"

class CTestObj
{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
};