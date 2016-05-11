#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\Frame\Input.h"//�L�[�{�[�h�C���v�b�g

class CPointa
{
public:
	CPointa();
	~CPointa();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Move();					//Move�֐�
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;
	BYTE diks[256];//�L�[�C���v�b�g
};