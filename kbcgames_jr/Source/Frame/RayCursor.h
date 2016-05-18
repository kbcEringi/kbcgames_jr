#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include"Input.h"//�L�[�{�[�h�C���v�b�g
#include "..\Game\Pointa.h"

class Ccamera;

//�����蔻��

#define PI 3.14159265358979323846f

class CRayCursor
{
public:
	CRayCursor();
	~CRayCursor();
	void Initialize();
	void Update(D3DXVECTOR3 pos, D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix);
private:
	float	m_interval;
	Ccamera*	m_pCamera;
	CPointa m_Pointa;
	btSphereShape* m_sphereColli;

	BYTE diks[256];//�L�[�C���v�b�g
};