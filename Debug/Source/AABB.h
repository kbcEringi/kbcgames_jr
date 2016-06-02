#pragma once
#include"..\Frame\C3DDraw.h"

class CAabb
{
public:
	CAabb();
	~CAabb();
	bool isIntersected(const D3DXVECTOR3& a);
	D3DXVECTOR3 CalcAABBSizeFromMesh(LPD3DXMESH mesh);
	void SetPosition(D3DXVECTOR3 pos){ m_position = pos; }
	void SetSize(D3DXVECTOR3 size){ m_size = size; }

private:
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_position;
};