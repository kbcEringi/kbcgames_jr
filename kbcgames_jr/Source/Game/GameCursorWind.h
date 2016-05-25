#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

class CGameCursorWind : public C3DObject
{
public:
	CGameCursorWind() : C3DObject(){}
	~CGameCursorWind();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
private:
	D3DXVECTOR3 m_position;
};
