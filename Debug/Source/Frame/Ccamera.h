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
	void RotTransversal(float RotY);	//����]
	void RotLongitudinal(float RotX); //�c��]
private:
	D3DXMATRIX		m_viewMatrix;			//�r���[�s��B
	D3DXMATRIX		m_projectionMatrix;		//�v���W�F�N�V�����s��B
	D3DXVECTOR3		m_vEyePt;				//�J�����̈ʒu�B
	D3DXVECTOR3		m_vLookatPt;			//�J�����̒����_�B
	D3DXVECTOR3		m_vUpVec;				//�J�����̏�����B
	float			m_Distance;				//�J�����̈ʒu�Ǝ��_�̋���
	D3DXVECTOR3 m_NormalizeObject;	//���K�����ꂽ�Ώۓ_

private://�ۑ�p�ϐ�
	float m_vFovy;		//��p
	float m_vAspect;	//�A�X�y�N�g��
	float m_vNear;		//�j�A
	float m_vFar;		//�t�@�[
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
//public://�ۑ�p�֐�
//	/*
//	*	��p�Z�b�g
//	*	������(float)�x���F45.0f
//	*/
//	void SetFovy(float fovy){ m_vFovy = D3DXToRadian(fovy); }
//	/*
//	*	�A�X�y�N�g��Z�b�g
//	*	������(float,float)�����F����,�c���F����
//	*/
//	void SetAspect(float Width, float Height){ m_vAspect = Width / Height; }
//	/*
//	*	�j�A���Z
//	*	������(float)
//	*/
//	void AddNear(float fnear){ m_vNear += fnear; }
//	/*
//	*	�t�@�[���Z
//	*	������(float)
//	*/
//	void AddFar(float ffar){ m_vFar += ffar; }
//private:
//	D3DXMATRIX		m_viewMatrix;			//�r���[�s��B
//	D3DXMATRIX		m_projectionMatrix;		//�v���W�F�N�V�����s��B
//	D3DXVECTOR3		m_vEyePt;				//�J�����̎��_�B
//	D3DXVECTOR3		m_vLookatPt;			//�J�����̒����_�B
//	D3DXVECTOR3		m_vUpVec;				//�J�����̏�����B
//private://�ۑ�p�ϐ�
//	float m_vFovy;		//��p
//	float m_vAspect;	//�A�X�y�N�g��
//	float m_vNear;		//�j�A
//	float m_vFar;		//�t�@�[
//};
