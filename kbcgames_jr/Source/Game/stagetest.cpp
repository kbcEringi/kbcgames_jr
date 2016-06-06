#include "stagetest.h"
#include<time.h>

SParicleEmitParameter particleParameterTbl[] =
{
	{
		"Texture\\leaf.png",	//const char* texturePath;						//!<テクスチャのファイルパス。
		D3DXVECTOR3(1.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<初速度。
		5.0f,							//float		life;								//!<寿命。単位は秒。
		0.01f,							//float		intervalTime;						//!<発生時間。単位は秒。
		1.0f,							//float		w;									//!<パーティクルの幅。
		1.0f,							//float		h;									//!<パーティクルの高さ。
		D3DXVECTOR3(0.0f, 10.0f, 10.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<重力。
		true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
		1.0f,							//float		fadeTime;							//!<フェードする時間。
		1.0f,							//float		initAlpha;							//!<初期アルファ値。
		true,							//bool		isBillboard;						//!<ビルボード？
		2.0f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		0,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
	},
	{
		"Texture\\PRT_Fire.png",	//const char* texturePath;						//!<テクスチャのファイルパス。
		D3DXVECTOR3(0.0f, 1.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<初速度。
		2.0f,							//float		life;								//!<寿命。単位は秒。
		0.0001f,							//float		intervalTime;						//!<発生時間。単位は秒。
		1.0f,							//float		w;									//!<パーティクルの幅。
		1.0f,							//float		h;									//!<パーティクルの高さ。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<重力。
		true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
		1.0f,							//float		fadeTime;							//!<フェードする時間。
		1.0f,							//float		initAlpha;							//!<初期アルファ値。
		true,							//bool		isBillboard;						//!<ビルボード？
		2.0f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
	},
};


void CStagetest::Initialize()
{
	m_camera.Initialize();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));
	random.Init((unsigned long)time);

	emi.Init(random, m_camera, particleParameterTbl[1], D3DXVECTOR3(0, 0, 0));
	wood.Initialize();

}

void CStagetest::Update()
{

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_camera.RotTransversal(-0.05f);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_camera.RotTransversal(0.05f);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_camera.RotLongitudinal(0.05f);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_camera.RotLongitudinal(-0.05f);
	}
	if (GetAsyncKeyState(VK_Z) & 0x8000)
	{
		m_camera.AddDistance(5);
	}
	if (GetAsyncKeyState(VK_X) & 0x8000)
	{
		m_camera.AddDistance(-5);
	}

	m_camera.SetLookat(D3DXVECTOR3(0,0,0));//Playerを追いかけるカメラ
	m_camera.Update();

	emi.Update();

	if (GetAsyncKeyState(VK_C) & 0x8000)
	emi.ApplyForce(D3DXVECTOR3(1,0,0));
	//pa.Update(m_camera.GetRotationMatrix());
	wood.Update();

}

void CStagetest::Draw()
{
	emi.Render();
	//pa.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	wood.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

}