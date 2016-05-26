#include "Stage1Back.h"

CStage1Back::~CStage1Back()
{

}

void CStage1Back::Initialize()
{
	m_SkinModel.Initialize("XFile\\Back.x");	//�ۂ���X�t�@�C��
	m_position.x = 0.0f;				//X���W
	m_position.y = 0.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
}

void CStage1Back::D3DUpdate()
{

}

void CStage1Back::D3DDraw(D3DXMATRIX view, D3DXMATRIX proj)
{
	(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	D3DXMatrixTranslation(&m_matWorld, m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z);
	m_SkinModel.Draw(m_matWorld, view, proj);
	(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}