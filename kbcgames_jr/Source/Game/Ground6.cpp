#include "Ground6.h"

CGround6::~CGround6()
{
}

void CGround6::Initialize()
{
	m_SkinModel.Initialize("XFile\\stage_06.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	m_SkinModel.GetLight()->m_ambientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[3] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[4] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[5] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVECTOR4 dir = D3DXVECTOR4(-0.75f, -0.75f, -0.75f, 1.0f);
	D3DXVec4Normalize(&dir, &dir);
	m_SkinModel.GetLight()->m_diffuseLightDirection[3] = dir;
}

void CGround6::Update()
{

}

void CGround6::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}