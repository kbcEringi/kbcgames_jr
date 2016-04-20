#pragma once

#include<d3dx9.h>

class CCamera
{
public:	
	CCamera();
	~CCamera();
	HRESULT Initialize();
	HRESULT Update();

	//============================================================
	//ビュー行列に関するメソッドです。
	//============================================================
	HRESULT SetView(D3DXVECTOR3 &eye, D3DXVECTOR3 &at, D3DXVECTOR3 &up);

	HRESULT SetDistance(float);
	HRESULT RotTransversal(float RotY);	//横回転
	HRESULT RotLongitudinal(float RotX); //縦回転

	HRESULT SerBase(D3DXVECTOR3);
	D3DXVECTOR3 GetVector(){ return m_Eye; }
	D3DXMATRIX GetView(){ return m_View; }
private:
	D3DXVECTOR3 m_Eye;	//カメラの位置
	D3DXVECTOR3 m_At;	//カメラの視点
	D3DXVECTOR3 m_Up;	//カメラの上方向
	
	D3DXVECTOR3 m_Base;	//カメラの位置
	D3DXVECTOR3 m_NormalizeObject;	//正規化された対象点
	D3DXVECTOR3 m_Object;	//対象点の位置

	float m_Distance;	//カメラの位置と視点の距離

	D3DXMATRIX m_View;	//ビュー行列
};