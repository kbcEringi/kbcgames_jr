#pragma once
#include"..\Frame\C3DObject.h"

struct SFlower
{
	D3DXVECTOR3 pos;
	int type;
};

class CFlower
{
public:
	CFlower();
	~CFlower();
	void Init(SFlower Data);
	void Render(D3DXMATRIX view, D3DXMATRIX proj);
private:
	C3DDraw m_Model;
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matRot;
	D3DXVECTOR3 m_vPos;
};