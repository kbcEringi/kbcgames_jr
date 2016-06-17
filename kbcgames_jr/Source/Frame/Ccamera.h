#pragma once

#include"DXCommon.h"
#include"..\Game\CGameFlg.h"
#include"CGamepad.h"

#define DEFAULT_VOLUME 10.0f
#define TARGET_VOLUME 30.0f

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
	D3DXMATRIX GetRotationMatrix(){ return m_RotationMatrix; }
	D3DXMATRIX GetInveMatrix(){ return m_viewMatrixRotInv; }
	void AddLookat(D3DXVECTOR3 vec){ m_vLookatPt += vec; }
	void SetLookat(D3DXVECTOR3 vec){ m_vLookatPt = vec; }
	void SetEyePt(D3DXVECTOR3 vec){ m_vEyePt = vec; }
	void RotTransversal(float RotY);	//横回転
	void RotLongitudinal(float RotX); //縦回転
	void AddDistance(float add){ m_Distance += add; }
	//滑らかに移動させるのと
	//直前の３Ｄ座標を記憶させる
	void Set2DProj(){
		if (flg == false)
		{
			m_v3DNormal = m_NormalizeObject;
			m_NormalizeObject.x = 0;
			m_NormalizeObject.y = 0;
			m_NormalizeObject.z = -1;
			//D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
			D3DXMatrixOrthoLH(&m_projectionMatrix, m_viewVolumeW, m_viewVolumeH, m_vNear, m_vFar);
			flg = true;
		}
	}
	void Set3DProj(){
		if (flg == true)
		{
			m_NormalizeObject = m_v3DNormal;
			m_Distance = 10;
			//D3DXMatrixOrthoLH(&m_projectionMatrix, m_viewVolumeW, m_viewVolumeH, m_vNear, m_vFar);
			D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
			flg = false;
		}
	}
	//ニアーを取得。
	float GetNear()
	{
		return m_vNear;
	}
	//ファーを取得。
	float GetFar()
	{
		return m_vFar;
	}
	void TargetVolume();
	void SetTarget(float target)
	{
		targetVolume = target;
	}
	void SetDistance(float distance)
	{
		m_Distance = distance;
	}
	void SetNear(float Near)
	{
		m_vNear = Near;
	}
	//タイトルシーン以外で使わない！！！バグが出ても知らないよ！
	void UpdateProjectionMatrix()
	{
		D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
	}
private:
	D3DXMATRIX		m_viewMatrix;			//ビュー行列。
	D3DXMATRIX		m_projectionMatrix;		//プロジェクション行列。
	D3DXMATRIX		m_RotationMatrix;		//回転行列
	D3DXMATRIX m_viewMatrixRotInv;			//回転行列の逆行列。
	D3DXVECTOR3		m_vEyePt;				//カメラの位置。
	D3DXVECTOR3		m_vLookatPt;			//カメラの注視点。
	D3DXVECTOR3		m_vUpVec;				//カメラの上方向。
	float			m_Distance;				//カメラの位置と視点の距離
	D3DXVECTOR3 m_NormalizeObject;	//正規化された対象点

	D3DXVECTOR3 m_v3DNormal;

	bool flg;
	float m_viewVolumeW;							//!<ビューボリュームの幅(2Dカメラの時だけ有効。)
	float m_viewVolumeH;							//!<ビューボリュームの高さ(2Dカメラの時だけ有効。)
	float Volume;
	float targetVolume;//Bが押された場合の大きさ
private://課題用変数
	float m_vFovy;		//画角
	float m_vAspect;	//アスペクト比
	float m_vNear;		//ニア
	float m_vFar;		//ファー
};
