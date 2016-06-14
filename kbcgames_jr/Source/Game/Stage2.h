#pragma once

//ステージ2クラス
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"
#include "..\Frame\RayCursor.h"//カーソル

/********オブジェクト2D********/
/********オブジェクト3D********/
#include"..\Frame\C3DObject.h"
#include "Ground2.h"
#include "wood.h"
#include "AlwaysWind.h"
#include "Windmill.h"
#include "Movefloor.h"
#include "Stage1Back.h"
#include "LostGround.h"
#include "Hasu.h"
#include "Goal.h"

#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"

#include"..\Frame\Shadow.h"
#include"..\Frame\CGimmickManager.h"


#define MAX_COLLISION 100

class CAudio;
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

	CAudio* m_pAudio;
	CRayCursor m_Ray;

	CGround2 m_Ground2;
	CWood m_wood;
	CWindmill m_windmill;
	CMovefloor m_Movefloor;
	CStage1Back m_Back1;
	CLostGround m_lost;
	CHasu m_hasu;
	CGoal m_Goal;

	//ギミックManager
	CGimmickManager m_gimmick;

};