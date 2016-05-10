#include "Stage1.h"
#include "..\Frame\Audio.h"

//オブジェクトの詳細
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

SCollisionInfo collisionInfoTable[] = {
	{
		//Block1のコリジョン
		D3DXVECTOR3(0.0f, 2.0f, 0.0f),			//座標。
		D3DXVECTOR3(45.0f, 90.0f, 0.0f),		//回転。
		D3DXVECTOR3(2.0f, 2.0f, 2.0f),			//拡大。	
	},
	{
		//Ground1のコリジョン
		D3DXVECTOR3(2.0f, 0.0f, 0.0f),		//座標。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//回転。
		D3DXVECTOR3(6.0f, 2.0f, 2.0f),	//拡大。	
	},
	{
		//Ground2のコリジョン
		D3DXVECTOR3(6.0f, -1.0f, 0.0f),		//座標。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//回転。
		D3DXVECTOR3(3.0f, 2.0f, 2.0f),	//拡大。	
	},
	{
		//Ground3のコリジョン
		D3DXVECTOR3(10.5f, -2.0f, 0.0f),		//座標。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//回転。
		D3DXVECTOR3(5.0f, 2.0f, 2.0f),	//拡大。	
	},
	{
		//Ground4のコリジョン
		D3DXVECTOR3(15.0f, -1.0f, 0.0f),		//座標。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//回転。
		D3DXVECTOR3(3.0f, 2.0f, 2.0f),	//拡大。	
	},
	{
		//Ground5のコリジョン
		D3DXVECTOR3(18.0f, 0.0f, 0.0f),		//座標。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//回転。
		D3DXVECTOR3(3.0f, 2.0f, 2.0f),	//拡大。	
	},
	{
		//Ground1のコリジョン
		D3DXVECTOR3(24.5f, 1.0f, 0.0f),		//座標。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//回転。
		D3DXVECTOR3(6.0f, 2.0f, 2.0f),	//拡大。	
	},
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

	//test.Initialize();
	m_Player.Initialize();
	m_Ground.Initialize();
	m_wood.Initialize();
	camera.Initialize();
	m_Debri.Initialize();
	m_Block1.Initialize();
	m_pointa.Initialize();

	//D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	this->CreateCollision();

	

}

void CStage1::Update()
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
	m_pAudio->Run();	//周期タスク実行
	//test.Update();
	m_Player.Update();
	m_Ground.Update();
	m_wood.Update();
	m_Debri.Update();
	m_Block1.Update();
	m_pointa.Update();
	//ポインタをPlayerが追いかける
	if (m_Player.GetPosition().x <= m_pointa.GetPosition().x)
	{
		m_Player.Add(D3DXVECTOR3(0.02f, 0.0f, 0.0f));
	}
	if (m_Player.GetPosition().y <= m_pointa.GetPosition().y)
	{
		m_Player.Add(D3DXVECTOR3(0.0f, 0.02f, 0.0f));
	}
	if (m_Player.GetPosition().x >= m_pointa.GetPosition().x)
	{
		m_Player.subtract(D3DXVECTOR3(0.02f, 0.0f, 0.0f));
	}
	if (m_Player.GetPosition().y >= m_pointa.GetPosition().y)
	{
		m_Player.subtract(D3DXVECTOR3(0.0f, 0.02f, 0.0f));
	}
	//Playerを追いかけるカメラ
	camera.SerBase(m_Player.GetPosition());
	
}

void CStage1::Draw()
{

	//D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	//Obj.Draw(matWorld, view, m_projMatrix);
	//test.Draw(camera.GetView());

	m_Ground.Draw(camera.GetView());//ステージ１を描画
	m_Block1.Draw(camera.GetView());//ブロック１を描画
	m_Debri.Draw(camera.GetView());//テストでぶり
	
	/************これを実行すると半透明になる（半透明にするオブジェクトのときにする）***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
	}
	m_pointa.Draw(camera.GetView());//ポインタ描画
	m_wood.Draw(camera.GetView());	//木描画
	m_Player.Draw(camera.GetView());//Playerを描画
	
	/***************************これ以降は半透明にならない処理*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
	camera.SerBase(D3DXVECTOR3(0.0, 0.0, 0.0));

}

void CStage1::CreateCollision()
{
	int arraySize = ARRAYSIZE(collisionInfoTable);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionInfoTable[i];
		//ここで剛体とかを登録する。
		//剛体を初期化。
		{
			//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
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