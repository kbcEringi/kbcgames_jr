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
private:
	C2DObject m_2Dobj;

	D3DXVECTOR3 vec3Position;
	D3DXVECTOR3 vec3Scale;
	BYTE diks[256];
	State state;

	bool flg;
};