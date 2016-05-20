#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>
#include"SkinModelDate.h"



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
	virtual void OnBeginRender(D3DXVECTOR4*, D3DXVECTOR4*, D3DXVECTOR4,int) = 0;
	virtual void OnRenderAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, LPD3DXBONECOMBINATION, UINT) = 0;
	virtual void OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, D3DXMATRIX) = 0;
	virtual void OnEndRender() = 0;
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
	void OnBeginRender(D3DXVECTOR4*, D3DXVECTOR4*, D3DXVECTOR4,int);
	void OnRenderAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, LPD3DXBONECOMBINATION, UINT) override;
	void OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, D3DXMATRIX)override;
	void OnEndRender();
};

class CSetEffectCallbackShadowMap : public ISetEffectCallback{
public:
	CSetEffectCallbackShadowMap();
	~CSetEffectCallbackShadowMap();
	void OnBeginRender(D3DXVECTOR4*, D3DXVECTOR4*, D3DXVECTOR4,int);
	void OnRenderAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, LPD3DXBONECOMBINATION, UINT) override;
	void OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, D3DXMATRIX) override;
	void OnEndRender();
	void SetEffect(ID3DXEffect* effect)
	{
		m_pEffect = effect;
	}
private:
	ID3DXEffect* m_pEffect;
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
	C3DDraw();
	void Initialize(LPCSTR , int pass = 0);
	//アニメーションを進める。
	void AddAnimation();
	void UpdateWorldMatrix(D3DXMATRIX worldMatrix);
	/*
	*第一引数　ワールドマトリクス（自分の位置）
	*第二引数　ビューマトリクス（カメラの位置）
	*/
	void Draw(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	void DrawFrame(
		LPD3DXFRAME pFrame, D3DXMATRIX, D3DXMATRIX);

	void DrawMeshContainer(
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase, D3DXMATRIX, D3DXMATRIX
		);
	ISetEffectCallback* GetEffectCallback()
	{
		return m_currentSetEffectCallback;
	}
	void SetEffectCallback(ISetEffectCallback* callback)
	{
		m_currentSetEffectCallback = callback;
	}
	LPD3DXMESH GetMesh()
	{
		 return m_skinmodel->GetFrameRoot()->pMeshContainer->MeshData.pMesh;
	}
	/*void SetAnimation(int idx)
	{
		m_pAnimController->SetTrackAnimationSet(1, animationSet[idx]); 
	}*/
	~C3DDraw();
protected:
	CSkinModelData* m_skinmodel;
	//ID3DXAnimationController* m_pAnimController;
	//LPD3DXANIMATIONSET animationSet[100];


	static const int LIGHT_NUM = 6;
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4	m_ambientLight;						//環境光

	int m_Graphicspass;
	CSetEffectCallbackDefault m_defaultSetEffectCallback;
	ISetEffectCallback* m_currentSetEffectCallback;

	D3DXMATRIX m_matWorld;
};