#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>
#include"SkinModelDate.h"
#include"CAnimation.h"
#include"CLight.h"
#include<map>

class C3DDraw;

struct Renderstate
{
	bool isLuminance;
	bool shadowflg;
	bool hureneruflg;
	bool unitychanflg;
	float Luminance;
	IDirect3DTexture9* normal;
	Renderstate()
	{
		isLuminance = false;
		shadowflg = true;
		hureneruflg = false;
		unitychanflg = false;
		Luminance = 0.0f;
		normal = nullptr;
	}
};

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
	virtual void OnBeginRender(CLight,int) = 0;
	virtual void OnRenderAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, LPD3DXBONECOMBINATION, UINT, D3DXMATRIX,  Renderstate) = 0;
	virtual void OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,  Renderstate) = 0;
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
	void OnBeginRender(CLight, int);
	void OnRenderAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, LPD3DXBONECOMBINATION, UINT, D3DXMATRIX,  Renderstate) override;
	void OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,  Renderstate)override;
	void OnEndRender();
};

class CSetEffectCallbackShadowMap : public ISetEffectCallback{
public:
	CSetEffectCallbackShadowMap();
	~CSetEffectCallbackShadowMap();
	void OnBeginRender(CLight, int);
	void OnRenderAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, LPD3DXBONECOMBINATION, UINT, D3DXMATRIX,  Renderstate) override;
	void OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,  Renderstate) override;
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
	void Initialize(LPCSTR);
	//アニメーションを進める。
	void AddAnimation();
	void UpdateWorldMatrix(D3DXMATRIX worldMatrix);
	/*
	*第一引数　ワールドマトリクス（自分の位置）
	*第二引数　ビューマトリクス（カメラの位置）
	*第三引数　プロジェクションマトリクス
	*第四引数　ローテーションマトリクス
	*/
	void Draw(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,D3DXMATRIX);
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
	void SetAnimation(int idx)
	{
		idx %= m_animation.GetNumAnimationSet();
		m_animation.PlayAnimation(idx, 0.1f);
	}
	void SetAnimationEndTime(int idx,float time)
	{
		idx %= m_animation.GetNumAnimationSet();
		m_animation.SetAnimationEndTime(idx, time);
	}
	void Setshadowflg(bool flg){ rens.shadowflg = flg; }
	void Sethureneruflg(bool flg){ rens.hureneruflg = flg; }
	CLight* GetLight(){ return &m_light; }
	void Setunitychanflg(){ rens.unitychanflg = true; }
	void SetLuminance(bool is, float lum = 0){ rens.isLuminance = is; rens.Luminance = lum; }
	//ディフューズテクスチャパス、ノーマルマップパス
	void SetNormalMap(LPCSTR);
	void Release()
	{
		if (m_skinmodel)
		{
			delete m_skinmodel;
			m_skinmodel = NULL;
		}
	}
	~C3DDraw();
protected:
	CSkinModelData* m_skinmodel;
	CAnimation m_animation;
	CLight m_light;
	int m_Graphicspass;
	CSetEffectCallbackDefault m_defaultSetEffectCallback;
	ISetEffectCallback* m_currentSetEffectCallback;

	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matRot;

	Renderstate rens;

};