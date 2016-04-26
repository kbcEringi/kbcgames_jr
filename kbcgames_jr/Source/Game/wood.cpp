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
	m_position.x = 8.0f;
	m_position.y = 2.0f;
	m_position.z = 0.0f;
}

void CWood::Update()
{

	if (m_Ground=0){//’n–Ê‚É•t‚¢‚Ä‚È‚¢Žž
		
	}
	if (m_force.x > 0.0f){
		m_position.x += m_force.x;
		m_force.x *= 0.85f;
	}

}

void CWood::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}