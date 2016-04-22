#include"TestScene.h"

void CTestScene::Initialize()
{
	//test.Initialize();
	m_Player.Initialize();
	m_stage1.Initialize();
	camera.Initialize();
}

void CTestScene::Update()
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

	//camera.RotLongitudinal(m_Player.GetPosition().x);
	camera.SerBase(m_Player.GetPosition());



	//test.Update();
	m_Player.Update();
	m_stage1.Update();
}

void CTestScene::Draw()
{
	//test.Draw(camera.GetView());
	m_stage1.Draw(camera.GetView());
	/*これを実行すると半透明になる（半透明にするオブジェクトのときにする）*/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
 	 m_Player.Draw(camera.GetView());
	/*これ以降は半透明にならない処理*/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	
	camera.SerBase(D3DXVECTOR3(0.0,0.0,0.0));
}