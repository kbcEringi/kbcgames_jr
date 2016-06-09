#include"GameCursor.h"
#include "Stage1.h"

void CGameCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	vec3Scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	vec3Position = D3DXVECTOR3(480.0f, 280.0f, 0.0f);
	state = view;//�\�����Ă���

	m_pos3D.x = 0.0f;
	m_pos3D.y = 0.0f;
	m_pos3D.z = 0.0f;
}

void CGameCursor::Update()
{
	Move();//�ړ�����
	Pos3D();
}

void CGameCursor::Draw()
{
	if (state == view)
	{
		(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, FALSE);
		m_2Dobj.Draw(vec3Position, vec3Scale);
		(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);
	}
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

void CGameCursor::Pos3D()
{
#if 0
	D3DXMATRIX mView = g_stage->GetCamera()->GetViewMatrix();
	D3DXMATRIX mProj = g_stage->GetCamera()->GetProjectionMatrix();
	D3DVIEWPORT9 vp;
	(*graphicsDevice()).GetViewport(&vp);
	//�X�N���[�����W���烏�[���h���W�����߂�
	//2D�J�[�\�����W��3D���W�n�ɕϊ�����(Z�͐��K�����W�n��0.0)�B
	
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&m_pos3D),
		reinterpret_cast<const D3DXVECTOR3*>(&vec3Position),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);

//	D3DXVec3Normalize(&m_pos3D, &m_pos3D);
	m_pos3D.z = 0.0f;
#endif
}