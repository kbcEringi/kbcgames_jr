#pragma once
#include"DXCommon.h"
#include<memory>
class CAnimation
{
public:
	/*
	 * �R���X�g���N�^
	 */
	CAnimation() :
		m_pAnimController(nullptr),
		m_numAnimSet(0),
		m_isBlending(false),
		m_isInterpolate(false),
		m_numMaxTracks(0),
		m_interpolateTime(0.0f),
		m_interpolateEndTime(0.0f)
	{
	}
	/*
	* �f�X�g���N�^�B
	*/
	~CAnimation()
	{
	}
	/*
	* �������B
	* �A�j���[�V�����R���g���[���[�B
	*/
	void Init(ID3DXAnimationController* anim);
	/*
	*�A�j���[�V�����̍Đ��B
	*�Đ��������A�j���[�V�����̃C���f�b�N�X�B
	*/
	void PlayAnimation(int animationSetIndex);
	/*
	*�A�j���[�V�����̍Đ��B�A�j���[�V�����̕⊮���s���܂��B
	*�Đ��������A�j���[�V�����̃C���f�b�N�X�B
	*��Ԏ��ԁB
	*/
	void PlayAnimation(int animationSetIndex, float interpolateTime);
#if 0
	/*
	*�A�j���[�V�����̃u�����f�B���O�Đ��B
	*�Đ��������A�j���[�V�����̃C���f�b�N�X�B
	*/
	void BlendAnimation(int animationSetIndex);
#endif
	/*
	*�A�j���[�V�����Z�b�g�̎擾�B
	*/
	int GetNumAnimationSet() const
	{
		return m_numAnimSet;
	}
	/*!
	*@brief	�A�j���[�V�����̍X�V�B
	*@param[in]		deltaTime	�X�V���ԁB�P�ʂ͕b�B
	*/
	void Update(float deltaTime);
private:
	ID3DXAnimationController* m_pAnimController;	//�A�j���[�V�����R���g���[���B
	int	m_numAnimSet;	//�A�j���[�V�����Z�b�g�̐��B
	std::unique_ptr<ID3DXAnimationSet*[]> m_animationSets;	//�A�j���[�V�����Z�b�g�̔z��B
	std::unique_ptr<float[]> m_blendRateTable;	//�u�����f�B���O���[�g�̃e�[�u���B
	int	m_currentAnimationSetNo;	//���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ��B
	int	m_currentTrackNo;	//���݂̃g���b�N�̔ԍ��B
	int	m_numMaxTracks;	//�A�j���[�V�����g���b�N�̍ő吔�B
	bool m_isBlending;	//�A�j���[�V�����u�����f�B���O���H
	bool m_isInterpolate;	//��Ԓ��H
	float m_interpolateEndTime;		//��ԏI�����ԁB
	float m_interpolateTime;	//��Ԏ��ԁB
};