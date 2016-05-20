#include "Pointa.h"

CPointa::~CPointa()
{

}

void CPointa::Initialize()
{
	m_SkinModel.Initialize("XFile\\Pointa.x");	//ぽいんたXファイル
	m_position.x = 2.0f;				//X座標
	m_position.y = 5.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標

	m_moveSpeed.x = 0.0f;				//X座標
	m_moveSpeed.y = 5.0f;				//Y座標
	m_moveSpeed.z = 0.0f;				//Z座標
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
}

void CPointa::D3DUpdate()
{
	//Move();//移動関数

}

void CPointa::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}

void CPointa::Move()//移動
{
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
