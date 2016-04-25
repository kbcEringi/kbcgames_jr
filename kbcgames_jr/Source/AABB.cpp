//#include "AABB.h"
//
//CAabb::CAabb()
//{
//	m_position = { 0.0f, 0.0f, 0.0f };
//	m_size = { 0.0f, 0.0f, 0.0f };
//}
//CAabb::~CAabb()
//{
//}
//
////��������
//bool CAabb::isIntersected(const D3DXVECTOR3 &a)
//{
//	float la = m_position.x - m_size.x;//left A
//	float ra = m_position.x + m_size.x;//right A
//	float lb = a.x - m_size.x;//left B;
//	float rb = a.x + m_size.x;//right B;
//	if ((la < rb) && (ra > lb))
//	{
//		float ta = m_position.y - m_size.y;//top A
//		float ba = m_position.y + m_size.y;//bottom A
//		float tb = a.y - m_size.y;//top B
//		float bb = a.y + m_size.y;//bottom B
//		if ((ta < bb) && (ba > tb))
//		{
//			return true;
//		}
//	}
//	return false;
//
//}
//
///*!
//*@brief	ID3DXMesh����AABB�̃T�C�Y���v�Z����֐��B
//*@param[in]	mesh		ID3DXMesh
//*@return	AABB�̃T�C�Y�B
//*/
////��ԏ��X,Y,Z���W�ƈ�ԉ���X,Y,Z���W�����闧���̂��쐬
//D3DXVECTOR3 CAabb::CalcAABBSizeFromMesh(LPD3DXMESH mesh)
//{
//
//	D3DXVECTOR3 min;
//	D3DXVECTOR3 max;
//	D3DXVECTOR3 size;
//	min.x = FLT_MAX;
//	min.y = FLT_MAX;
//	min.z = FLT_MAX;
//	max.x = -FLT_MAX;
//	max.y = -FLT_MAX;
//	max.z = -FLT_MAX;
//	LPDIRECT3DVERTEXBUFFER9 vb;
//	mesh->GetVertexBuffer(&vb);
//	D3DVERTEXBUFFER_DESC desc;
//	vb->GetDesc(&desc);
//	int stride = D3DXGetFVFVertexSize(desc.FVF);
//	char* pVB = NULL;
//	vb->Lock(0, desc.Size, (void**)&pVB, D3DLOCK_DISCARD);
//	int numVertex = desc.Size / stride;
//	for (int vertNo = 0; vertNo < numVertex; vertNo++) {
//		float* pVertexPos = (float*)(pVB);
//		min.x = min(min.x, pVertexPos[0]);
//		min.y = min(min.y, pVertexPos[1]);
//		min.z = min(min.z, pVertexPos[2]);
//		max.x = max(max.x, pVertexPos[0]);
//		max.y = max(max.y, pVertexPos[1]);
//		max.z = max(max.z, pVertexPos[2]);
//		pVB += stride;
//	}
//	vb->Unlock();
//	size = max - min;
//	return size;
//}