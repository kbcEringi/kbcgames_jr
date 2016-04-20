#include"TestObj.h"

void CTestObj::Initialize()
{
	Obj.Initialize("XFile\\kyu.x");
	//Obj.Initialize("XFile\\player.x");
	D3DXMatrixIdentity(&matWorld);
}

void CTestObj::Update()
{

}

void CTestObj::Draw(D3DXMATRIX view)
{
	Obj.SetWorldMatrix(matWorld);
	Obj.SetviewMatrix(view);
	Obj.Draw();
}