#include "Ground3.h"

CGround3::~CGround3()
{
}

void CGround3::Initialize()
{
	m_SkinModel.Initialize("XFile\\stage_03.x");
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

void CGround3::Update()
{

}

void CGround3::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}