#include "AlwaysWind.h"
#include "Stage1.h"
#include "..\Frame\Stage\CStageManager.h"
#include "CGameFlg.h"
#include "..\Frame\Audio.h"

/*!
*@brief	ID3DXMesh����AABB�̃T�C�Y���v�Z����֐��B
*@param[in]	mesh		ID3DXMesh
*/


void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max)
{
	D3DXVECTOR3 size;
	min.x = FLT_MAX;
	min.y = FLT_MAX;
	min.z = FLT_MAX;
	max.x = -FLT_MAX;
	max.y = -FLT_MAX;
	max.z = -FLT_MAX;
	LPDIRECT3DVERTEXBUFFER9 vb;
	mesh->GetVertexBuffer(&vb);
	D3DVERTEXBUFFER_DESC desc;
	vb->GetDesc(&desc);
	//int stride = D3DXGetFVFVertexSize(desc.FVF);
	int stride = 80; //@todo ��������
	char* pVB = NULL;
	vb->Lock(0, desc.Size, (void**)&pVB, D3DLOCK_DISCARD);
	int numVertex = desc.Size / stride;
	for (int vertNo = 0; vertNo < numVertex; vertNo++) {
		float* pVertexPos = (float*)(pVB);
		min.x = min(min.x, pVertexPos[0]);
		min.y = min(min.y, pVertexPos[1]);
		min.z = min(min.z, pVertexPos[2]);
		max.x = max(max.x, pVertexPos[0]);
		max.y = max(max.y, pVertexPos[1]);
		max.z = max(max.z, pVertexPos[2]);
		pVB += stride;
	}
	vb->Unlock();
}


SParicleEmitParameter particleParameterTbl
{
	"Texture\\leaf.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
	D3DXVECTOR3(5.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
	1.5f,							//float		life;								//!<�����B�P�ʂ͕b�B
	0.1f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
	1.0f,							//float		w;									//!<�p�[�e�B�N���̕��B
	1.0f,							//float		h;									//!<�p�[�e�B�N���̍����B
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
	D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
	D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
	true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	0.1f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
	1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
	true,							//bool		isBillboard;						//!<�r���{�[�h�H
	1.3f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	0,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
};

CAlwaysWind::CAlwaysWind() : C3DObject()
{
	m_force.x = 0.0f;
	m_force.y = 0.0f;
	m_force.z = 0.0f;
}


CAlwaysWind::~CAlwaysWind()
{
}

void CAlwaysWind::Initialize()
{
	
	m_SkinModel.Initialize("XFile\\wood.x");
	//CalcAABBSizeFromMesh(m_SkinModel.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMax.z = 1.5f;
	m_aabbMin.z = -1.5f;
	m_aabbMax.y = 0.5f;
	m_aabbMin.y = -0.5f;
	m_aabbMax.x = 5.0f*1.5;
	m_aabbMin.x = 0;
	//m_data.position.x = 14.0f;
	//m_data.position.y = 1.0f;
	//m_data.position.z = 0.0f;

	/*D3DXQUATERNION rot;
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;
	rot.w = 1.0f;
	D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 3.14f*0.25f);*/
	D3DXMatrixRotationQuaternion(&m_rotationMatrix, &m_data.rotation);
	m_aabbMin += m_data.position;
	m_aabbMax += m_data.position;

	D3DXVECTOR3 initPositionRandomMargin;
	initPositionRandomMargin.x = m_rotationMatrix.m[2][0];
	initPositionRandomMargin.y = m_rotationMatrix.m[2][1];
	initPositionRandomMargin.z = m_rotationMatrix.m[2][2];
	initPositionRandomMargin *= 3.0f;
	initPositionRandomMargin.x += m_rotationMatrix.m[1][0];
	initPositionRandomMargin.y += m_rotationMatrix.m[1][1];
	initPositionRandomMargin.z += m_rotationMatrix.m[1][2];

	initPositionRandomMargin.x += m_rotationMatrix.m[0][0];
	initPositionRandomMargin.y += m_rotationMatrix.m[0][1];
	initPositionRandomMargin.z += m_rotationMatrix.m[0][2];

	D3DXVECTOR3 initSpeed;
	initSpeed.x = m_rotationMatrix.m[0][0];
	initSpeed.y = m_rotationMatrix.m[0][1];
	initSpeed.z = m_rotationMatrix.m[0][2];

	particleParameterTbl.initPositionRandomMargin = initPositionRandomMargin;
	particleParameterTbl.initVelocity = initSpeed *5;
	emi.Init(random, *STAGEMANEGER->GetStage()->GetCamera(), particleParameterTbl, m_data.position);

	//�I�[�f�B�I������
	m_pAudio = &Audio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	AudioFlag = false;
	/*size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);*/

}

void CAlwaysWind::Update()
{

	CPlayer* player = STAGEMANEGER->GetStage()->GetPlayer();
	D3DXVECTOR3 pos = player->GetPosition();
	//2D�̎�
	if (GAMEFLG->Getflg()){
		if (m_aabbMin.x < pos.x
			&& m_aabbMin.y < pos.y
			&& m_aabbMax.x > pos.x
			&& m_aabbMax.y > pos.y
			){
			m_force = D3DXVECTOR3(70.0f, 0.0f, 0.0f);
			D3DXVECTOR4 force;
			D3DXVec3Transform(&force, &m_force, &m_rotationMatrix);
			m_force.x = force.x;
			m_force.y = force.y;
		}
		else{
			if (D3DXVec3Length(&m_force) < 0.1f){
				m_force.x = 0.0f;
				m_force.y = 0.0f;
			}
			else{
				m_force *= 0.95f;
			}
		}
	}
	else {
		if (m_aabbMin.x < pos.x
			&& m_aabbMin.y < pos.y
			&& m_aabbMin.z < pos.z
			&& m_aabbMax.x > pos.x
			&& m_aabbMax.y > pos.y
			&& m_aabbMax.z > pos.z
			){
			m_force = D3DXVECTOR3(70.0f, 0.0f, 0.0f);
			D3DXVECTOR4 force;
			D3DXVec3Transform(&force, &m_force, &m_rotationMatrix);
			m_force.x = force.x;
			m_force.y = force.y;
			m_force.z = force.z;
		}
		else{
			if (D3DXVec3Length(&m_force) < 0.1f){
				m_force.x = 0.0f;
				m_force.y = 0.0f;
				m_force.z = 0.0f;
			}
			else{
				m_force *= 0.95f;
			}
		}
	}
	if (D3DXVec3LengthSq(&m_force) > 0.01f) {
		
		player->ApplyForce(m_force);
		player->SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	emi.Update();
}

void CAlwaysWind::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	emi.Render();

	D3DXMatrixTranslation(&m_matWorld, m_data.position.x, m_data.position.y, m_data.position.z);
	
	//m_SkinModel.Draw(m_matWorld, view, proj);
}
