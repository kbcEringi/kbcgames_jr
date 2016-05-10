#include"TitleScene.h"

void CTitleScene::Initialize()
{
	m_title.Initialize();
}

void CTitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000){
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::STAGE1);
	}
	m_title.Update();
}

void CTitleScene::Draw()
{
	m_title.Draw();
}