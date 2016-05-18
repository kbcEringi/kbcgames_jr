#include "SetWind.h"
#include "Stage1.h"

/*!
*@brief	ID3DXMeshからAABBのサイズを計算する関数。
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
	int stride = D3DXGetFVFVertexSize(desc.FVF);
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


CSetWind::CSetWind()
{
	m_force.x = 0.0f;
	m_force.y = 0.0f;
	m_force.z = 0.0f;
}


CSetWind::~CSetWind()
{
}

void CSetWind::Initialize()
{
	Obj.Initialize("XFile\\wood.x");
	CalcAABBSizeFromMesh(Obj.GetMesh(), m_aabbMin, m_aabbMax);
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 18.0f;
	m_position.y = 4.0f;
	m_position.z = 0.0f;
	D3DXQUATERNION rot;
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;
	rot.w = 1.0f;
	D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 3.14f*0.0f);
	D3DXMatrixRotationQuaternion(&m_rotationMatrix, &rot);
	m_aabbMin += m_position;
	m_aabbMax += m_position;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	/*size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);*/

}

void CSetWind::Update()
{
	CPlayer* player = g_stage->GetPlayer();
	D3DXVECTOR3 pos = player->GetPosition();
	if (m_aabbMin.x < pos.x
		&& m_aabbMin.y < pos.y
		&& m_aabbMin.z < pos.z
		&& m_aabbMax.x > pos.x
		&& m_aabbMax.y > pos.y
		&& m_aabbMax.z > pos.z
		){
		m_force = D3DXVECTOR3(17.0f, 0.0f, 0.0f);
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
		}else{
			m_force *= 0.95f;
		}
	}
	player->ApplyForce(m_force);

}

void CSetWind::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	
	Obj.Draw(matWorld, view, m_projMatrix);
}
