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

	//滑らかに移動させるのと
	//直前の３Ｄ座標を記憶させる
	void Set2Dflg(bool flg){
		if (flg && !m_2Dflg)
		{
			m_v3DNormal = m_NormalizeObject;
			m_NormalizeObject.x = 0;
			m_NormalizeObject.y = 0;
			m_NormalizeObject.z = -1;
			//D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
			D3DXMatrixOrthoLH(&m_projectionMatrix, m_viewVolumeW, m_viewVolumeH, m_vNear, m_vFar);
		}
		else if (!flg && m_2Dflg)
		{
			m_NormalizeObject = m_v3DNormal;
			m_Distance = 15;
			//D3DXMatrixOrthoLH(&m_projectionMatrix, m_viewVolumeW, m_viewVolumeH, m_vNear, m_vFar);
			D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
		}
		m_2Dflg = flg;
	}
	bool Get2Dflg(){ return m_2Dflg; }

private:
	D3DXMATRIX		m_viewMatrix;			//ビュー行列。
	D3DXMATRIX		m_projectionMatrix;		//プロジェクション行列。
	D3DXVECTOR3		m_vEyePt;				//カメラの位置。
	D3DXVECTOR3		m_vLookatPt;			//カメラの注視点。
	D3DXVECTOR3		m_vUpVec;				//カメラの上方向。
	float			m_Distance;				//カメラの位置と視点の距離
	D3DXVECTOR3 m_NormalizeObject;	//正規化された対象点

	D3DXVECTOR3 m_v3DNormal;

	bool m_2Dflg;
	float m_viewVolumeW;							//!<ビューボリュームの幅(2Dカメラの時だけ有効。)
	float m_viewVolumeH;							//!<ビューボリュームの高さ(2Dカメラの時だけ有効。)
	float Volume;
private://課題用変数
	float m_vFovy;		//画角
	float m_vAspect;	//アスペクト比
	float m_vNear;		//ニア
	float m_vFar;		//ファー
};
