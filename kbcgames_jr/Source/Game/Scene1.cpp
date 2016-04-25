#include "Scene1.h"

void CScene1::Initialize()
{
	//test.Initialize();
	m_Player.Initialize();
	m_stage1.Initialize();
	m_wood.Initialize();
	camera.Initialize();
}

void CScene1::Update()
{
	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//camera.RotLongitudinal(0.05f);
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//camera.RotLongitudinal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//{
	//camera.RotTransversal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//{
	//camera.RotTransversal(0.05f);
	//}

	//camera.RotLongitudinal(m_Player.GetPosition().x);
	camera.SerBase(m_Player.GetPosition());//Playerを追いかけるカメラ

	//test.Update();
	m_Player.Update();
	m_stage1.Update();
	m_wood.Update();

	/*m_aabb.isIntersected(m_Player.GetPosition());
	m_aabb.SetPosition(m_Player.GetPosition());
	m_aabb.SetSize(m_Player.GetPosition());
	m_aabb.CalcAABBSizeFromMesh(m_Player.GetMesh());*/
}

void CScene1::Draw()
{
	//test.Draw(camera.GetView());
	m_stage1.Draw(camera.GetView());//ステージ１を描画
	/*これを実行すると半透明になる（半透明にするオブジェクトのときにする）*/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(2.0f,0.0f,0.0f));
	}
	m_Player.Draw(camera.GetView());
	m_wood.Draw(camera.GetView());
	m_Player.Draw(camera.GetView());//Playerを描画
	/*これ以降は半透明にならない処理*/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	camera.SerBase(D3DXVECTOR3(0.0, 0.0, 0.0));
}