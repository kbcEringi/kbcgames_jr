#include"CFlower.h"
#include"..\Frame\C3DDraw.h"

CFlower::CFlower()
{
	m_vPos = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRot);
}

CFlower::~CFlower()
{

}

void CFlower::Init(SFlower Data)
{

	m_Model.Initialize("XFile\\flower.x");
	m_vPos = Data.pos;
}

void CFlower::Render(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_vPos.x, m_vPos.y, m_vPos.z);

	m_Model.Draw(m_matWorld, view, proj, m_matRot);
}