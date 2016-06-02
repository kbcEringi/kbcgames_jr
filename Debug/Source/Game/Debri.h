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
	*@brief	構築処理。
	*@param[in]	size	箱のサイズ。
	*@param[in]	pos		箱の座標。
	*/
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	
private:
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	D3DXVECTOR3 size;
	CRigidbody m_Rigidbody;
};