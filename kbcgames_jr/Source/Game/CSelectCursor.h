#pragma once

#include"..\Frame\C2DObject.h"
#include"..\Frame\Input.h"
#include"..\Frame\CGamepad.h"

#define MAX_COMAND_NUM 2

class CSelectCursor
{
public:
	void Initialize();
	void Update();
	void Draw();
	int  GetSelect()
	{
		return m_selectIndex;
	}
private:
	C2DObject m_2Dobj;

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_scale;
	BYTE diks[256];

	int m_selectIndex;
	float m_moveDistance;

};