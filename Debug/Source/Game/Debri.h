#pragma once
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"


class CDebri : public C3DObject
{
public:
	CDebri() : C3DObject(){}
	void Initialize();
	void D2DUpdate(){}
	void D3DUpdate();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	void OnDestroy();
	/*!
	*@brief	�\�z�����B
	*@param[in]	size	���̃T�C�Y�B
	*@param[in]	pos		���̍��W�B
	*/
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	
private:
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	D3DXVECTOR3 size;
	CRigidbody m_Rigidbody;
};