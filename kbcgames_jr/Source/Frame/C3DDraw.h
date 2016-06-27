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
*�G�t�F�N�g�ݒ�̃R�[���o�b�N�N���X�B
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
* Default�̃G�t�F�N�g�ݒ�R�[���o�b�N�B
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
* 3D�I�u�W�F�N�g�B
*/
class C3DDraw
{
	friend class ISetEffectCallback;
	friend class CSetEffectCallbackDefault;
public:
	/*
	*�������@X�t�@�C�����i��F"XFile\\kyu.x"�j
	*�������@�O���t�B�b�N�p�X�i�f�t�H���g���O�A�X�y�L�������P�j
	*/
	C3DDraw();
	void Initialize(LPCSTR);
	//�A�j���[�V������i�߂�B
	void AddAnimation();
	void UpdateWorldMatrix(D3DXMATRIX worldMatrix);
	/*
	*�������@���[���h�}�g���N�X�i�����̈ʒu�j
	*�������@�r���[�}�g���N�X�i�J�����̈ʒu�j
	*��O�����@�v���W�F�N�V�����}�g���N�X
	*��l�����@���[�e�[�V�����}�g���N�X
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
	//�f�B�t���[�Y�e�N�X�`���p�X�A�m�[�}���}�b�v�p�X
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