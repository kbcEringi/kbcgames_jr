#include"TitleScene.h"
#include "..\Frame\Audio.h"

void CTitleScene::Initialize()
{
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("title");	//ステージ音楽再生

	m_title.Initialize();
	m_TitleCursor.Initialize();
}

void CTitleScene::Update()
{
	m_pAudio->Run();	//周期タスク実行
	Select();//セレクト

	m_title.Update();
	m_TitleCursor.Update();
}

void CTitleScene::Draw()
{
	m_title.Draw();
	/************これを実行すると半透明になる（半透明にするオブジェクトのときにする）***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	m_TitleCursor.Draw();
	/***************************これ以降は半透明にならない処理*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
}

void CTitleScene::Select()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000){
		switch (m_TitleCursor.GetSelect())
		{
		case COMMAND_SELECT::START:
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::STAGE1);
			m_pAudio->StopCue("title");
			m_pAudio->PlayCue("start");
			break;
		case COMMAND_SELECT::EXIT:
			PostQuitMessage(0);
			break;
		}

	}
}