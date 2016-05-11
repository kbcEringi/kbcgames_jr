#include "Debri.h"

void CDebri::Initialize()
{
	Obj.Initialize("XFile\\Debri.x");	//プレイヤーXファイル
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X座標
	m_position.y = 20.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	m_Rigidbody.Initialize(&m_position, &size);
}
void CDebri::Update()
{
	//物理エンジンで計算された剛体の位置と回転を反映させる。
	m_Rigidbody.Update(&m_position);
}
void CDebri::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	m_Rigidbody.Draw();
	Obj.Draw(matWorld, view, m_projMatrix);
}
void CDebri::OnDestroy()
{
	m_Rigidbody.OnDestroy();
}