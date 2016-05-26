#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\BulletPhysics\BulletPhysics.h"

class CGround : public C3DObject
{
public:
	CGround() : C3DObject(){}
	~CGround();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void D2DDraw(D3DXMATRIX, D3DXMATRIX)override{}
	void D3DDraw(D3DXMATRIX, D3DXMATRIX)override;
private:
	D3DXVECTOR3 m_position;
};
