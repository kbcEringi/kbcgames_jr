#pragma once

//ステージ2クラス
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"
#include "..\Frame\RayCursor.h"//カーソル

/********オブジェクト2D********/
/********オブジェクト3D********/
#include"..\Frame\C3DObject.h"
#include "Ground5.h"
#include "Stage1Back.h"
#include "Goal.h"

#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"

#include"..\Frame\Shadow.h"
#include"..\Frame\CGimmickManager.h"


#define MAX_COLLISION 100

class CAudio;
class C3DObject;


//enum GIMMICK{ AlwaysWind };

class CStage5 : public CStage
{
public:
	CStage5(){}
	~CStage5(){}
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

	CGround5 m_Ground5;
	CStage1Back m_Back1;
	CGoal m_Goal;

	//ギミックManager
	CGimmickManager m_gimmick;


};