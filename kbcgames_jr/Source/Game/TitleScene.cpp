#include"TitleScene.h"

void CTitleScene::Initialize()
{
	m_title.Initialize();
}

void CTitleScene::Update()
{
	/*if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		camera.RotLongitudinal(0.05f);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		camera.RotLongitudinal(-0.05f);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		camera.RotTransversal(-0.05f);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		camera.RotTransversal(0.05f);
	}*/
	
	m_title.Update();
}

void CTitleScene::Draw()
{
	camera.SerBase(D3DXVECTOR3(0.0, 0.0, 0.0));
	m_title.Draw();
}