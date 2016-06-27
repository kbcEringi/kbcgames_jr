#include "TitleUnitychan.h"
#include "Stage1.h"
#include"..\Frame\Stage\CStageManager.h"



CTitleUnitychan::~CTitleUnitychan()
{

}

void CTitleUnitychan::Init(UnitychanAnim ani)
{
	m_SkinModel.Initialize("XFile\\Unity.x");	//ぽいんたXファイル
	m_SkinModel.Setshadowflg(false);
	
	m_position.x = -2.5f;				//X座標
	m_position.y = -1.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標

	m_currentAngleY = 0.0f;

	m_SkinModel.GetLight()->m_ambientLight = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[0] = D3DXVECTOR4(-1.0, 0.0f, 1.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[1] = D3DXVECTOR4(1.0, 0.0f, 1.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[3] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[4] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[5] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);

	m_SkinModel.GetLight()->m_diffuseLightColor[0] = D3DXVECTOR4(0.25, 0.2f, 0.2f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightColor[1] = D3DXVECTOR4(0.25, 0.2f, 0.2f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightColor[2] = D3DXVECTOR4(0.25, 0.2f, 0.2f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightColor[3] = D3DXVECTOR4(0.4, 0.4f, 0.4f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightColor[4] = D3DXVECTOR4(0.25, 0.2f, 0.2f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightColor[5] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);

	//D3DXVECTOR4 dir = D3DXVECTOR4(0.0f, 0.0f, 0.5f, 1.0f);
	//D3DXVec4Normalize(&dir, &dir);
	//m_SkinModel.GetLight()->m_diffuseLightDirection[3] = dir;
	m_SkinModel.SetAnimationEndTime(Run, 0.8f);


	m_SkinModel.Setunitychanflg();
	m_SkinModel.SetAnimation(ani);
}

void CTitleUnitychan::Update()
{
	m_SkinModel.AddAnimation();
	
}

void CTitleUnitychan::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{

	

	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.UpdateWorldMatrix(m_matWorld);
	D3DXMatrixRotationY(&m_matRot, m_currentAngleY + D3DXToRadian(190.0f));
	m_matWorld = m_matRot * m_matWorld;
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);

}
