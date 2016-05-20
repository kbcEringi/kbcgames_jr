#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"

#include"..\Frame\Ccamera.h"

/********�I�u�W�F�N�g********/
#include "..\Frame\RayCursor.h"//�J�[�\��
//#include"TestObj.h"
/********�I�u�W�F�N�g2D********/
#include "GameCursor.h"
/********�I�u�W�F�N�g3D********/
#include "Player.h"
#include "Ground.h"
#include "wood.h"
#include "AlwaysWind.h"
#include"Windmill.h"
#include "Debri.h"
#include "Pointa.h"

#include"..\BulletPhysics\BulletPhysics.h"

#include"..\Frame\CGamepad.h"

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
	CRayCursor m_Ray;
	/********�I�u�W�F�N�g2D********/
	CGameCursor m_GameCursor;
	/******�I�u�W�F�N�g3d*****/
	//CTestObj test;
	CPlayer m_Player;
	CGround m_Ground;
	CWood m_wood;
	CDebri m_Debri;
	CPointa m_pointa;
	CAlwaysWind m_setwind;
	//CWindmill m_windmill;

	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody[MAX_COLLISION];	//���́B
	btDefaultMotionState* m_myMotionState;
	
};
extern CStage1* g_stage;