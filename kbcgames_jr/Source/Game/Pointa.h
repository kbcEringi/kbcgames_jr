#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

class CPointa : public C3DObject
{
public:
	CPointa() : C3DObject(){}
	~CPointa();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void D2DDraw(D3DXMATRIX, D3DXMATRIX)override{}
	void D3DDraw(D3DXMATRIX, D3DXMATRIX)override;
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	void SetPos(D3DXVECTOR3* pos)
	{
		m_position = *pos;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
private:
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;
};