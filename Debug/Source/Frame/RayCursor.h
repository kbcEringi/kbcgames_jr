#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include"Input.h"//キーボードインプット
#include "..\Game\Pointa.h"
#include"..\Frame\CGamepad.h"

class Ccamera;

//あたり判定

#define PI 3.14159265358979323846f

class CRayCursor
{
public:
	CRayCursor();
	~CRayCursor();
	void Initialize();
	void Update(D3DXVECTOR3 pos, D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix);
	void SetPointa(CPointa* pointa)
	{
		m_Pointa = pointa;
	}
private:
	float	m_interval;

	D3DXVECTOR4 start;
	D3DXVECTOR4 end;
	
	Ccamera*	m_pCamera;
	CPointa* m_Pointa;
	btSphereShape* m_sphereColli;

	BYTE diks[256];//キーインプット
};