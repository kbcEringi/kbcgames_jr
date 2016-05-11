#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include"..\BulletPhysics\BulletPhysics.h"

class CGround
{
public:
	CGround();
	~CGround();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
};
