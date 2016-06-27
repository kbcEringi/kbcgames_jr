#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\BulletPhysics\BulletPhysics.h"

class CGround8 : public C3DObject
{
public:
	CGround8() : C3DObject(){}
	~CGround8();
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
private:
	D3DXVECTOR3 m_position;
};
