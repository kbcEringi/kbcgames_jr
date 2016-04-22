#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	Obj.Initialize("XFile\\Player.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X���W
	m_position.y = 0.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	m_Ground = true;					//���n�ʂɂ��Ă��邩�H�iTRUE�j
	NowPositionY = 0.0f;				//���̃|�W�V����
	Gravity = -0.2;						//�d��
	MaxJump = 1.0f;						//�W�����v�����
	SpeedPower = 0.0f;
}

void CPlayer::Update()
{
	if (GetAsyncKeyState('D'))
	{
		m_position.x += 0.2f;
	}
	else if (GetAsyncKeyState('A'))
	{
		m_position.x -= 0.2f;
	}
	else if (GetAsyncKeyState('W'))
	{
		m_position.y += 0.2f;
	}
	else if (GetAsyncKeyState('S'))
	{
		m_position.y -= 0.2f;
	}
	Jump();

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}

void CPlayer::Jump()
{
	//�W�����v����(�n�ʂɂ��Ă���)
	if (m_Ground == true && GetAsyncKeyState(VK_SPACE))
	{
		m_Ground = false;
		SpeedPower = MaxJump;
		NowPositionY = m_position.y;//���̃|�W�V��������
		
	}
	//�n�ʂɂ��Ă��Ȃ�
	if (!m_Ground)
	{
		SpeedPower += Gravity;
		m_position.y += SpeedPower;
		if (NowPositionY <= m_position.y)
			m_Ground = true;
	}
	
}