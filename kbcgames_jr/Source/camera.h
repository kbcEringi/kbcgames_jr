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
	//�r���[�s��Ɋւ��郁�\�b�h�ł��B
	//============================================================
	HRESULT SetView(D3DXVECTOR3 &eye, D3DXVECTOR3 &at, D3DXVECTOR3 &up);

	HRESULT SetDistance(float);
	HRESULT RotTransversal(float RotY);	//����]
	HRESULT RotLongitudinal(float RotX); //�c��]

	HRESULT SerBase(D3DXVECTOR3);
	D3DXVECTOR3 GetVector(){ return m_Eye; }
	D3DXMATRIX GetView(){ return m_View; }
private:
	D3DXVECTOR3 m_Eye;	//�J�����̈ʒu
	D3DXVECTOR3 m_At;	//�J�����̎��_
	D3DXVECTOR3 m_Up;	//�J�����̏����
	
	D3DXVECTOR3 m_Base;	//�J�����̈ʒu
	D3DXVECTOR3 m_NormalizeObject;	//���K�����ꂽ�Ώۓ_
	D3DXVECTOR3 m_Object;	//�Ώۓ_�̈ʒu

	float m_Distance;	//�J�����̈ʒu�Ǝ��_�̋���

	D3DXMATRIX m_View;	//�r���[�s��
};