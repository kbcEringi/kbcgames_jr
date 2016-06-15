//�p�[�e�B�N���𔭐�������
#pragma once
#include<iostream>
#include"..\DXCommon.h"
#include<list>
class CParticle;
class Ccamera;
class CRandom;

struct SParicleEmitParameter {
	//�������B
	void Init()
	{
		memset(this, 0, sizeof(SParicleEmitParameter));
		initAlpha = 1.0f;
		brightness = 1.0f;
		isBillboard = true;
	}
	const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
	D3DXVECTOR3	initVelocity;						//!<�����x�B
	float		life;								//!<�����B�P�ʂ͕b�B
	float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
	float		w;									//!<�p�[�e�B�N���̕��B
	float		h;									//!<�p�[�e�B�N���̍����B
	D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
	D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
	D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
	D3DXVECTOR3	gravity;							//!<�d�́B
	bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
	float		initAlpha;							//!<�����A���t�@�l�B
	bool		isBillboard;						//!<�r���{�[�h�H
	float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	int			alphaBlendMode;						//!<0�����������A1���Z�����B

};

class CParticleEmitter
{
public:
	CParticleEmitter(){}
	~CParticleEmitter(){ Release(); }
	void Init(CRandom& random, Ccamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition);
	void Update();
	void Render();
	void ApplyForce(const D3DXVECTOR3& applyForce);
	void Release()
	{
		std::list<CParticle*>::iterator p = particleList.begin();
		while (p != particleList.end()){
			p = particleList.erase(p);
		}
		particleList.clear();
		if (m_pMaterials != NULL)
		{
			m_pMaterials->Release();
			m_pMaterials = NULL;
		}
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}
		if (m_pTextures != NULL)
		{
			m_pTextures->Release();
			m_pTextures = NULL;
		}
		if (m_pEffect != NULL)
		{
			m_pEffect->Release();
			m_pEffect = NULL;
		}
	}
private:
	float					timer;			//!<�^�C�}�[
	CRandom*				random;			//!<���������@�B
	Ccamera*				camera;			//!<�J�����B
	SParicleEmitParameter	param;			//!<�p�����[�^�B
	D3DXVECTOR3				emitPosition;	//!<�G�~�b�^�[�̍��W�B
	std::list<CParticle*>	particleList;	//!<�p�[�e�B�N���̃��X�g�B

	ID3DXBuffer* m_pMaterials;
	DWORD m_NumMaterials;
	ID3DXMesh* m_pMesh;
	IDirect3DTexture9* m_pTextures;
	ID3DXEffect* m_pEffect;

	
};