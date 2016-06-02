#include"GameScene.h"

void CGameScene::Initialize()
{
	
}

void CGameScene::Update()
{
	STAGEMANEGER->UpdateStage();
}

void CGameScene::Draw()
{
	STAGEMANEGER->DrawStage();
}