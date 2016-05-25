#include"Input.h"


void Dinput::Initialize(HWND hWnd)
{
	DirectInput8Create(
		GetModuleHandle(NULL),	// �C���X�^���X �n���h��
		DIRECTINPUT_VERSION,	// DirectInput�̃o�[�W����
		IID_IDirectInput8,				// �擾�C���^�[�t�F�C�X�̃^�C�v
		(VOID**)&m_pDInput,			// �C���^�[�t�F�C�X�|�C���^
		NULL);					// �g��Ȃ�
	m_pDInput->CreateDevice(
		GUID_SysKeyboard,	// �L�[�{�[�h���󂯕t����
		&KeyDevice,		// IDirectInputDevice8�|�C���^
		NULL);
	KeyDevice->SetDataFormat(&c_dfDIKeyboard);
	KeyDevice->SetCooperativeLevel(
		hWnd, // �E�B���h�E�n���h��
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}