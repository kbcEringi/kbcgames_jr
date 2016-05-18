#include "Stage1.h"
#include "..\Frame\Audio.h"

CStage1* g_stage = NULL;
//オブジェクトの詳細
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

SCollisionInfo collisionInfoTable3D[] = {
#include "CollisionInfo3D.h"
};

SCollisionInfo collisionInfoTable2D[] = {
#include "CollisionInfo2D.h"
};


void CStage1::Initialize()
{
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("stage1");	//ステージ音楽再生

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

	m_Player.Initialize();
	m_Ground.Initialize();
	m_wood.Initialize();
	m_setwind.Initialize();
	m_camera.Initialize();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));
	m_Debri.Initialize();
	m_pointa.Initialize();
	m_GameCursor.Initialize();


	m_Ray.Initialize();//レイカーソル初期化
	//D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	this->CreateCollision();
	g_stage = this;
}

void CStage1::Update()
{
	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//	m_camera.RotLongitudinal(0.05f);
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//	m_camera.RotLongitudinal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//{
	//	m_camera.RotTransversal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//{
	//	m_camera.RotTransversal(0.05f);
	//}

	m_pAudio->Run();	//周期タスク実行
	m_camera.SetLookat(m_Player.GetPosition());//Playerを追いかけるカメラ
	m_camera.Update();
	m_Player.Update();
	m_Ground.Update();
	m_wood.Update();
	m_setwind.Update();
	m_Debri.Update();
	m_pointa.Update();
	m_GameCursor.Update();
	//ポインタをPlayerが追いかける
	m_Player.Move(m_pointa.GetPosition());
	//レイカーソルに値をセット
	m_Ray.Update(m_GameCursor.GetPosition(), m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
}

void CStage1::Draw()
{
	m_Ground.Draw(m_camera.GetViewMatrix());//ステージ１を描画
	m_Debri.Draw(m_camera.GetViewMatrix());//テストでぶり
	m_pointa.Draw(m_camera.GetViewMatrix());//ポインタ描画
	
	/************これを実行すると半透明になる（半透明にするオブジェクトのときにする）***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
	}

	m_Player.Draw(m_camera.GetViewMatrix());//Playerを描画
	m_wood.Draw(m_camera.GetViewMatrix());	//木描画
	m_setwind.Draw(m_camera.GetViewMatrix());//風描画
	m_GameCursor.Draw();
	/***************************これ以降は半透明にならない処理*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
}

void CStage1::CreateCollision()
{
	int arraySize = ARRAYSIZE(collisionInfoTable3D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionInfoTable3D[i];
		//ここで剛体とかを登録する。
		//剛体を初期化。
		{
			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, -collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
			m_rigidBody[i] = new btRigidBody(rbInfo);

			//ワールドに追加。
			g_bulletPhysics.AddRigidBody(m_rigidBody[i]);

		}
	}

}