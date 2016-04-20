#include"TestScene.h"

void CTestScene::Initialize()
{
	test.Initialize();
	camera.Initialize();
}

void CTestScene::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
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
	}
	test.Update();
}

void CTestScene::Draw()
{
	test.Draw(camera.GetView());
	camera.SerBase(D3DXVECTOR3(0.0,0.0,0.0));
}