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
	~CParticleEmitter(){}
	void Init(CRandom& random, Ccamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition);
	void Update();
	void Render();
	void ApplyForce(const D3DXVECTOR3& applyForce);
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

//SParicleEmitParameter particleParameterTbl[] =
//{
//	{
//		"Texture\\leaf.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
//		D3DXVECTOR3(1.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
//		5.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
//		0.01f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
//		1.0f,							//float		w;									//!<�p�[�e�B�N���̕��B
//		1.0f,							//float		h;									//!<�p�[�e�B�N���̍����B
//		D3DXVECTOR3(0.0f, 10.0f, 10.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
//		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
//		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
//		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
//		1.0f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
//		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
//		true,							//bool		isBillboard;						//!<�r���{�[�h�H
//		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
//		0,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
//	},
//	{
//		"Texture\\hi.jpg",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
//		D3DXVECTOR3(0.0f, 1.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
//		3.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
//		0.1f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
//		0.5f,							//float		w;									//!<�p�[�e�B�N���̕��B
//		0.5f,							//float		h;									//!<�p�[�e�B�N���̍����B
//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
//		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
//		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
//		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
//		3.0f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
//		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
//		true,							//bool		isBillboard;						//!<�r���{�[�h�H
//		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
//		1,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
//	},
//	{
//		"Texture\\PRT_Fire.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
//		D3DXVECTOR3(0.0f, 1.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
//		2.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
//		0.1f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
//		1.0f,							//float		w;									//!<�p�[�e�B�N���̕��B
//		1.0f,							//float		h;									//!<�p�[�e�B�N���̍����B
//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
//		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
//		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
//		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
//		3.0f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
//		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
//		true,							//bool		isBillboard;						//!<�r���{�[�h�H
//		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
//		1,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
//	},
//};