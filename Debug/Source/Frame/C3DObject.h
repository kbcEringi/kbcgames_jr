#pragma once
/*
 *	全ての３Dオブジェクトの基底クラス
 */
#include"DXCommon.h"
#include"C3DDraw.h"

class C3DObject
{
public:
	C3DObject(){D3DXMatrixIdentity(&m_matWorld);}
	~C3DObject(){}
public:
	virtual void Initialize()=0;
	virtual void D2DUpdate()=0;
	virtual void D3DUpdate()=0;
	virtual void Draw(D3DXMATRIX, D3DXMATRIX)=0;
	C3DDraw* GetSkinModel(){ return &m_SkinModel; }
protected:
	C3DDraw m_SkinModel;
	D3DXMATRIX m_matWorld;
};