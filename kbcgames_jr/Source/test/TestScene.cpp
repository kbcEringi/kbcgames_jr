#include"TestScene.h"


CShadowMap g_Shadow;

void CTestScene::Initialize()
{
	testob.Initialize();

	g_Shadow.Create(512, 512);
	g_Shadow.SetLightPosition(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	g_Shadow.SetLightDirection(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	g_Shadow.Entry(&testob);

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

	g_Shadow.Update();
	jimen.Update();
	camera.SerBase(testob.GetTrans());
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
}

void CTestScene::Draw()
{
	testob.Draw(camera.GetView(), m_projMatrix);
	jimen.Draw(camera.GetView());

	camera.SerBase(D3DXVECTOR3(0.0,0.0,0.0));
}