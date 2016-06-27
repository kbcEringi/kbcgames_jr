#include"ResultScene.h"
#include "..\Frame\Audio.h"

void CResultScene::Initialize()
{
	//オーディオ初期化
	m_pAudio = &Audio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("yuniyu-ni");
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
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
	m_pAudio->Run();	//周期タスク実行
	m_camera.Update();
	m_StageClear.Update();
	m_Select.Update();
	CTUnitychan.Update();

	Select();//セレクト
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
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);


	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_A))
		{
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
			m_pAudio->StopCue("yuniyu-ni");//タイトル音楽ストップ
			m_pAudio->PlayCue("unitychanderu");//スタート

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
			m_pAudio->StopCue("yuniyu-ni");//タイトル音楽ストップ
			m_pAudio->PlayCue("unitychanderu");//スタート
		}
		else if (KEYDOWN(diks, DIK_B))
		{
			
			exit(0);

		}
		else
		{
			(*GetKeyDevice()).Acquire();//キーデバイス取得
		}
	}

	GAMEPAD(CGamepad)->UpdateControllerState();

}