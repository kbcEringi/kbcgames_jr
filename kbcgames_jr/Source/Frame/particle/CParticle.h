//パーティクル本体
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
	//乱数、カメラ、パーティクル値、ポジション
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
	CRandom* random;	//乱数
	float			life;						//!<ライフ。
	float			timer;						//!<タイマー。
	D3DXVECTOR3		velocity;					//!<速度。
	D3DXVECTOR3		position;					//!<座標。
	D3DXVECTOR3		gravity;					//!<重力。
	float			rotateZ;					//!<Z軸周りの回転。
	D3DXMATRIX			mWorld;						//!<ワールド行列。
	D3DXVECTOR3		addVelocityRandomMargih;	//!<速度の積分のときのランダム幅。
	bool			isDead;						//!<死亡フラグ。
	bool			isFade;						//!<死ぬときにフェードアウトする？
	float			fadeTIme;					//!<フェードの時間。
	eState			state;						//!<状態。
	float			initAlpha;					//!<初期アルファ。
	float			alpha;						//!<アルファ。
	bool			isBillboard;				//!<ビルボード？
	D3DXVECTOR3		applyForce;					//!<外部から加わる力。
	float			brightness;					//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
	int				alphaBlendMode;				//!<0半透明合成、1加算合成。
	
};

//まずは一枚描画