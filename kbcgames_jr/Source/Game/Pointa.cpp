#include "Pointa.h"

CPointa::CPointa()
{

}

CPointa::~CPointa()
{

}

void CPointa::Initialize()
{
	Obj.Initialize("XFile\\Pointa.x");	//ぽいんたXファイル
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X座標
	m_position.y = 5.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標

	m_moveSpeed.x = 0.0f;				//X座標
	m_moveSpeed.y = 5.0f;				//Y座標
	m_moveSpeed.z = 0.0f;				//Z座標
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);


}

void CPointa::Update()
{
	Move();//移動関数

}

void CPointa::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPointa::Move()//移動
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);

	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//右
	{
		m_position.x += 0.1f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//左
	{
		m_position.x -= 0.1f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//上
	{
		m_position.y += 0.1f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//下
	{
		m_position.y -= 0.1f;
	}
	else
	{
		(*GetKeyDevice()).Acquire();//キーデバイス取得
	}
	
}
