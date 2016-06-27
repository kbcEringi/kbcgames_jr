#include"ResultScene.h"
#include "..\Frame\Audio.h"

void CResultScene::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = &Audio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("yuniyu-ni");
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	GAMEFLG->Set3D();
	m_camera.Initialize();
	m_camera.SetNear(0.1f);
	m_camera.SetDistance(4.0f);
	m_camera.RotLongitudinal(D3DXToRadian(-20.0f));
	m_camera.SetLookat(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	m_camera.Update();

	

	m_StageClear.Initialize();
	m_Select.Initialize();
	CTUnitychan.Init(CTUnitychan.Jump);
	
}

void CResultScene::Update()
{
	m_pAudio->Run();	//�����^�X�N���s
	m_camera.Update();
	m_StageClear.Update();
	m_Select.Update();
	CTUnitychan.Update();

	Select();//�Z���N�g
}

void CResultScene::Draw()
{
	m_StageClear.Draw();
	m_Select.Draw();
	(*graphicsDevice()).Clear(
		0,
		NULL,
		D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);
	CTUnitychan.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
}

void CResultScene::Select()
{
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);


	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_A))
		{
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
			m_pAudio->StopCue("yuniyu-ni");//�^�C�g�����y�X�g�b�v
			m_pAudio->PlayCue("unitychanderu");//�X�^�[�g

		}
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_B))
		{
			exit(0);
		}

	}
	else
	{
		if (KEYDOWN(diks, DIK_RETURN))
		{
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
			m_pAudio->StopCue("yuniyu-ni");//�^�C�g�����y�X�g�b�v
			m_pAudio->PlayCue("unitychanderu");//�X�^�[�g
		}
		else if (KEYDOWN(diks, DIK_B))
		{
			
			exit(0);

		}
		else
		{
			(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
		}
	}

	GAMEPAD(CGamepad)->UpdateControllerState();

}