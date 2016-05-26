#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "Player.h"

class CStage1Back : public C3DObject
{
public:
	CStage1Back() : C3DObject(){}
	~CStage1Back();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void D2DDraw(D3DXMATRIX, D3DXMATRIX)override{}
	void D3DDraw(D3DXMATRIX, D3DXMATRIX)override;
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
	void SetPointa(CPlayer* player)
	{
		m_pPlayer = player;
	}
private:
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	CPlayer* m_pPlayer;
};