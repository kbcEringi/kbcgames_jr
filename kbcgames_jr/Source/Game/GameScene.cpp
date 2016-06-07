#include"GameScene.h"
#include"..\Frame\Stage\CStageManager.h"

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
	/*if (STAGEMANEGER->GetStage()->GetPlayer()->GetDeid() == true)
	{
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::RESULT);
	}*/
}