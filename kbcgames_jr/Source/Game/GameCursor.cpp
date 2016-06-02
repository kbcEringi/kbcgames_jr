#include"GameCursor.h"

void CGameCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	vec3Scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	vec3Position = D3DXVECTOR3(480.0f, 280.0f, 0.0f);
}

void CGameCursor::Update()
{
	Move();//�ړ�����
}

void CGameCursor::Draw()
{
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, FALSE);
	m_2Dobj.Draw(vec3Position, vec3Scale);
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);
}

void CGameCursor::Move()
{
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);

	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (KEYDOWN(diks, DIK_RIGHT) & 0x80 || GAMEPAD(CGamepad)->GetStickL_X()>0)//�E
		{
			vec3Position.x += 6.0f;
		}
		if (KEYDOWN(diks, DIK_LEFT) & 0x80 || GAMEPAD(CGamepad)->GetStickL_X()<0)//��
		{
			vec3Position.x -= 6.0f;
		}
		if (KEYDOWN(diks, DIK_UP) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() > 0)//��
		{
			vec3Position.y -= 6.0f;
		}
		if (KEYDOWN(diks, DIK_DOWN) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() < 0)//��
		{
			vec3Position.y += 6.0f;
		}
		else
		{
			(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
		}
	}
}