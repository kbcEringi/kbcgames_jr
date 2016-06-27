#include "Goal.h"
#include"..\Frame\Stage\CStageManager.h"
#include"..\Frame\SceneManager.h"
#include "..\Frame\Audio.h"
#ifdef _DEBUG
#include"..\Frame\CGamepad.h"
#endif

SParicleEmitParameter GoalparticleParameterTbl
{
	"Texture\\goal_particle.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
	D3DXVECTOR3(0.0f, 10.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
	1.5f,							//float		life;								//!<�����B�P�ʂ͕b�B
	0.02f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
	0.5,							//float		w;									//!<�p�[�e�B�N���̕��B
	0.2,							//float		h;									//!<�p�[�e�B�N���̍����B
	D3DXVECTOR3(0.5f, 0.0f, 0.5f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
	D3DXVECTOR3(4.0f, 0.3f, 4.0f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
	D3DXVECTOR3(1.0f, 0.5f, 1.0f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
	D3DXVECTOR3(0.0f, -9.8f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
	true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	0.1f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
	1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
	true,							//bool		isBillboard;						//!<�r���{�[�h�H
	1.3f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	0,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
};

CGoal::~CGoal()
{
}

void CGoal::Initialize(D3DXVECTOR3 pos)
{
	m_SkinModel.Initialize("XFile\\Goal.x");
	m_SkinModel.SetLuminance(false, 0.0f);
	//�I�[�f�B�I������
	m_pAudio = &Audio();
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

	/*GoalparticleParameterTbl.initPositionRandomMargin = initPositionRandomMargin;
	GoalparticleParameterTbl.initVelocity = initSpeed * 5;*/
	emi.Init(random, *STAGEMANEGER->GetStage()->GetCamera(), GoalparticleParameterTbl, D3DXVECTOR3(m_position.x+3.0f,m_position.y+3.0f,m_position.z));

	goalflag = false;
	OnGoal = false;
}

void CGoal::Update()
{
#ifdef _DEBUG
	if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_Y))
	{
		goalflag = true;
	}
#endif
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
			goalflag = true;
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
			goalflag = true;

		}
	}
	emi.Update();
}

void CGoal::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	if (goalflag == true)
	{
		emi.Render();
	}
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CGoal::SetGoalAudio()
{
	if (OnGoal == false)
	{
		m_pAudio->PlayCue("goal");
		OnGoal = true;
	}
}

void CGoal::StopGoalAudio()
{

	if (OnGoal == true)
	{
		m_pAudio->StopCue("goal");
		OnGoal = false;
	}
}