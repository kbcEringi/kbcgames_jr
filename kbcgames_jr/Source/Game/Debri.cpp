#include "Debri.h"

void CDebri::Initialize()
{
	m_SkinModel.Initialize("XFile\\Debri.x");	//プレイヤーXファイル
	m_position.x = 0.0f;				//X座標
	m_position.y = 20.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	m_Rigidbody.Initialize(&m_position, &size);
}
void CDebri::D3DUpdate()
{
	//物理エンジンで計算された剛体の位置と回転を反映させる。
	m_Rigidbody.Update(&m_position);
}
void CDebri::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_Rigidbody.Draw();
	m_SkinModel.Draw(m_matWorld, view, proj);
}
void CDebri::OnDestroy()
{
	m_Rigidbody.OnDestroy();
}