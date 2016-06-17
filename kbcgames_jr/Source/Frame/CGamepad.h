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
	 *	コントローラーが接続されているか判定
	 *	ゲームのアップデートで必ず呼ぶ
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
	 *	左スティックの傾き量　
	 *	左：マイナス、右：プラス
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
	*	左スティックの傾き量　
	*	下：マイナス、上：プラス
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
	*	右スティックの傾き量　
	*	左：マイナス、右：プラス
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
	*	右スティックの傾き量　
	*	下：マイナス、上：プラス
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
	 *	ボタンが押されたか
	 */
	bool isButtonsDown(const int& Buttons)
	{
		return (m_GPNowBuf & Buttons);
	}
	// ボタンが押されたか判定
	bool isButtonsTrg(const int& Buttons)
	{
		return (!(m_GPOldBuf & Buttons) && (m_GPNowBuf & Buttons));
	}
	/*
	 *	左トリガーの深度
	 */
	BYTE  GetTriggerL()
	{
		return m_state.Gamepad.bLeftTrigger;
	}
	/*
	*	右トリガーの深度
	*/
	BYTE  GetTriggerR()
	{
		return m_state.Gamepad.bRightTrigger;
	}
	/*
	 *	コントローラーがさされているか
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

	XINPUT_STATE m_state;	//状態
	bool m_bConnected;	//コントローラー生存
};