#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\BulletPhysics\BulletPhysics.h"

class CGround5 : public C3DObject
{
public:
	CGround5() : C3DObject(){}
	~CGround5();
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
private:
	D3DXVECTOR3 m_position;
};
