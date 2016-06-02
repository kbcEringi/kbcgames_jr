#include"SelectScene.h"

void CSelectScene::Initialize()
{
	m_cursor.Initialize();
}

void CSelectScene::Update()
{
	m_cursor.Update();

	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);

	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_A))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);
		}
	}
	else
	{
		if (KEYDOWN(diks, DIK_A))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);
		}
	}
}

void CSelectScene::Draw()
{
	m_cursor.Draw();
}