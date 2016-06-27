#pragma once

#include "..\..\Game\Player.h"
#include "..\Ccamera.h"
#include "..\..\Game\GameCursor.h"
#include "..\..\Game\Pointa.h"
#include "..\..\Game\GameCursor3D.h"
#include "..\..\Game\GameCursorWind.h"
#include"..\Shadow.h"
#include"..\..\Game\CDataLoad.h"

#define MAX_COLLISION 100

//オブジェクトの詳細
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

class CAudio;

//今後ステージは此奴を継承する
class CStage
{
public:
	CStage();
	virtual ~CStage(){}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void SetStageAudio();
	void StopStageAudio();
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
	CGameCursor3D* GetCursor3D()
	{
		return&m_GameCursor3D;
	}
	CPointa* GetPointa()
	{
		return &m_pointa;
	}
	CGameCursorWind* GetWind()
	{
		return&m_GCursorWind;
	}
	void Add3DRigidBody(int arraySize);
	void Add2DRigidBody(int arraySize);
	void Remove3DRigidBody(int arraySize);
	void Remove2DRigidBody(int arraySize);
protected:
	void ExecuteChangeCamera(int araySize2D,int araySize3D);
protected:
	CPlayer m_Player;
	Ccamera m_camera;
	CGameCursor m_GameCursor;
	CPointa m_pointa;
	CGameCursor3D m_GameCursor3D;
	CGameCursorWind m_GCursorWind;


	bool				isButtomTriger;
	bool				isDied;

	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3D[MAX_COLLISION];	//剛体3D。
	btRigidBody*		m_rigidBody2D[MAX_COLLISION];	//剛体2D。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
	bool				m_isAdd3DCollision;

	CDataLoad dl;

	CAudio* m_pAudio;
	D3DXVECTOR3 syokipos;
};

extern CShadowMap g_Shadow;