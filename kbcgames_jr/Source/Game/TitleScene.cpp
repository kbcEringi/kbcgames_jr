#include"TitleScene.h"
#include "..\Frame\Audio.h"
#include"..\Frame\Stage\CStageManager.h"
#include"CDataLoad.h"

void CTitleScene::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = &Audio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("title");	//�^�C�g�����y�Đ�
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	m_camera.Initialize();
	m_camera.SetNear(0.1f);
	
	m_camera.SetDistance(4.0f);
	m_camera.RotLongitudinal(D3DXToRadian(-20.0f));
	m_camera.SetLookat(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	m_camera.UpdateProjectionMatrix();
	m_camera.Update();
	m_title.Initialize();
	m_continue.Initialize();
	m_start.Initialize();
	m_Unitychan.Init(m_Unitychan.Run);
}

void CTitleScene::Update()
{
	m_pAudio->Run();	//�����^�X�N���s
	m_camera.Update();
	m_title.Update();
	m_continue.Update();
	m_start.Update();
	m_Unitychan.Update();

	Select();//�Z���N�g
}

void CTitleScene::Draw()
{
	m_title.Draw();
	CDataLoad dl;
	int num = dl.LoadData();
#ifndef _DEBUG
	if (num > 0 && num<10)
#endif
	{
		m_continue.Draw();
	}
	m_start.Draw();
	(*graphicsDevice()).Clear(
		0,
		NULL,
		D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);
	m_Unitychan.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
}

void CTitleScene::Select()
{
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);


	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_A))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);
			m_pAudio->StopCue("title");//�^�C�g�����y�X�g�b�v
			m_pAudio->PlayCue("start");//�X�^�[�g

		}
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_B))
		{
			CDataLoad dl;
			int num = dl.LoadData();
			if (num > 0 && num<10)
			{
				STAGEMANEGER->SelectStage(num);
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

				m_pAudio->StopCue("title");//�^�C�g�����y�X�g�b�v
				m_pAudio->PlayCue("start");//�X�^�[�g
			}
		}
		
	}
	else
	{
		if (KEYDOWN(diks, DIK_RETURN))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

				m_pAudio->StopCue("title");//�^�C�g�����y�X�g�b�v
				m_pAudio->PlayCue("start");//�X�^�[�g
		}
		else if (KEYDOWN(diks, DIK_B))
		{
			CDataLoad dl;
			int num = dl.LoadData();
			if (num > 0 && num<10)
			{
				STAGEMANEGER->SelectStage(num);
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

				m_pAudio->StopCue("title");//�^�C�g�����y�X�g�b�v
				m_pAudio->PlayCue("start");//�X�^�[�g
			}
		
		}
		else
		{
			(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
		}
	}

	GAMEPAD(CGamepad)->UpdateControllerState();

}