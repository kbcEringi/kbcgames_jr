#include "Pointa.h"
#include "Stage1.h"
#include"..\Frame\Stage\CStageManager.h"

CPointa::~CPointa()
{

}

void CPointa::Initialize()
{
	m_SkinModel.Initialize("XFile\\Pointa.x");	//ぽいんたXファイル
	//m_SkinModel.Sethureneruflg(true);
	m_SkinModel.SetLuminance(true, 2.0f);
	m_SkinModel.SetNormalMap("Texture\\1_normals.png");
	m_position.x = 2.0f;				//X座標
	m_position.y = 5.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標

	m_moveSpeed.x = 0.0f;				//X座標
	m_moveSpeed.y = 5.0f;				//Y座標
	m_moveSpeed.z = 0.0f;				//Z座標

	DrawFlag = false;

}

void CPointa::Update()
{

}

void CPointa::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	D3DXVECTOR3 pos;
	pos = m_position - STAGEMANEGER->GetStage()->GetPlayer()->GetPosition();//プレイヤーとの距離を求める。
	pos.y = 0.0f;
	if (DrawFlag == true)
	{
		m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
	}
}