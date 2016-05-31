#pragma once

#include"..\Frame\DXCommon.h"
#include"..\Frame\Scene.h"
#include"..\Frame\Ccamera.h"
#include "..\Frame\RayCursor.h"//�J�[�\��

/********�I�u�W�F�N�g2D********/
#include "GameCursor.h"
/********�I�u�W�F�N�g3D********/
#include"..\Frame\C3DObject.h"
#include "Player.h"
#include "Ground.h"
#include "wood.h"
#include "AlwaysWind.h"
#include "Windmill.h"
#include "Movefloor.h"
#include "Debri.h"
#include "Pointa.h"
#include "Stage1Back.h"
#include "LostGround.h"
#include "GameCursorWind.h"
#include "Hasu.h"
#include "Goal.h"

#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"

#include"..\Frame\Shadow.h"
#include"..\Frame\CGimmickManager.h"

#define MAX_COLLISION 100

class CSceneManager;
class CAudio;
class C3DObject;

enum GIMMICK{ AlwaysWind };

class CStage1 : public CScene
{
public:
	CStage1(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();
	void CreateCollision3D();
	void CreateCollision2D();
	void Add3DRigidBody();
	void Add2DRigidBody();
	void Remove3DRigidBody();
	void Remove2DRigidBody();
	CPlayer* GetPlayer()
	{
		return &m_Player;
	}
	Ccamera* GetCamera()
	{
		return &m_camera;
	}
	CGameCursor* GetCursor()
	{
		return &m_GameCursor;
	}
private:

	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;

	Ccamera m_camera;
	CAudio* m_pAudio;
	CRayCursor m_Ray;
	/********�I�u�W�F�N�g2D********/
	CGameCursor m_GameCursor;
	/******�I�u�W�F�N�g3d*****/
	//CTestObj test;
	CPlayer m_Player;
	CGround m_Ground;
	CWood m_wood;
	CPointa m_pointa;
	//CAlwaysWind m_setwind;
	CWindmill m_windmill;
	CMovefloor m_Movefloor;
	CStage1Back m_Back1;
	CLostGround m_lost;
	CGameCursorWind m_GCursorWind;
	CHasu m_hasu;
	CGoal m_Goal;

	//�M�~�b�NManager
	CGimmickManager m_gimmick;

	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3D[MAX_COLLISION];	//����3D�B
	btRigidBody*		m_rigidBody2D[MAX_COLLISION];	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
	bool				m_isAdd3DCollision;
};
extern CStage1* g_stage;