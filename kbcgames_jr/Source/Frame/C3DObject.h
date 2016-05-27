#pragma once
/*
 *	全ての３Dオブジェクトの基底クラス
 */
#include"DXCommon.h"
#include"C3DDraw.h"

struct ObjectData
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
};

class C3DObject
{
public:
	C3DObject(){D3DXMatrixIdentity(&m_matWorld);}
	~C3DObject(){}
public:
	virtual void Initialize()=0;
	virtual void D2DUpdate()=0;
	virtual void D3DUpdate()=0;
	virtual void D2DDraw(D3DXMATRIX, D3DXMATRIX) = 0;
	virtual void D3DDraw(D3DXMATRIX, D3DXMATRIX) = 0;
	C3DDraw* GetSkinModel(){ return &m_SkinModel; }

	void SetObject2DData(ObjectData obj){ m_2Ddata = obj; }
	void SetObject3DData(ObjectData obj){ m_3Ddata = obj; }

protected:
	C3DDraw m_SkinModel;
	ObjectData m_2Ddata;
	ObjectData m_3Ddata;
	D3DXMATRIX m_matWorld;
};