#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include"Input.h"//キーボードインプット
#include "..\Game\GameCursor.h"
#include "..\Game\Pointa.h"
#include "Ccamera.h"

//あたり判定

#define PI 3.14159265358979323846f

class CRayCursor
{
public:
	CRayCursor();
	~CRayCursor();
	void Initialize();
	void Update();
private:
	float	m_interval;
	Ccamera*	m_pCamera;
	CGameCursor m_GameCursor;
	CPointa m_Pointa;
	btSphereShape* m_sphereColli;

	BYTE diks[256];//キーインプット
};