#include"ResultScene.h"
#include "..\Frame\Audio.h"

void CResultScene::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������

	m_gameover.Initialize();
}

void CResultScene::Update()
{
	m_pAudio->Run();	//�����^�X�N���s

	m_gameover.Update();

	if (GetAsyncKeyState(VK_RETURN))
	{
		exit(0);
	}

	//Select();//�Z���N�g
}

void CResultScene::Draw()
{
	m_gameover.Draw();
}

//void CResultScene::Select()
//{
//	(*GetKeyDevice()).GetDeviceState(
//		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
//		&diks);
//
//	GAMEPAD(CGamepad)->UpdateControllerState();
//	if (GAMEPAD(CGamepad)->GetConnected())
//	{
//		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_A)){
//			switch (m_gameoverCusor.GetSelect())
//			{
//			case COMMAND_SELECT::START:
//				SINSTANCE(CSceneManager)->ChangeScene(SCENE::SELECT);
//
//				m_pAudio->StopCue("title");//�^�C�g�����y�X�g�b�v
//				m_pAudio->PlayCue("uni1512");//�X�^�[�g
//				break;
//			case COMMAND_SELECT::EXIT:
//				PostQuitMessage(0);
//				break;
//			}
//
//		}
//
//	}
//	else
//	{
//		if (KEYDOWN(diks, DIK_RETURN))
//		{
//			switch (m_gameoverCusor.GetSelect())
//			{
//			case COMMAND_SELECT::START:
//				SINSTANCE(CSceneManager)->ChangeScene(SCENE::SELECT);
//
//				m_pAudio->StopCue("title");//�^�C�g�����y�X�g�b�v
//				m_pAudio->PlayCue("uni1512");//�X�^�[�g
//				break;
//			case COMMAND_SELECT::EXIT:
//				PostQuitMessage(0);
//				break;
//			}
//		}
//		else
//		{
//			(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
//		}
//	}
//}