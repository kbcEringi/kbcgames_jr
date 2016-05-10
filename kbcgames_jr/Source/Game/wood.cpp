#include "wood.h"


CWood::CWood()
{
}


CWood::~CWood()
{
}

void CWood::Initialize()
{
	Obj.Initialize("XFile\\wood.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 18.0f;
	m_position.y = 10.0f;
	m_position.z = 0.0f;
	m_Ground = true;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	m_Rigidbody.Initialize(&m_position, &size);//剛体初期化

}

void CWood::Update()
{
	//テストコード
	if ((GetAsyncKeyState('A') & 0x8000) != 0){
		m_Ground = false;
		m_force.y = 0.1f;
	}
	if (m_Ground==false){//地面に付いてない時
		m_position.y -= m_force.y;
		m_position.y *= 1.01f;
	}
	if (m_force.x > 0.0f){
		m_position.x += m_force.x;
		m_force.x *= 0.85f;
	}
	m_Rigidbody.Update(&m_position);//剛体アップデート
}

void CWood::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	m_Rigidbody.Draw();		//剛体draw
	Obj.Draw(matWorld, view, m_projMatrix);
}

