#include"GameScene.h"
#include "Stage1.h"

void CGameScene::Initialize()
{
	
}

void CGameScene::Update()
{
	STAGEMANEGER->UpdateStage();
	Deid();
	
}

void CGameScene::Draw()
{
	STAGEMANEGER->DrawStage();
}

void CGameScene::Deid()
{
	if (g_stage->GetPlayer()->GetDeid() == true)
	{
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::RESULT);
	}
}