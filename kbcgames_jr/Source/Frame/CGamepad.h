#pragma once

#include<Windows.h>
#include<XInput.h>
#include<d3d9.h>
#include<d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define SINSTANCE(Class) Class::GetInstance()

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
	static CGamepad *GetInstance()
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
		}
		else
		{
			m_bConnected = false;
		}
		if ((m_state.Gamepad.sThumbLX < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbLX > -INPUT_DEADZONE) && 
			(m_state.Gamepad.sThumbLY < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbLY > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbLX = 0;
			m_state.Gamepad.sThumbLY = 0;
		}
		if ((m_state.Gamepad.sThumbRX < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbRX > -INPUT_DEADZONE)&&
			(m_state.Gamepad.sThumbRY < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbRY > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbRX = 0;
			m_state.Gamepad.sThumbRY = 0;
		}
	}
	/*
	 *	左スティックの傾き量　
	 *	左：マイナス、右：プラス
	 */
	SHORT GetStickL_X()
	{	
		return m_state.Gamepad.sThumbLX;
	}
	/*
	*	左スティックの傾き量　
	*	下：マイナス、上：プラス
	*/
	SHORT GetStickL_Y()
	{
		return m_state.Gamepad.sThumbLY;
	}
	/*
	*	右スティックの傾き量　
	*	左：マイナス、右：プラス
	*/
	SHORT GetStickR_X()
	{
		return m_state.Gamepad.sThumbRX;
	}
	/*
	*	右スティックの傾き量　
	*	下：マイナス、上：プラス
	*/
	SHORT GetStickR_Y()
	{
		return m_state.Gamepad.sThumbRY;
	}
	/*
	 *	ボタンが押されたか
	 */
	bool isButtonsDown(const int& Buttons)
	{
		return (m_state.Gamepad.wButtons & Buttons);
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
	static CGamepad *s_gamepad;
	CGamepad(){}

	XINPUT_STATE m_state;	//状態
	bool m_bConnected;	//コントローラー生存
};

CGamepad *CGamepad::s_gamepad = new CGamepad();
