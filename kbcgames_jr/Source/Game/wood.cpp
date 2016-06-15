#include "wood.h"
CWood::~CWood()
{
}

void CWood::Initialize()
{
	m_SkinModel.Initialize("XFile\\wood.x");

	m_Ground = true;
	size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	m_Rigidbody.Initialize(&m_data.position, &size);//剛体初期化

}

void CWood::Update()
{
	//テストコード
	//if ((GetAsyncKeyState('A') & 0x8000) != 0){
	//	m_Ground = false;
	//	m_force.y = 0.1f;
	//}
	//if (m_Ground==false){//地面に付いてない時
	//	m_position.y -= m_force.y;
	//	m_position.y *= 1.01f;
	//}
	//if (m_force.x > 0.0f){
	//	m_position.x += m_force.x;
	//	m_force.x *= 0.85f;
	//}
	//m_Rigidbody.Update(&m_position);//剛体アップデート
}

void CWood::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_data.position.x, m_data.position.y, m_data.position.z);
	m_Rigidbody.Draw();		//剛体draw
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}

