//パーティクルを発生させる
#pragma once
#include<iostream>
#include"..\DXCommon.h"
#include<list>
class CParticle;
class Ccamera;
class CRandom;

struct SParicleEmitParameter {
	//初期化。
	void Init()
	{
		memset(this, 0, sizeof(SParicleEmitParameter));
		initAlpha = 1.0f;
		brightness = 1.0f;
		isBillboard = true;
	}
	const char* texturePath;						//!<テクスチャのファイルパス。
	D3DXVECTOR3	initVelocity;						//!<初速度。
	float		life;								//!<寿命。単位は秒。
	float		intervalTime;						//!<発生時間。単位は秒。
	float		w;									//!<パーティクルの幅。
	float		h;									//!<パーティクルの高さ。
	D3DXVECTOR3	initPositionRandomMargin;			//!<初期位置のランダム幅。
	D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
	D3DXVECTOR3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
	D3DXVECTOR3	gravity;							//!<重力。
	bool		isFade;								//!<死ぬときにフェードアウトする？
	float		fadeTime;							//!<フェードする時間。
	float		initAlpha;							//!<初期アルファ値。
	bool		isBillboard;						//!<ビルボード？
	float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
	int			alphaBlendMode;						//!<0半透明合成、1加算合成。

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
	float					timer;			//!<タイマー
	CRandom*				random;			//!<乱数生成機。
	Ccamera*				camera;			//!<カメラ。
	SParicleEmitParameter	param;			//!<パラメータ。
	D3DXVECTOR3				emitPosition;	//!<エミッターの座標。
	std::list<CParticle*>	particleList;	//!<パーティクルのリスト。

	ID3DXBuffer* m_pMaterials;
	DWORD m_NumMaterials;
	ID3DXMesh* m_pMesh;
	IDirect3DTexture9* m_pTextures;
	ID3DXEffect* m_pEffect;
};