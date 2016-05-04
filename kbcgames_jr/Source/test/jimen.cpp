#include"jimen.h"

void CTestjimen::Initialize()
{
	Obj.Initialize("XFile\\box.x",0);

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

}

void CTestjimen::Update()
{
	D3DXMatrixIdentity(&matWorld);
	vecTrans = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	D3DXMatrixTranslation(&matTrans, vecTrans.x, vecTrans.y, vecTrans.z);
	matWorld *= matTrans;
}

void CTestjimen::Draw(D3DXMATRIX view)
{
	Obj.Draw(matWorld, view, m_projMatrix);
}