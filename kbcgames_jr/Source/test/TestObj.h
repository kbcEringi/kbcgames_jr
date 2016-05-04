#pragma once

#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

#include"..\Frame\Input.h"

class CTestObj
{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	D3DXVECTOR3 GetTrans(){ return vecTrans; }
	C3DObject* Get3DObj(){ return &Obj; }
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
	
	D3DXVECTOR3 vecTrans;
	D3DXMATRIX matTrans, m_projMatrix;

	BYTE diks[256];
};