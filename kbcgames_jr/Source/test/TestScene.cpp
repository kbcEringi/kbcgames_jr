#include"TestScene.h"

void CTestScene::Initialize()
{
	testob.Initialize();
	jimen.Initialize();
	camera.Initialize();
	testPost.Initialize();
	gazo.Initialize();
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
	testPost.Update();
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
}

void CTestScene::Draw()
{
	//testob.Draw(camera.GetView(), m_projMatrix);
	jimen.Draw(camera.GetView());
	testPost.Draw(camera.GetView());

	//gazo.Draw();

	camera.SerBase(D3DXVECTOR3(0.0,0.0,0.0));
}