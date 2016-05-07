#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"

#include"..\Frame\camera.h"
//#include"TestObj.h"
/********オブジェクト********/
#include "Player.h"
#include "Ground.h"
#include "wood.h"
#include "Debri.h"
#include "block1.h"

#include"..\BulletPhysics\BulletPhysics.h"

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

private:

	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;

	CCamera camera;
	CAudio* m_pAudio;
	/******オブジェクト*****/
	//CTestObj test;
	CPlayer m_Player;
	CGround m_Ground;
	CWood m_wood;
	CDebri m_Debri;
	CBlock1 m_Block1;
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody[MAX_COLLISION];	//剛体。
	btDefaultMotionState* m_myMotionState;
	
};