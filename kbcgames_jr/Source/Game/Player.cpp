#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"
#include "LostGround.h"

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
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	
	m_IsIntersect.CollisitionInitialize(&m_position);//�����蔻�菉����
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

}

void CPlayer::Update()
{
	Move(m_moveSpeed);//�ړ��֐�
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	Died();
	m_IsIntersect.Intersect(&m_position, &m_moveSpeed, m_callbackList);//m_position����̈ړ���(�����蔻��)
	
}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPlayer::Move(D3DXVECTOR3 movespeed)//�ړ�
{

#if 1
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	if (GetAsyncKeyState(VK_LEFT) ){
		m_moveSpeed.x = -4.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT) ){
		m_moveSpeed.x = 4.0f;
	}
	if (GetAsyncKeyState(VK_SHIFT)){
		if (GetAsyncKeyState(VK_UP)){
			m_moveSpeed.z = 4.0f;
		}
		if (GetAsyncKeyState(VK_DOWN)){
			m_moveSpeed.z = -4.0f;
		}
	}
	else{
		if (GetAsyncKeyState(VK_UP)){
			m_moveSpeed.y = 4.0f;
		}
	}

#else
	D3DXMatrixIdentity(&matWorld);
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
#endif

}

void CPlayer::Died()
{
	if (m_position.y <= -5.0)
	{
		PostQuitMessage(0);
	}
}