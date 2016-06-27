#pragma once

//ステージ3クラス
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"
#include "..\Frame\RayCursor.h"//カーソル

/********オブジェクト2D********/
/********オブジェクト3D********/
#include"..\Frame\C3DObject.h"
#include "Ground3.h"
#include "Stage1Back.h"
#include "Goal.h"

#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"

#include"..\Frame\Shadow.h"
#include"..\Frame\CGimmickManager.h"


#define MAX_COLLISION 100

class C3DObject;


//enum GIMMICK{ AlwaysWind };

class CStage3 : public CStage
{
public:
	CStage3(){}
	~CStage3(){}
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

	CGround3 m_Ground3;
	CStage1Back m_Back1;
	CGoal m_goal;

	//ギミックManager
	CGimmickManager m_gimmick;

	int GoalCount;
};