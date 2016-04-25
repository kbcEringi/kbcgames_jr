#pragma once

#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

#include"..\Frame\Input.h"

class CTestObj
{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	D3DXVECTOR3 GetTrans(){ return vecTrans; }
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
	
	D3DXVECTOR3 vecTrans;
	D3DXMATRIX matTrans;

	BYTE diks[256];
};