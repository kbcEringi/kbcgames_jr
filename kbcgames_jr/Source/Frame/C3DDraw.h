#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>



class C3DDraw;
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
public:
	virtual void OnBeginRender(C3DDraw* p3dDraw, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix) = 0;
	virtual void OnPreDrawSubset(C3DDraw* p3dDraw, int materialNo) = 0;
	virtual void OnEndRender(C3DDraw*	p3dDraw) = 0;
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
	void OnBeginRender(C3DDraw* p3dDraw, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix) override;
	void OnPreDrawSubset(C3DDraw* p3dDraw, int materialNo) override;
	void OnEndRender(C3DDraw*	p3dDraw) override;
};

class CSetEffectCallbackShadowMap : public ISetEffectCallback{
public:
	CSetEffectCallbackShadowMap();
	~CSetEffectCallbackShadowMap();
	void OnBeginRender(C3DDraw* p3dDraw, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix) override;
	void OnPreDrawSubset(C3DDraw* p3dDraw, int materialNo) override;
	void OnEndRender(C3DDraw*	p3dDraw) override;
};
/*
* 3Dオブジェクト。
*/
class C3DDraw
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
	~C3DDraw();
	//メッシュを取得。
	LPD3DXMESH GetMesh()
	{
		return m_Mesh;
	}
protected:
	LPD3DXBUFFER m_D3DXMtrlBuffer;	//マテリアル
	DWORD m_NumMaterials;		//マテリアル数
	LPD3DXMESH m_Mesh;			//メッシュ
	LPDIRECT3DTEXTURE9*  m_pMeshTextures;	//メッシュテクスチャ

	D3DXMATERIAL *materials;

	static const int LIGHT_NUM = 6;
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4	m_ambientLight;						//環境光

	int m_Graphicspass;
	CSetEffectCallbackDefault m_defaultSetEffectCallback;
	ISetEffectCallback* m_currentSetEffectCallback;
};