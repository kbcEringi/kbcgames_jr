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
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	void SetPos(D3DXVECTOR3* pos)
	{
		m_position = *pos;
	}
	void SetDraw(bool flag)
	{
		DrawFlag = flag;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
	bool GetDraw()
	{
		return DrawFlag;
	}
private:
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;
	bool DrawFlag;
};