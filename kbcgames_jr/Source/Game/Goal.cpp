#include "Goal.h"
#include"..\Frame\Stage\CStageManager.h"
#include"..\Frame\SceneManager.h"
#include "..\Frame\Audio.h"

SParicleEmitParameter GoalparticleParameterTbl
{
	"Texture\\goal_particle.png",	//const char* texturePath;						//!<テクスチャのファイルパス。
	D3DXVECTOR3(0.0f, 10.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<初速度。
	1.5f,							//float		life;								//!<寿命。単位は秒。
	0.02f,							//float		intervalTime;						//!<発生時間。単位は秒。
	0.5,							//float		w;									//!<パーティクルの幅。
	0.2,							//float		h;									//!<パーティクルの高さ。
	D3DXVECTOR3(0.5f, 0.0f, 0.5f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<初期位置のランダム幅。
	D3DXVECTOR3(4.0f, 0.3f, 4.0f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
	D3DXVECTOR3(1.0f, 0.5f, 1.0f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
	D3DXVECTOR3(0.0f, -9.8f, 0.0f),		//D3DXVECTOR3	gravity;							//!<重力。
	true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
	0.1f,							//float		fadeTime;							//!<フェードする時間。
	1.0f,							//float		initAlpha;							//!<初期アルファ値。
	true,							//bool		isBillboard;						//!<ビルボード？
	1.3f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
	0,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
};

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

	/*GoalparticleParameterTbl.initPositionRandomMargin = initPositionRandomMargin;
	GoalparticleParameterTbl.initVelocity = initSpeed * 5;*/
	emi.Init(random, *STAGEMANEGER->GetStage()->GetCamera(), GoalparticleParameterTbl, m_position);

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
	emi.Update();
}

void CGoal::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	if (goalflag == true)
	{
		emi.Render();
	}
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}