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
		pAnimController(nullptr),
		numAnimSet(0),
		isBlending(false),
		isInterpolate(false),
		numMaxTracks(0),
		interpolateTime(0.0f),
		interpolateEndTime(0.0f)
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
	/*!
	*@brief	�A�j���[�V�����̏I���^�C����ݒ肷��B
		*@param[in]	animationSetIndex		�A�j���[�V�����C���f�b�N�X�B
		*@param[in] endTime					�A�j���[�V�����̏I���^�C���B - 1.0��ݒ肷��ƃA�j���[�V�����t�@�C���ɐݒ肳��Ă���I���^�C���ɂȂ�B
		*/
	void SetAnimationEndTime(int animationSetIndex, double endTime)
	{
		animationEndTime[animationSetIndex] = endTime;
	}
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
		return numAnimSet;
	}
	/*!
	*@brief	�A�j���[�V�����̍X�V�B
	*@param[in]		deltaTime	�X�V���ԁB�P�ʂ͕b�B
	*/
	void Update(float deltaTime);
private:
	ID3DXAnimationController*				pAnimController;		//!<�A�j���[�V�����R���g���[���B
	int										numAnimSet;				//!<�A�j���[�V�����Z�b�g�̐��B
	std::unique_ptr<ID3DXAnimationSet*[]>	animationSets;			//!<�A�j���[�V�����Z�b�g�̔z��B
	std::unique_ptr<float[]>				blendRateTable;			//!<�u�����f�B���O���[�g�̃e�[�u���B
	std::unique_ptr<double[]>				animationEndTime;		//!<�A�j���[�V�����̏I���^�C���B�f�t�H���g��-1.0�������Ă��āA-1.0�������Ă���ꍇ��ID3DXAnimationSet�̃A�j���[�V�����I���^�C�����D�悳���B
	//!<DirectX9�̃A�j���[�V�����Z�b�g�ɂP�b�ȉ��̃A�j���[�V������������@��������Ȃ��B1�b�ȉ��̃A�j���[�V�����͂�����K���ݒ�B
	double									localAnimationTime;		//!<���[�J���A�j���[�V�����^�C���B
	int										currentAnimationSetNo;	//!<���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ��B
	int										currentTrackNo;			//!<���݂̃g���b�N�̔ԍ��B
	int										numMaxTracks;			//!<�A�j���[�V�����g���b�N�̍ő吔�B
	bool									isBlending;				//!<�A�j���[�V�����u�����f�B���O���H
	bool									isInterpolate;			//!<��Ԓ��H
	float									interpolateEndTime;		//!<��ԏI�����ԁB
	float									interpolateTime;		//!<��Ԏ��ԁB
};