#pragma once

#include"..\C2DObject.h"

class Cgazou
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	C2DObject m_2Dobj;
	D3DXMATRIX  matWorld, matTrans, matScale, matRot;
	D3DXVECTOR3 vec3Trans;
	D3DXVECTOR3 vec3Scale;
	D3DXVECTOR3 vec3Rot;
};