#include"TestObj.h"

void CTestObj::Initialize()
{
	Obj.Initialize("XFile\\kyu.x");
	D3DXMatrixIdentity(&matWorld);
}

void CTestObj::Update()
{

}

void CTestObj::Draw(D3DXMATRIX view)
{
	Obj.Draw(matWorld, view);
}