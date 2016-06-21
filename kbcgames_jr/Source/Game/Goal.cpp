#include "Goal.h"
#include"..\Frame\Stage\CStageManager.h"
#include"..\Frame\SceneManager.h"
#include "..\Frame\Audio.h"

CGoal::~CGoal()
{
}

void CGoal::Initialize(D3DXVECTOR3 pos)
{
	m_SkinModel.Initialize("XFile\\Goal.x");
	m_SkinModel.SetLuminance(true, 2.0f);
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");

	CalcAABBSizeFromMesh(m_SkinModel.GetMesh(), m_aabbMin, m_aabbMax);//AABB
	m_position.x = pos.x;
	m_position.y = pos.y;
	m_position.z = pos.z;
	m_aabbMin += m_position;
	m_aabbMax += m_position;
	m_SkinModel.Sethureneruflg(true);

	goalflag = false;
}

void CGoal::Update()
{
	m_pAudio->Run();
	D3DXVECTOR3 pos = STAGEMANEGER->GetStage()->GetPlayer()->GetPosition();
	if (GAMEFLG->Getflg() == true)
	{
		if (m_aabbMin.x < pos.x
			&& m_aabbMin.y < pos.y
			&& m_aabbMax.x > pos.x
			&& m_aabbMax.y > pos.y
			)
		{
			/*MessageBox(NULL, TEXT("Goal"), 0, MB_OK);
			exit(0);*/
			goalflag = true;
			m_pAudio->PlayCue("goal");
		}
	}
	else
	{
		if (m_aabbMin.x < pos.x
			&& m_aabbMin.y < pos.y
			&& m_aabbMin.z < pos.z
			&& m_aabbMax.x > pos.x
			&& m_aabbMax.y > pos.y
			&& m_aabbMax.z > pos.z
			)
		{
			/*MessageBox(NULL, TEXT("Goal"), 0, MB_OK);
			exit(0);*/
			goalflag = true;
			m_pAudio->PlayCue("goal");
		}
	}
	m_pAudio->StopCue("goal");
}

void CGoal::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}