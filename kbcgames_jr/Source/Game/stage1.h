#pragma once

//�X�e�[�W�P�N���X
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"


/********�I�u�W�F�N�g2D********/
/********�I�u�W�F�N�g3D********/
#include "..\Frame\RayCursor.h"//�J�[�\��
#include"..\Frame\C3DObject.h"
#include "Ground.h"
#include"Goal.h"
#include "Stage1Back.h"

#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"
#include"..\Frame\CGimmickManager.h"

#include"FlowerManager.h"

class C3DObject;

enum GIMMICK{ AlwaysWind };

class CStage1 : public CStage
{
public:
	CStage1(){}
	~CStage1(){}
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
	CGround m_Ground;
	CStage1Back m_Back1;
	CGoal m_goal;
	//�M�~�b�NManager
	CGimmickManager m_gimmick;
	FlowerManager m_flower;

	int GoalCount;//�S�[���㉽�t���[������Ɏ��̃X�e�[�W��
};