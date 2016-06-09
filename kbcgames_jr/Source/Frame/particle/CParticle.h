//�p�[�e�B�N���{��
#pragma once

#include"../DXCommon.h"
#include"..\CRandom.h"
#include"..\Ccamera.h"
class CRandom;
class Ccamera;
struct SParicleEmitParameter;

#define PI 3.14159265358979323846f

class CParticle
{
	enum eState {
		eStateRun,
		eStateFadeOut,
		eStateDead,
	};
public:
	CParticle();
	~CParticle();
	//�����A�J�����A�p�[�e�B�N���l�A�|�W�V����
	void Init(CRandom& random, Ccamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3 emitPosition);
	void Update();
	void Draw(DWORD m_NumMaterials,
		ID3DXMesh* m_pMesh,
		IDirect3DTexture9* m_pTextures,
		ID3DXEffect* m_pEffect);
	void ApplyForce(const D3DXVECTOR3 applyForce)
	{
		this->applyForce = applyForce;
	}
	bool GetDead(){ return isDead; }
private:

	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 scale;
	D3DXMATRIX matscale;
	Ccamera* camera;
	CRandom* random;	//����
	float			life;						//!<���C�t�B
	float			timer;						//!<�^�C�}�[�B
	D3DXVECTOR3		velocity;					//!<���x�B
	D3DXVECTOR3		position;					//!<���W�B
	D3DXVECTOR3		gravity;					//!<�d�́B
	float			rotateZ;					//!<Z������̉�]�B
	D3DXMATRIX			mWorld;						//!<���[���h�s��B
	D3DXVECTOR3		addVelocityRandomMargih;	//!<���x�̐ϕ��̂Ƃ��̃����_�����B
	bool			isDead;						//!<���S�t���O�B
	bool			isFade;						//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	float			fadeTIme;					//!<�t�F�[�h�̎��ԁB
	eState			state;						//!<��ԁB
	float			initAlpha;					//!<�����A���t�@�B
	float			alpha;						//!<�A���t�@�B
	bool			isBillboard;				//!<�r���{�[�h�H
	D3DXVECTOR3		applyForce;					//!<�O����������́B
	float			brightness;					//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
	int				alphaBlendMode;				//!<0�����������A1���Z�����B
	
};

//�܂��͈ꖇ�`��