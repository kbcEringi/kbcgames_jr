#include "Stage1Back.h"
#include"CGameFlg.h"
#include "..\Frame\Stage\CStageManager.h"

CStage1Back::~CStage1Back()
{

}

void CStage1Back::Initialize()
{
	m_pPlayer = NULL;
	m_SkinModel.Initialize("XFile\\sky.x");	//ぽいんたXファイル
	m_SkinModel.SetLuminance(true,0.2);
	m_SkinModel.Setshadowflg(false);

	m_position.x = 0.0f;				//X座標
	m_position.y = 120.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	m_SkinModel.GetLight()->m_ambientLight = D3DXVECTOR4(1,1,1,1);
	m_SkinModel.GetLight()->m_diffuseLightDirection[0] = D3DXVECTOR4(0, 0, 0, 0);
	m_SkinModel.GetLight()->m_diffuseLightDirection[1] = D3DXVECTOR4(0, 0, 0, 0);
	m_SkinModel.GetLight()->m_diffuseLightDirection[2] = D3DXVECTOR4(0, 0, 0, 0);
	m_SkinModel.GetLight()->m_diffuseLightDirection[3] = D3DXVECTOR4(0, 0, 0, 0);
	m_SkinModel.GetLight()->m_diffuseLightDirection[4] = D3DXVECTOR4(0, 0, 0, 0);
	m_SkinModel.GetLight()->m_diffuseLightDirection[5] = D3DXVECTOR4(0, 0, 0, 0);
	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45.0f), 960.0f / 580.0f, 1.0f, 10000.0f);
	m_targetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
}
void CStage1Back::Update()
{
	if (GAMEFLG->Getflg())
	{
		m_position.y = 85.0f;
	}
	else
	{
		m_position.y = 130.0f;
	}
}

void CStage1Back::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	if (m_pPlayer != NULL && STAGEMANEGER->GetStage()->GetPlayer()->GetState() != CPlayer::StateGoal)
	{
		m_targetPosition = m_pPlayer->GetPosition();
		
	}
	D3DXMatrixTranslation(&m_matWorld, m_targetPosition.x, m_targetPosition.y - m_position.y, m_targetPosition.z);
	m_SkinModel.Draw(m_matWorld, view, this->proj, m_matRot);
	(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}