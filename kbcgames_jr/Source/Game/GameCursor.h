#pragma once

#include"..\Frame\C2DObject.h"
#include"..\Frame\Input.h"
#include"..\Frame\CGamepad.h"


class CGameCursor
{
public:
	enum State
	{
		view,
		nonview
	};
	void Initialize();
	void Update();
	void Draw();
	void Move();
	void Pos3D();
	D3DXVECTOR3 GetPosition()
	{
		return vec3Position;
	}
	void SetPos(D3DXVECTOR3 pos)
	{
		vec3Position = pos;
	}
	void SetState(State state)
	{
		this->state = state;

	}
	D3DXVECTOR3 GetPos3D()
	{
		return m_pos3D;
	}
private:
	C2DObject m_2Dobj;

	D3DXVECTOR3 vec3Position;
	D3DXVECTOR3 vec3Scale;
	D3DXVECTOR3 m_pos3D;
	BYTE diks[256];
	State state;
};