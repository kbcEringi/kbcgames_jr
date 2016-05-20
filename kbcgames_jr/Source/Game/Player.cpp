#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"

CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	m_SkinModel.Initialize("XFile\\unitychan.x");	//�v���C���[X�t�@�C��
	m_position.x = 0.0f;				//X���W
	m_position.y = 4.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	m_moveSpeed.x = 0.0f;				//�ړ����x
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//�ړ����x
	m_IsIntersect.CollisitionInitialize(&m_position);//�����蔻�菉����
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

}

void CPlayer::D3DUpdate()
{
	//Move();//�ړ��֐�
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	Died();
	m_IsIntersect.Intersect(&m_position, &m_moveSpeed);//m_position����̈ړ���(�����蔻��)
	
}

void CPlayer::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}

void CPlayer::Move(D3DXVECTOR3 movespeed)//�ړ�
{


	D3DXMatrixIdentity(&m_matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);
	m_moveSpeed.x = 0.0f;//�󂯂镗�̗͂�x���W�̏�����
	//m_moveSpeed.y = 0.0f;//�󂯂镗�̗͂�y���W�̏�����
	m_moveSpeed.z = 0.0f;//�󂯂镗�̗͂�z���W�̏�����
	//m_moveSpeed.y = 0.0f;
	if (m_position.x <= movespeed.x)//�E
	{
		m_position.x += 0.1f;
		//m_position.x += 0.2f;
	}
	if (m_position.x >= movespeed.x)//��
	{
		m_position.x -= 0.1f;
		//m_position.x -= 0.2f;
	}
	if (m_position.y <= movespeed.y)//��
	{
		m_position.y += 0.1f;
		//m_position.y += 0.2f;
	}
	if (m_position.y >= movespeed.y)//��
	{
		m_position.y -= 0.1f;
		//m_position.y -= 0.2f;
	}

}

void CPlayer::Died()
{
	if (m_position.y <= -5.0)
	{
		PostQuitMessage(0);
	}
}