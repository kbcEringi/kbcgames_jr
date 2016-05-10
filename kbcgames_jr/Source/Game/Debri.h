#pragma once
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"


class CDebri{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	virtual void OnDestroy();
	/*!
	*@brief	�\�z�����B
	*@param[in]	size	���̃T�C�Y�B
	*@param[in]	pos		���̍��W�B
	*/
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	D3DXVECTOR3 size;
	CRigidbody m_Rigidbody;
};