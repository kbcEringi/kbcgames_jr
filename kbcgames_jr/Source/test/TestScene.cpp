#include"TestScene.h"

void CTestScene::Initialize()
{
	ZeroMemory(diks, sizeof(diks));
	
	test.Initialize();
	jimen.Initialize();
	gazou.Initialize();

	camera.Initialize();
}

void CTestScene::Update()
{
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	if (KEYDOWN(diks, DIK_UP) & 0x80)
	{
		camera.RotLongitudinal(0.05f);
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)
	{
		camera.RotLongitudinal(-0.05f);
	}
	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)
	{
		camera.RotTransversal(-0.05f);
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)
	{
		camera.RotTransversal(0.05f);
	}
	else
	{
		(*GetKeyDevice()).Acquire();
	}

	test.Update();
	jimen.Update();
	gazou.Update();
}

void CTestScene::Draw()
{
	test.Draw(camera.GetView());
	jimen.Draw(camera.GetView());
	gazou.Draw();

	camera.SerBase(test.GetTrans());
}