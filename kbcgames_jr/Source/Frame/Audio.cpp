#include "Audio.h"

CAudio::CAudio(){
	isInited = false;
	//memset(&m_audio, 0, sizeof(m_audio));
}//�R���X�g���N�^
CAudio::~CAudio()//�f�X�g���N�^
{
	CleanupXACT();
}

//�O���[�o���ݒ�t�@�C����p����XACT�G���W��������
HRESULT CAudio::Initialize(const char* engineName, const char* wbName, const char* sbName)
{
	if (isInited) {
		return S_OK;
	}
	isInited = true;
	if (FAILED(CreateEngine(engineName))){ return E_FAIL; }
	if (FAILED(CreateWaveBank(wbName))){ return E_FAIL; }//�E�F�[�u�o���N
	if (FAILED(CreateSoundBank(sbName))){ return E_FAIL; }//�T�E���h�o���N
	return S_OK;	//����
}

HRESULT CAudio::CreateEngine(const char* engineFileName)
{
	HANDLE hFile;	//�t�@�C���n���h��
	HRESULT hr = E_FAIL;	//����

					/*�G���W���쐬*/
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(XACT3CreateEngine(0, &m_audio.pEngine))){ return E_FAIL; }

	m_audio.xactEngineName = engineFileName;


//xgs�t�@�C���ǂݍ���
	void* xgsBuf = NULL;//xgs�o�b�t�@�[
	DWORD xgsFileSize;    //xgs�t�@�C���T�C�Y
	bool isSuccess = false;//��������
	//�t�@�C������
	hFile = CreateFile(engineFileName, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile){
		xgsFileSize = GetFileSize(hFile, NULL);        //�t�@�C���T�C�Y���擾
		if (xgsFileSize != INVALID_FILE_SIZE){       //�t�@�C���T�C�Y�擾����
			xgsBuf = CoTaskMemAlloc(xgsFileSize);    //�t�@�C���T�C�Y���������m��
			if (xgsBuf){    //�������m�ې���
				DWORD byteRead;
				//xgs�t�@�C���Ǎ�
				if (NULL != ReadFile(hFile, xgsBuf, xgsFileSize, &byteRead, NULL)){
					isSuccess = true;    //����
				}
			}
		}
		CloseHandle(hFile);        //�t�@�C���n���h�������
	}

	if (!isSuccess){ return E_FAIL; }

	//�ǂݍ���xgs�t�@�C������G���W��������
	XACT_RUNTIME_PARAMETERS xactParams = { 0 };
	xactParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	xactParams.pGlobalSettingsBuffer = xgsBuf;
	xactParams.globalSettingsBufferSize = xgsFileSize;
	xactParams.globalSettingsFlags = XACT_FLAG_GLOBAL_SETTINGS_MANAGEDATA;

	if (FAILED(m_audio.pEngine->Initialize(&xactParams))){
		return E_FAIL;
	}
	return S_OK;
}

//WaveBank����
HRESULT CAudio::CreateWaveBank(const char* wbFileName){
	HANDLE hFile;			//�t�@�C���n���h��
	HANDLE hMapFile;		//�t�@�C���}�b�s���O�n���h��
	DWORD dwFileSize;		//�t�@�C���T�C�Y
	HRESULT hr = E_FAIL;	//����

	m_audio.waveBankName = wbFileName;		//�E�F�[�u�o���N���Z�b�g

					/*�E�F�[�u�o���N�쐬*/
	//�E�F�[�u�o���N�n���h���擾
	hFile = CreateFile(m_audio.waveBankName, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//CreateFile�ɐ����������H
	if (hFile != INVALID_HANDLE_VALUE){
		dwFileSize = GetFileSize(hFile, NULL);	//�E�F�[�u�o���N�t�@�C���T�C�Y�擾
		//�t�@�C���T�C�Y�擾�ɐ����������H
		if (dwFileSize != -1){
			//�E�F�[�u�o���N�ɑ΂���t�@�C���}�b�s���O�I�u�W�F�N�g��ǎ���p�ō쐬
			hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL);
			//�}�b�s���O�ɐ����������H
			if (hMapFile){
				//�E�F�[�u�o���N�t�@�C���}�b�v�̃r���[��ݒ�
				m_audio.pbWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				//�r���[�̎擾�ɐ����������H
				if (m_audio.pbWaveBank){
					//���������E�F�[�u�o���N���쐬
					if (SUCCEEDED(
						m_audio.pEngine->CreateInMemoryWaveBank(
						m_audio.pbWaveBank, dwFileSize, 0, 0, &m_audio.pWaveBank)))
					{
						hr = S_OK;	//�E�F�[�u�o���N�擾����
					}
				}
				CloseHandle(hMapFile); //�t�@�C���}�b�s���O�n���h�������
			}
		}
		CloseHandle(hFile); //�E�F�[�u�o���N�t�@�C���n���h�������
	}
	return hr;
}

//SoundBank����
HRESULT CAudio::CreateSoundBank(const char* sbFileName){
	HANDLE hFile;			//�t�@�C���n���h��
	HANDLE hMapFile;		//�t�@�C���}�b�s���O�n���h��
	DWORD dwFileSize;		//�t�@�C���T�C�Y
	HRESULT hr = E_FAIL;	//����

	m_audio.soundBankName = sbFileName;		//�T�E���h�o���N���Z�b�g

	//�T�E���h�o���N�n���h���擾
	hFile = CreateFile(m_audio.soundBankName,
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	//CreateFile�ɐ����������H
	if (hFile != INVALID_HANDLE_VALUE){
		dwFileSize = GetFileSize(hFile, NULL);
		//�t�@�C���T�C�Y�擾�ɐ����������H
		if (dwFileSize != -1){
			hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL);
			//�}�b�s���O�ɐ����������H
			if (hMapFile){
				m_audio.pbSoundBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);	//�T�E���h�o���N�t�@�C���}�b�v�̃r���[��ݒ�
				//�r���[�̎擾�ɐ����������H
				if (m_audio.pbSoundBank){
					if (FAILED(m_audio.pEngine->CreateSoundBank(
						m_audio.pbSoundBank, dwFileSize,
						0, 0, &m_audio.pSoundBank))){
						return E_FAIL;	//�T�E���h�o���N�쐬���s
					}
					hr = S_OK;	//�T�E���h�o���N��������
				}
				CloseHandle(hMapFile); //�t�@�C���}�b�s���O�n���h�������
			}
		}
		CloseHandle(hFile); //�T�E���h�o���N�t�@�C���n���h�������
	}
}

//XACT�̎�������
void CAudio::Run(){
	if (m_audio.pEngine != NULL){
		m_audio.pEngine->DoWork();	//�����I�^�X�N���s
	}
}

//CleanupXACT�֐�����
void CAudio::CleanupXACT(){
/*	if (m_audio.pEngine){
		m_audio.pEngine->ShutDown();    //XACT���V���b�g�_�E��
		SAFE_RELEASE(m_audio.pEngine);    //XACT�G���W�������
	}
	if (m_audio.pbSoundBank){
		UnmapViewOfFile(m_audio.pbSoundBank);    //�T�E���h�o���N�̃r���[���A���}�b�v
	}
	m_audio.pbSoundBank = NULL;
	if (m_audio.pbWaveBank){
		UnmapViewOfFile(m_audio.pbWaveBank);    //�E�F�[�u�o���N�̃r���[���A���}�b�v    
	}
	m_audio.pbWaveBank = NULL;
	m_audio.pWaveBank->Destroy();
	m_audio.pSoundBank->Destroy();
	CoUninitialize();*/
}

void CAudio::PlayCue(const char* cue){
	if (m_audio.pSoundBank != NULL){
		//�T�E���h�o���N����w�肵���L���[�̃L���[�C���f�b�N�X�擾
		m_audio.cueIndex = m_audio.pSoundBank->GetCueIndex(cue);
		//�L���[�C���f�b�N�X�擾�����H
		if (m_audio.cueIndex != XACTINDEX_INVALID){
			m_audio.pSoundBank->Play(m_audio.cueIndex, 0, 0, NULL);    //�L���[�Đ�
		}
	}
}

void CAudio::StopCue(const char* cue){
	if (m_audio.pSoundBank != NULL){
		//�T�E���h�o���N����w�肵���L���[�̃L���[�C���f�b�N�X�擾
		m_audio.cueIndex = m_audio.pSoundBank->GetCueIndex(cue);
		//�L���[�C���f�b�N�X�擾�����H
		if (m_audio.cueIndex != XACTINDEX_INVALID){
			m_audio.pSoundBank->Stop(m_audio.cueIndex,
				XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);    //�L���[��~
		}
	}
}