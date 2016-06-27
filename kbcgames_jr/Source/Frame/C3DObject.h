#pragma once
/*
 *	全ての３Dオブジェクトの基底クラス
 */
#include"DXCommon.h"
#include"C3DDraw.h"


struct ObjectData
{
	D3DXVECTOR3 position;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 PlayerParameter;
};

class C3DObject
{
public:
	C3DObject(){ D3DXMatrixIdentity(&m_matWorld); D3DXMatrixIdentity(&m_matRot); }
	virtual ~C3DObject(){ Release(); }
public:
	virtual void Initialize()=0;
	virtual void Update()=0;
	virtual void Draw(D3DXMATRIX, D3DXMATRIX) = 0;
	C3DDraw* GetSkinModel(){ return &m_SkinModel; }
	void SetObjectData(ObjectData obj){ m_data = obj; }
	void Release()
	{
		m_SkinModel.Release();
	}
protected:
	C3DDraw m_SkinModel;
	ObjectData m_data;
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matRot;
};