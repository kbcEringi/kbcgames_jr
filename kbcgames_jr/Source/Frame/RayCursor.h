#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include"Input.h"//�L�[�{�[�h�C���v�b�g
#include "..\Game\GameCursor.h"
#include "..\Game\Pointa.h"
#include "Ccamera.h"

//�����蔻��

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

	BYTE diks[256];//�L�[�C���v�b�g
};