#include"ResultScene.h"
#include "..\Frame\Audio.h"

void CResultScene::Initialize()
{
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化

	m_gameover.Initialize();
}

void CResultScene::Update()
{
	m_pAudio->Run();	//周期タスク実行

	m_gameover.Update();

	if (GetAsyncKeyState(VK_RETURN))
	{
		exit(0);
	}

	//Select();//セレクト
}

void CResultScene::Draw()
{
	m_gameover.Draw();
}

//void CResultScene::Select()
//{
//	(*GetKeyDevice()).GetDeviceState(
//		sizeof(diks),	// パラメータ バッファサイズ
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
//				m_pAudio->StopCue("title");//タイトル音楽ストップ
//				m_pAudio->PlayCue("uni1512");//スタート
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
//				m_pAudio->StopCue("title");//タイトル音楽ストップ
//				m_pAudio->PlayCue("uni1512");//スタート
//				break;
//			case COMMAND_SELECT::EXIT:
//				PostQuitMessage(0);
//				break;
//			}
//		}
//		else
//		{
//			(*GetKeyDevice()).Acquire();//キーデバイス取得
//		}
//	}
//}