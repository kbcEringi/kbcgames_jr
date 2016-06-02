#include "Debri.h"

void CDebri::Initialize()
{
	m_SkinModel.Initialize("XFile\\Debri.x");	//�v���C���[X�t�@�C��
	m_position.x = 0.0f;				//X���W
	m_position.y = 20.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	m_Rigidbody.Initialize(&m_position, &size);
}
void CDebri::D3DUpdate()
{
	//�����G���W���Ōv�Z���ꂽ���̂̈ʒu�Ɖ�]�𔽉f������B
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