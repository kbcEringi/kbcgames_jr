#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"

#include"..\Frame\Ccamera.h"
//#include"TestObj.h"
/********2D�I�u�W�F�N�g********/
#include "GameCursor.h"
/********3d�I�u�W�F�N�g********/
#include "Player.h"
#include "Ground.h"
#include "wood.h"
#include "Debri.h"
#include "Pointa.h"

#include"..\BulletPhysics\BulletPhysics.h"//�����蔻��

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

private:

	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;

	Ccamera m_camera;
	CAudio* m_pAudio;
	/******2D�I�u�W�F�N�g*****/
	CGameCursor m_GCursor;
	/******3D�I�u�W�F�N�g*****/
	//CTestObj test;
	CPlayer m_Player;
	CGround m_Ground;
	CWood m_wood;
	CDebri m_Debri;
	CPointa m_pointa;

	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody[MAX_COLLISION];	//���́B
	btDefaultMotionState* m_myMotionState;
	
};