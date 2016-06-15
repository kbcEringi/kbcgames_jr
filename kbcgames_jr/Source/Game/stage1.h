#pragma once

//ステージ１クラス
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"
#include "..\Frame\RayCursor.h"//カーソル

/********オブジェクト2D********/
/********オブジェクト3D********/
#include"..\Frame\C3DObject.h"
#include "Ground.h"

#include "Stage1Back.h"

#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"
#include"..\Frame\Shadow.h"
#include"..\Frame\CGimmickManager.h"

#include"Goal.h"

class CAudio;
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

	CAudio* m_pAudio;
	CRayCursor m_Ray;
	
	CGround m_Ground;

	CStage1Back m_Back1;

	CGoal m_goal;

	//ギミックManager
	CGimmickManager m_gimmick;

};