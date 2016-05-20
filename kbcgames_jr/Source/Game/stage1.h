#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"

#include"..\Frame\Ccamera.h"

/********オブジェクト********/
#include "..\Frame\RayCursor.h"//カーソル
/********オブジェクト2D********/
#include "GameCursor.h"
/********オブジェクト3D********/
#include "Player.h"
#include "Ground.h"
#include "wood.h"
#include "AlwaysWind.h"
#include "Debri.h"
#include "Pointa.h"

#include"..\BulletPhysics\BulletPhysics.h"

#include"..\Frame\CGamepad.h"

#include"..\Frame\Shadow.h"

#define MAX_COLLISION 100

class CSceneManager;
class CAudio;

class CStage1 : public CScene
{
public:
	CStage1(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();
	void CreateCollision();
	CPlayer* GetPlayer()
	{
		return &m_Player;
	}
private:

	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;

	Ccamera m_camera;
	CAudio* m_pAudio;
	/******オブジェクト*****/
	CRayCursor m_Ray;
	/********オブジェクト3D********/
	CGameCursor m_GameCursor;
	/******オブジェクト3d*****/
	//CTestObj test;
	CPlayer m_Player;
	CGround m_Ground;
	CWood m_wood;
	CDebri m_Debri;
	CPointa m_pointa;
	CAlwaysWind m_setwind;

	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody[MAX_COLLISION];	//剛体。
	btDefaultMotionState* m_myMotionState;
	
};
extern CStage1* g_stage;