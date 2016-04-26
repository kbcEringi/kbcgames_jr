#include "Player.h"


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
	m_position.y = 0.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	m_Ground = true;					//���n�ʂɂ��Ă��邩�H�iTRUE�j
	NowPositionY = 0.0f;				//���̃|�W�V����
	Gravity = -0.2;						//�d��
	MaxJump = 1.0f;						//�W�����v�����
	SpeedPower = 0.0f;					//���������
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
}

void CPlayer::Update()
{
	
	Move();//�ړ��֐�
	//Jump();//�v���C���[�W�����v�֐�

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}

void CPlayer::Move()//�ړ�
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);
	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//�E
	{
		m_position.x += 0.2f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//��
	{
		m_position.x -= 0.2f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//��
	{
		m_position.y += 0.2f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//��
	{
		m_position.y -= 0.2f;
	}
	else
	{
		(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
	}
}

//void CPlayer::Jump()//�W�����v
//{
//	//�W�����v����(�n�ʂɂ��Ă��鎞)
//	if (m_Ground == true && KEYDOWN(diks, DIK_SPACE) & 0x80)
//	{
//		NowPositionY = m_position.y;//���̃|�W�V��������
//		m_Ground = false;
//		SpeedPower = MaxJump;
//		
//		
//	}
//	//�n�ʂɂ��Ă��Ȃ���
//	if (!m_Ground)
//	{
//		SpeedPower += Gravity;
//		m_position.y += SpeedPower;
//		if (NowPositionY >= m_position.y)
//			m_Ground = true;
//	}
//	
//}