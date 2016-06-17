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
	void RotTransversal(float RotY);	//����]
	void RotLongitudinal(float RotX); //�c��]
	void AddDistance(float add){ m_Distance += add; }
	//���炩�Ɉړ�������̂�
	//���O�̂R�c���W���L��������
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
	//�j�A�[���擾�B
	float GetNear()
	{
		return m_vNear;
	}
	//�t�@�[���擾�B
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
	//�^�C�g���V�[���ȊO�Ŏg��Ȃ��I�I�I�o�O���o�Ă��m��Ȃ���I
	void UpdateProjectionMatrix()
	{
		D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
	}
private:
	D3DXMATRIX		m_viewMatrix;			//�r���[�s��B
	D3DXMATRIX		m_projectionMatrix;		//�v���W�F�N�V�����s��B
	D3DXMATRIX		m_RotationMatrix;		//��]�s��
	D3DXMATRIX m_viewMatrixRotInv;			//��]�s��̋t�s��B
	D3DXVECTOR3		m_vEyePt;				//�J�����̈ʒu�B
	D3DXVECTOR3		m_vLookatPt;			//�J�����̒����_�B
	D3DXVECTOR3		m_vUpVec;				//�J�����̏�����B
	float			m_Distance;				//�J�����̈ʒu�Ǝ��_�̋���
	D3DXVECTOR3 m_NormalizeObject;	//���K�����ꂽ�Ώۓ_

	D3DXVECTOR3 m_v3DNormal;

	bool flg;
	float m_viewVolumeW;							//!<�r���[�{�����[���̕�(2D�J�����̎������L���B)
	float m_viewVolumeH;							//!<�r���[�{�����[���̍���(2D�J�����̎������L���B)
	float Volume;
	float targetVolume;//B�������ꂽ�ꍇ�̑傫��
private://�ۑ�p�ϐ�
	float m_vFovy;		//��p
	float m_vAspect;	//�A�X�y�N�g��
	float m_vNear;		//�j�A
	float m_vFar;		//�t�@�[
};
