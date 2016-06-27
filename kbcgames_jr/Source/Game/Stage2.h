#pragma once

//�X�e�[�W2�N���X
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"
#include "..\Frame\RayCursor.h"//�J�[�\��

/********�I�u�W�F�N�g2D********/
/********�I�u�W�F�N�g3D********/
#include"..\Frame\C3DObject.h"
#include "Ground2.h"
#include "Stage1Back.h"
#include "Goal.h"

#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"

#include"..\Frame\Shadow.h"
#include"..\Frame\CGimmickManager.h"


#define MAX_COLLISION 100

class C3DObject;


//enum GIMMICK{ AlwaysWind };

class CStage2 : public CStage
{
public:
	CStage2(){}
	~CStage2(){}
	void Initialize();
	void Update();
	void Draw();
	void CreateCollision3D();
	void CreateCollision2D();

private:

	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;

	CRayCursor m_Ray;

	CGround2 m_Ground2;
	CStage1Back m_Back1;
	CGoal m_goal;

	//�M�~�b�NManager
	CGimmickManager m_gimmick;

	int GoalCount;
};