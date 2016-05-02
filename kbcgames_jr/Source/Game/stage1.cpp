#include "Stage1.h"


CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize()
{
	Obj.Initialize("XFile\\stage1.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = -1.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("stage1");	//ステージ音楽再生
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

}

void CStage1::Update()
{
	m_pAudio->Run();	//周期タスク実行
}

void CStage1::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}