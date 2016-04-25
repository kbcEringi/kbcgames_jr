#include"TestScene.h"

void CTestScene::Initialize()
{
	testob.Initialize();
	jimen.Initialize();
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
	testob.Update();
	jimen.Update();
	camera.SerBase(testob.GetTrans());
}

void CTestScene::Draw()
{
	testob.Draw(camera.GetView());
	jimen.Draw(camera.GetView());
	camera.SerBase(D3DXVECTOR3(0.0,0.0,0.0));
}