#include "stagetest.h"
#include<time.h>

SParicleEmitParameter particleParameterTbl[] =
{
	{
		"Texture\\leaf.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		D3DXVECTOR3(1.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
		5.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
		0.01f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		1.0f,							//float		w;									//!<�p�[�e�B�N���̕��B
		1.0f,							//float		h;									//!<�p�[�e�B�N���̍����B
		D3DXVECTOR3(0.0f, 10.0f, 10.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		1.0f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		0,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	},
	{
		"Texture\\hi.jpg",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		D3DXVECTOR3(0.0f, 1.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
		3.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
		0.1f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		0.5f,							//float		w;									//!<�p�[�e�B�N���̕��B
		0.5f,							//float		h;									//!<�p�[�e�B�N���̍����B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		3.0f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	}, 
	{
		"Texture\\PRT_Fire.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		D3DXVECTOR3(0.0f, 1.0f, 0.0f),		//D3DXVECTOR3	initVelocity;						//!<�����x�B
		2.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
		0.001f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		1.0f,							//float		w;									//!<�p�[�e�B�N���̕��B
		1.0f,							//float		h;									//!<�p�[�e�B�N���̍����B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		D3DXVECTOR3(0.3f, 0.0f, 0.3f),		//D3DXVECTOR3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		D3DXVECTOR3(0.005f, 0.0f, 0.005f),	//D3DXVECTOR3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//D3DXVECTOR3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		3.0f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		12.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	},
};


void CStagetest::Initialize()
{
	m_camera.Initialize();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));
	random.Init((unsigned long)time);


	emi.Init(random, m_camera, particleParameterTbl[2], D3DXVECTOR3(0, 0, 0));
	//emi2.Init(random, m_camera, particleParameterTbl[2], D3DXVECTOR3(0, 0, 0));

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
		m_camera.AddDistance(1);
	}
	if (GetAsyncKeyState(VK_X) & 0x8000)
	{
		m_camera.AddDistance(-1);
	}
	if (GetAsyncKeyState(VK_Q) & 0x8000)
	{
		particleParameterTbl[2].brightness++;
	}
	if (GetAsyncKeyState(VK_W) & 0x8000)
	{
		particleParameterTbl[2].brightness--;
	}
	m_camera.SetLookat(D3DXVECTOR3(0,0,0));//Player��ǂ�������J����
	m_camera.Update();


	emi.Update();
	//emi2.Update();

	if (GetAsyncKeyState(VK_C) & 0x8000){
		//.ApplyForce(D3DXVECTOR3(0.5, 0, 0));
		//emi2.ApplyForce(D3DXVECTOR3(0.5, 0, 0));
	}
	//pa.Update(m_camera.GetRotationMatrix());


	//if (GetAsyncKeyState(VK_C) & 0x8000){
	//	emi.ApplyForce(D3DXVECTOR3(0, 0, 10));
	//}

	wood.Update();

}

void CStagetest::Draw()
{

	emi.Render();
	//emi2.Render();
	//pa.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

	wood.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

}