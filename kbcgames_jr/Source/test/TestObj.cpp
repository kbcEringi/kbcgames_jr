#include"TestObj.h"


void CTestObj::Initialize()
{
	Obj.Initialize("XFile\\kyu2.x");
	vecTrans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ZeroMemory(diks, sizeof(diks));
}

void CTestObj::Update()
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	if (KEYDOWN(diks, DIK_W) & 0x80)
	{
		vecTrans.z += 0.05;
	}
	if (KEYDOWN(diks, DIK_S) & 0x80)
	{
		vecTrans.z += -0.05;
	}
	if (KEYDOWN(diks, DIK_A) & 0x80)
	{
		vecTrans.x += -0.05;
	}
	if (KEYDOWN(diks, DIK_D) & 0x80)
	{
		vecTrans.x += 0.05;
	}
	else
	{
		(*GetKeyDevice()).Acquire();
	}
	D3DXMatrixTranslation(&matTrans, vecTrans.x, vecTrans.y, vecTrans.z);
	matWorld *= matTrans;
}

void CTestObj::Draw(D3DXMATRIX view)
{
	Obj.Draw(matWorld, view);
}