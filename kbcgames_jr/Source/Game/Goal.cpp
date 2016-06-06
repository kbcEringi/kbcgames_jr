#include "Goal.h"
#include"..\Frame\Stage\CStageManager.h"


CGoal::~CGoal()
{
}

void CGoal::Initialize()
{
	m_SkinModel.Initialize("XFile\\Goal.x");

	CalcAABBSizeFromMesh(m_SkinModel.GetMesh(), m_aabbMin, m_aabbMax);//AABB
	m_position.x = 255.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	m_aabbMin += m_position;
	m_aabbMax += m_position;
}

void CGoal::Update()
{
	D3DXVECTOR3 pos = STAGEMANEGER->GetStage()->GetPlayer()->GetPosition();
	
	if (m_aabbMin.x < pos.x
		&& m_aabbMin.y < pos.y
		&& m_aabbMin.z < pos.z
		&& m_aabbMax.x > pos.x
		&& m_aabbMax.y > pos.y
		&& m_aabbMax.z > pos.z
		)
	{
		MessageBox(NULL, TEXT("Goal"), 0, MB_OK);
		exit(0);
	}
}

void CGoal::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}