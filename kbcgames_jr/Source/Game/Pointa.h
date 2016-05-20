#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include"..\Frame\Input.h"//�L�[�{�[�h�C���v�b�g

class CPointa
{
public:
	CPointa();
	~CPointa();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	void SetPos(D3DXVECTOR3 pos)
	{
		m_position = pos;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	BYTE diks[256];//�L�[�C���v�b�g
};