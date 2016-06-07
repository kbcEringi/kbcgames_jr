#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

class CGameCursor3D : public C3DObject
{
public:
	enum State{
		select,
		nonselect
	};
	CGameCursor3D() : C3DObject(){}
	~CGameCursor3D();
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	void Move();
	void SetState(State state)
	{
		this->state = state;

	}
	D3DXVECTOR3 GetPos()
	{
		return m_position;
	}
	void SetPos(D3DXVECTOR3 pos)
	{
		m_position = pos;
	}
private:
	D3DXVECTOR3 m_position;
	BYTE diks[256];
	State state;
};
