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
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
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
	D3DXVECTOR3 m_targetPosition;
	LPD3DXMESH m_mesh;
	CPlayer* m_pPlayer;
	D3DXMATRIX proj;
	D3DXMATRIX view;
};