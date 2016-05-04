#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>

class C3DObject;
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
* Default�̃G�t�F�N�g�ݒ�R�[���o�b�N�B
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
* 3D�I�u�W�F�N�g�B
*/
class C3DObject
{
	friend class ISetEffectCallback;
	friend class CSetEffectCallbackDefault;
public:
	/*
	*�������@X�t�@�C�����i��F"XFile\\kyu.x"�j
	*�������@�O���t�B�b�N�p�X�i�f�t�H���g���O�A�X�y�L�������P�j
	*/
	void Initialize(LPCSTR , int pass = 0);
	/*
	*�������@���[���h�}�g���N�X�i�����̈ʒu�j
	*�������@�r���[�}�g���N�X�i�J�����̈ʒu�j
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
	LPD3DXBUFFER m_D3DXMtrlBuffer;	//�}�e���A��
	DWORD m_NumMaterials;		//�}�e���A����
	LPD3DXMESH m_Mesh;			//���b�V��
	LPDIRECT3DTEXTURE9*  m_pMeshTextures;	//���b�V���e�N�X�`��
	ID3DXEffect* m_pEffect;

	D3DXMATERIAL *materials;

	static const int LIGHT_NUM = 6;
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4	m_ambientLight;						//����

	int m_Graphicspass;
	CSetEffectCallbackDefault m_defaultSetEffectCallback;
	ISetEffectCallback* m_currentSetEffectCallback;
};