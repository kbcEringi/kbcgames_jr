#pragma once

#include"DXCommon.h"

class Ccamera
{
public:
	Ccamera()
	{
		D3DXMatrixIdentity(&m_viewMatrix);
		D3DXMatrixIdentity(&m_projectionMatrix);
	}
	void Initialize();
	void Update();
	D3DXMATRIX GetViewMatrix(){ return m_viewMatrix; }
	D3DXMATRIX GetProjectionMatrix(){ return m_projectionMatrix; }
	void AddLookat(D3DXVECTOR3 vec){ m_vLookatPt += vec; }
	void SetLookat(D3DXVECTOR3 vec){ m_vLookatPt = vec; }
	void SetEyePt(D3DXVECTOR3 vec){ m_vEyePt = vec; }
	void RotTransversal(float RotY);	//横回転
	void RotLongitudinal(float RotX); //縦回転
private:
	D3DXMATRIX		m_viewMatrix;			//ビュー行列。
	D3DXMATRIX		m_projectionMatrix;		//プロジェクション行列。
	D3DXVECTOR3		m_vEyePt;				//カメラの位置。
	D3DXVECTOR3		m_vLookatPt;			//カメラの注視点。
	D3DXVECTOR3		m_vUpVec;				//カメラの上方向。
	float			m_Distance;				//カメラの位置と視点の距離
	D3DXVECTOR3 m_NormalizeObject;	//正規化された対象点

private://課題用変数
	float m_vFovy;		//画角
	float m_vAspect;	//アスペクト比
	float m_vNear;		//ニア
	float m_vFar;		//ファー
};


//class Ccamera
//{
//public:
//	Ccamera()
//	{
//		m_vEyePt = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		m_vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		D3DXMatrixIdentity(&m_viewMatrix);
//		D3DXMatrixIdentity(&m_projectionMatrix);
//	}
//	void Initialize();
//	void Update();
//	D3DXMATRIX GetViewMatrix(){ return m_viewMatrix; }
//	D3DXMATRIX GetProjectionMatrix(){ return m_projectionMatrix; }
//	void AddEye(D3DXVECTOR3 vec){ m_vEyePt += vec; }
//	void AddLookat(D3DXVECTOR3 vec){ m_vLookatPt += vec; }
//public://課題用関数
//	/*
//	*	画角セット
//	*	第一引数(float)度数：45.0f
//	*/
//	void SetFovy(float fovy){ m_vFovy = D3DXToRadian(fovy); }
//	/*
//	*	アスペクト比セット
//	*	第一引数(float,float)横幅：ｘ軸,縦幅：ｙ軸
//	*/
//	void SetAspect(float Width, float Height){ m_vAspect = Width / Height; }
//	/*
//	*	ニア加算
//	*	第一引数(float)
//	*/
//	void AddNear(float fnear){ m_vNear += fnear; }
//	/*
//	*	ファー加算
//	*	第一引数(float)
//	*/
//	void AddFar(float ffar){ m_vFar += ffar; }
//private:
//	D3DXMATRIX		m_viewMatrix;			//ビュー行列。
//	D3DXMATRIX		m_projectionMatrix;		//プロジェクション行列。
//	D3DXVECTOR3		m_vEyePt;				//カメラの視点。
//	D3DXVECTOR3		m_vLookatPt;			//カメラの注視点。
//	D3DXVECTOR3		m_vUpVec;				//カメラの上方向。
//private://課題用変数
//	float m_vFovy;		//画角
//	float m_vAspect;	//アスペクト比
//	float m_vNear;		//ニア
//	float m_vFar;		//ファー
//};
