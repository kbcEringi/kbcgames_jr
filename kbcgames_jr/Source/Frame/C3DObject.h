#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>

class C3DObject;
/*
*エフェクト設定のコールバッククラス。
*/
class ISetEffectCallback{
public:
	ISetEffectCallback() 
	{
	}
	virtual ~ISetEffectCallback()
	{
	}
	void SetEffect(ID3DXEffect* effect)
	{
		m_pEffect = effect;
	}
public:
	virtual void OnBeginRender(C3DObject* p3dObject, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix) = 0;
	virtual void OnPreDrawSubset(C3DObject* p3dObject, int materialNo) = 0;
	virtual void OnEndRender(C3DObject*	m_p3dObject) = 0;
protected:
	ID3DXEffect*	m_pEffect;
};
/*
* Defaultのエフェクト設定コールバック。
*/
class CSetEffectCallbackDefault : public ISetEffectCallback{
public:
	CSetEffectCallbackDefault();
	~CSetEffectCallbackDefault();
	void OnBeginRender(C3DObject* p3dObject, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix) override;
	void OnPreDrawSubset(C3DObject* p3dObject, int materialNo) override;
	void OnEndRender(C3DObject*	m_p3dObject) override;
};

class CSetEffectCallbackShadowMap : public ISetEffectCallback{
public:
	CSetEffectCallbackShadowMap();
	~CSetEffectCallbackShadowMap();
	void OnBeginRender(C3DObject* p3dObject, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix) override;
	void OnPreDrawSubset(C3DObject* p3dObject, int materialNo) override;
	void OnEndRender(C3DObject*	m_p3dObject) override;
};
/*
* 3Dオブジェクト。
*/
class C3DObject
{
	friend class ISetEffectCallback;
	friend class CSetEffectCallbackDefault;
public:
	/*
	*第一引数　Xファイル名（例："XFile\\kyu.x"）
	*第二引数　グラフィックパス（デフォルト＝０、スペキュラ＝１）
	*/
	void Initialize(LPCSTR , int pass = 0);
	/*
	*第一引数　ワールドマトリクス（自分の位置）
	*第二引数　ビューマトリクス（カメラの位置）
	*/
	void Draw(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	ISetEffectCallback* GetEffectCallback()
	{
		return m_currentSetEffectCallback;
	}
	void SetEffectCallback(ISetEffectCallback* callback)
	{
		m_currentSetEffectCallback = callback;
	}
	ID3DXEffect* GetEffect()
	{
		return m_pEffect;
	}
	~C3DObject();
protected:
	LPD3DXBUFFER m_D3DXMtrlBuffer;	//マテリアル
	DWORD m_NumMaterials;		//マテリアル数
	LPD3DXMESH m_Mesh;			//メッシュ
	LPDIRECT3DTEXTURE9*  m_pMeshTextures;	//メッシュテクスチャ
	ID3DXEffect* m_pEffect;

	D3DXMATERIAL *materials;

	static const int LIGHT_NUM = 6;
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4	m_ambientLight;						//環境光

	int m_Graphicspass;
	CSetEffectCallbackDefault m_defaultSetEffectCallback;
	ISetEffectCallback* m_currentSetEffectCallback;
};