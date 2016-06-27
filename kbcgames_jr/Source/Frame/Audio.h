#pragma once
#include "xact3.h"
#include "SceCommon.h"
#include"DXCommon.h"

typedef struct AUDIO_SET{
	IXACT3Engine* pEngine;	//XACT�G���W��
	IXACT3WaveBank* pWaveBank;  //�E�F�[�u�o���N
	IXACT3SoundBank* pSoundBank;	//�T�E���h�o���N
	const char* xactEngineName;	//XACT�G���W����
	const char* waveBankName;   //�E�F�[�u�o���N��
	const char* soundBankName;	//�T�E���h�o���N��
	VOID* pbWaveBank;           //�E�F�[�u�o���N�n���h��
	VOID* pbSoundBank; // �T�E���h�o���N�n���h��
	XACTINDEX cueIndex;                //�L���[�C���f�b�N�X

}AOUDI_SET;

//XACT������
class CAudio{
	CAudio();
	~CAudio();
public:
	static CAudio& GetAudio()
	{
		static CAudio instance;
		return instance;
	}
	//XACT�������֐��i�G���W�����A�E�F�[�u�o���N���A�T�E���h�o���N��)
	HRESULT Initialize(const char*, const char*, const char*);
	//�G���W���쐬
	HRESULT CreateEngine(const char*);
	//�E�F�[�u�o���N�쐬
	HRESULT CreateWaveBank(const char*);
	//�T�E���h�o���N�쐬
	HRESULT CreateSoundBank(const char*);
	//XACT�G���W���̎����I�^�X�N���s�p
	void Run();
	//XACT�I���֐�
	void CleanupXACT();

	//�L���[�Đ��֐�(�L���[��)
	void PlayCue(const char*);
	/****************************************************/
	/*StopCue�֐�										*/
	/*	�@�\�F�w�肵���o���N�L�[�̍Đ����~���܂�		*/
	/*	�����F											*/
	/*	  key		�F�o���N�L�[						*/
	/*	�߂�l�F�Ȃ�									*/
	/****************************************************/
	void StopCue(const char*);
private:
	bool isInited;
	AUDIO_SET m_audio;	//XACT�f�[�^�p
	CAudio* m_pAudio;
};

static inline CAudio& Audio()
{
	return CAudio::GetAudio();
}
//WaveBank����
