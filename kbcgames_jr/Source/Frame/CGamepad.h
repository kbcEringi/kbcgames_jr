#pragma once

#include<Windows.h>
#include<XInput.h>
#pragma comment(lib, "Xinput.lib")
#include"DXCommon.h"

#define GAMEPAD(Class) Class::getGameInstance()

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )

#define GAMEPAD_DPAD_UP          0x0001
#define GAMEPAD_DPAD_DOWN        0x0002
#define GAMEPAD_DPAD_LEFT        0x0004
#define GAMEPAD_DPAD_RIGHT       0x0008
#define GAMEPAD_START            0x0010
#define GAMEPAD_BACK             0x0020
#define GAMEPAD_LEFT_THUMB       0x0040
#define GAMEPAD_RIGHT_THUMB      0x0080
#define GAMEPAD_LEFT_SHOULDER    0x0100
#define GAMEPAD_RIGHT_SHOULDER   0x0200
#define GAMEPAD_A                0x1000
#define GAMEPAD_B                0x2000
#define GAMEPAD_X                0x4000
#define GAMEPAD_Y                0x8000

class CGamepad
{
public:
	static CGamepad *getGameInstance()
	{
		if (!s_gamepad)
		{
			s_gamepad = new CGamepad();
		}
		return s_gamepad;
	}
	static void Delete()
	{
		delete s_gamepad;
		s_gamepad = NULL;
	}
	/*
	 *	�R���g���[���[���ڑ�����Ă��邩����
	 *	�Q�[���̃A�b�v�f�[�g�ŕK���Ă�
	 */
	void UpdateControllerState()
	{
		if (XInputGetState(0, &m_state) == ERROR_SUCCESS)
		{
			m_bConnected = true;
			ZeroMemory(&m_GPOldBuf, sizeof(m_GPOldBuf));
			memcpy(&m_GPOldBuf, &m_GPNowBuf, sizeof(m_GPNowBuf));
			m_GPNowBuf = m_state.Gamepad.wButtons;
		}
		else
		{
			m_bConnected = false;
		}
	
	}

	void ClearBuffer(){
		ZeroMemory(&m_GPNowBuf, sizeof(m_GPNowBuf));
		memcpy(&m_GPOldBuf, &m_GPNowBuf, sizeof(m_GPNowBuf));
	}
	/*
	 *	���X�e�B�b�N�̌X���ʁ@
	 *	���F�}�C�i�X�A�E�F�v���X
	 */
	SHORT GetStickL_X()
	{	
		if ((m_state.Gamepad.sThumbLX < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbLX > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbLX = 0;
		}
		return m_state.Gamepad.sThumbLX;
	}
	/*
	*	���X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	SHORT GetStickL_Y()
	{
		if ((m_state.Gamepad.sThumbLY < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbLY > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbLY = 0;

		}
		return m_state.Gamepad.sThumbLY;
	}
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	SHORT GetStickR_X()
	{

		if ((m_state.Gamepad.sThumbRX < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbRX > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbRX = 0;
		}
		return m_state.Gamepad.sThumbRX;
	}
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	SHORT GetStickR_Y()
	{
		if ((m_state.Gamepad.sThumbRY < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbRY > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbRY = 0;
		}
		return m_state.Gamepad.sThumbRY;
	}
	/*
	 *	�{�^���������ꂽ��
	 */
	bool isButtonsDown(const int& Buttons)
	{
		return (m_GPNowBuf & Buttons);
	}
	// �{�^���������ꂽ������
	bool isButtonsTrg(const int& Buttons)
	{
		return (!(m_GPOldBuf & Buttons) && (m_GPNowBuf & Buttons));
	}
	/*
	 *	���g���K�[�̐[�x
	 */
	BYTE  GetTriggerL()
	{
		return m_state.Gamepad.bLeftTrigger;
	}
	/*
	*	�E�g���K�[�̐[�x
	*/
	BYTE  GetTriggerR()
	{
		return m_state.Gamepad.bRightTrigger;
	}
	/*
	 *	�R���g���[���[��������Ă��邩
	 */
	bool GetConnected()
	{
		return m_bConnected;
	}
private:
	WORD m_GPNowBuf;
	WORD m_GPOldBuf;

	static CGamepad *s_gamepad;
	CGamepad(){
		m_bConnected = false;
		m_GPNowBuf = false;
		m_GPOldBuf = false;
	}

	XINPUT_STATE m_state;	//���
	bool m_bConnected;	//�R���g���[���[����
};