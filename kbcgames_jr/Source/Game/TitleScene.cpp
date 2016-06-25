#include"TitleScene.h"
#include "..\Frame\Audio.h"
#include"..\Frame\Stage\CStageManager.h"
#include"CDataLoad.h"

void CTitleScene::Initialize()
{
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("title");	//タイトル音楽再生
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
	m_camera.Initialize();
	m_camera.SetNear(0.1f);
	
	m_camera.SetDistance(4.0f);
	m_camera.RotLongitudinal(D3DXToRadian(-20.0f));
	m_camera.SetLookat(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	m_camera.UpdateProjectionMatrix();
	m_camera.Update();
	m_title.Initialize();
	m_start.Initialize();
	m_Unitychan.Initialize();
}

void CTitleScene::Update()
{
	m_pAudio->Run();	//周期タスク実行
	m_camera.Update();
	m_title.Update();
	m_start.Update();
	m_Unitychan.Update();

	Select();//セレクト
}

void CTitleScene::Draw()
{
	m_title.Draw();
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
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);


	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_A))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);
			m_pAudio->StopCue("title");//タイトル音楽ストップ
			m_pAudio->PlayCue("start");//スタート

		}
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_B))
		{
			CDataLoad dl;
			int num = dl.LoadData();
			if (num > 0)
			{
				STAGEMANEGER->SelectStage(num);
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

				m_pAudio->StopCue("title");//タイトル音楽ストップ
				m_pAudio->PlayCue("start");//スタート
			}
		}
		
	}
	else
	{
		if (KEYDOWN(diks, DIK_RETURN))
		{
			STAGEMANEGER->SelectStage(1);
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

				m_pAudio->StopCue("title");//タイトル音楽ストップ
				m_pAudio->PlayCue("start");//スタート
		}
		else if (KEYDOWN(diks, DIK_B))
		{
			CDataLoad dl;
			int num = dl.LoadData();
			if (num > 0)
			{
				STAGEMANEGER->SelectStage(num);
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::GAME);

				m_pAudio->StopCue("title");//タイトル音楽ストップ
				m_pAudio->PlayCue("start");//スタート
			}
		
		}
		else
		{
			(*GetKeyDevice()).Acquire();//キーデバイス取得
		}
	}

	GAMEPAD(CGamepad)->UpdateControllerState();

}