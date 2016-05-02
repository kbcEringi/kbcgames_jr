#include "Stage1.h"
#include "..\Frame\Audio.h"

void CStage1::Initialize()
{
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("stage1");	//ステージ音楽再生
	//test.Initialize();
	m_Player.Initialize();
	/*m_Ground.Initialize();*/
	m_wood.Initialize();
	camera.Initialize();
}

void CStage1::Update()
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
	m_pAudio->Run();	//周期タスク実行
	camera.SerBase(m_Player.GetPosition());//Playerを追いかけるカメラ

	//test.Update();
	m_Player.Update();
	/*m_Ground.Update();*/
	m_wood.Update();
}

void CStage1::Draw()
{
	//test.Draw(camera.GetView());
	/*m_Ground.Draw(camera.GetView());*///ステージ１を描画
	/************これを実行すると半透明になる（半透明にするオブジェクトのときにする）***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
	}

	m_Player.Draw(camera.GetView());//Playerを描画
	m_wood.Draw(camera.GetView());	//木描画
	/***************************これ以降は半透明にならない処理*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
	camera.SerBase(D3DXVECTOR3(0.0, 0.0, 0.0));
}