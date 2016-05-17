#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	Obj.Initialize("XFile\\Player.x");	//�v���C���[X�t�@�C��
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X���W
	m_position.y = 4.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	m_moveSpeed.x = 0.0f;				//�ړ����x
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//�ړ����x
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	
	m_IsIntersect.CollisitionInitialize(&m_position);//�����蔻�菉����
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

}

void CPlayer::Update()
{
	//Move();//�ړ��֐�
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	m_IsIntersect.Intersect(&m_position, &m_moveSpeed);//m_position����̈ړ���(�����蔻��)
	
}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPlayer::Move(D3DXVECTOR3 movespeed)//�ړ�
{


	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	if (KEYDOWN(diks, DIK_SPACE) & 0x80)
	{
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
	else
	{
		(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
	}
}
