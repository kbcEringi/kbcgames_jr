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
	Obj.Initialize("XFile\\unitychan.x");	//�v���C���[X�t�@�C��
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X���W
	m_position.y = 4.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	m_moveSpeed.x = 0.0f;				//�ړ����x
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//�ړ����x

	m_targetAngleY = 0.0f;				//�L�����A���O��
	m_currentAngleY = 0.0f;
	//��
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

	m_Turn.Initialize();
	m_IsIntersect.CollisitionInitialize(&m_position);//�����蔻�菉����
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

}

void CPlayer::Update()
{
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	Died();//���S
	Move(m_Pointa->GetPosition());
	m_IsIntersect.Intersect(&m_position, &m_moveSpeed);//m_position����̈ړ���(�����蔻��)
	
}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	//��]�s����쐬����B
	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, m_currentAngleY);
	matWorld = mRot * matWorld;
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPlayer::Move(D3DXVECTOR3 pos)//�ړ�
{
	bool isTurn = false;
	

	//D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);
	m_moveSpeed.x = 0.0f;//�󂯂镗�̗͂�x���W�̏�����
	//m_moveSpeed.y = 0.0f;//�󂯂镗�̗͂�y���W�̏�����
	m_moveSpeed.z = 0.0f;//�󂯂镗�̗͂�z���W�̏�����
	if (m_position.x < pos.x && fabs(m_position.x - pos.x) > 0.1f)//�E
	{
		m_moveSpeed.x += 1.0f;
		//�E����
		m_targetAngleY = D3DXToRadian(-90.0f);
		isTurn = true;
	}
	if (m_position.x > pos.x && fabs(m_position.x - pos.x) > 0.1f)//��
	{
		m_moveSpeed.x -= 1.0f;
		//����������������
		m_targetAngleY = D3DXToRadian(90.0f);
		isTurn = true;
	}
	if (m_position.z < pos.z && fabs(m_position.z - pos.z) > 0.1f)//��
	{
		m_moveSpeed.z += 1.0f;
		//���
 		m_targetAngleY = D3DXToRadian(180.0f);
		isTurn = true;
	}
	if (m_position.z > pos.z && fabs(m_position.z - pos.z) > 0.1f)//��
	{
		m_moveSpeed.z -= 1.0f;
		//����
		m_targetAngleY = D3DXToRadian(0.0f);
		isTurn = true;
	}
	m_currentAngleY = m_Turn.Update(isTurn, m_targetAngleY);
	

}

void CPlayer::Died()
{
	if (m_position.y <= -5.0)
	{
		PostQuitMessage(0);
	}
}