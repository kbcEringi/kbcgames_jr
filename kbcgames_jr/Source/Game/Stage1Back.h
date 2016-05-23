#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

class CStage1Back : public C3DObject
{
public:
	CStage1Back() : C3DObject(){}
	~CStage1Back();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
private:
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
};