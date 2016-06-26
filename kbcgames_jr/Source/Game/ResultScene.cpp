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
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化

	
}

void CResultScene::Update()
{
	m_pAudio->Run();	//周期タスク実行

	

	if (GetAsyncKeyState(VK_RETURN))
	{
		exit(0);
	}

	//Select();//セレクト
}

void CResultScene::Draw()
{
	
}