#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>
#include"SkinModelDate.h"



class C3DDraw;
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
	virtual void OnBeginRender(D3DXVECTOR4*, D3DXVECTOR4*, D3DXVECTOR4,int) = 0;
	virtual void OnRenderAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, LPD3DXBONECOMBINATION, UINT) = 0;
	virtual void OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED*, D3DXMATRIX, D3DXMATRIX) = 0;
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
	void Initialize(LPCSTR , int pass = 0);
	//�A�j���[�V������i�߂�B
	void AddAnimation();
	void UpdateWorldMatrix(D3DXMATRIX worldMatrix);
	/*
	*�������@���[���h�}�g���N�X�i�����̈ʒu�j
	*�������@�r���[�}�g���N�X�i�J�����̈ʒu�j
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
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4	m_ambientLight;						//����

	int m_Graphicspass;
	CSetEffectCallbackDefault m_defaultSetEffectCallback;
	ISetEffectCallback* m_currentSetEffectCallback;

	D3DXMATRIX m_matWorld;
};