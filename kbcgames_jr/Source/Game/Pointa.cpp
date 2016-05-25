#include "Pointa.h"

CPointa::~CPointa()
{

}

void CPointa::Initialize()
{
	m_SkinModel.Initialize("XFile\\Pointa.x");	//ぽいんたXファイル
	m_position.x = 2.0f;				//X座標
	m_position.y = 5.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標

	m_moveSpeed.x = 0.0f;				//X座標
	m_moveSpeed.y = 5.0f;				//Y座標
	m_moveSpeed.z = 0.0f;				//Z座標
}

void CPointa::D3DUpdate()
{

}

void CPointa::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}