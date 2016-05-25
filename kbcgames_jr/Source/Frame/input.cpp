#include"Input.h"


void Dinput::Initialize(HWND hWnd)
{
	DirectInput8Create(
		GetModuleHandle(NULL),	// インスタンス ハンドル
		DIRECTINPUT_VERSION,	// DirectInputのバージョン
		IID_IDirectInput8,				// 取得インターフェイスのタイプ
		(VOID**)&m_pDInput,			// インターフェイスポインタ
		NULL);					// 使わない
	m_pDInput->CreateDevice(
		GUID_SysKeyboard,	// キーボードを受け付ける
		&KeyDevice,		// IDirectInputDevice8ポインタ
		NULL);
	KeyDevice->SetDataFormat(&c_dfDIKeyboard);
	KeyDevice->SetCooperativeLevel(
		hWnd, // ウィンドウハンドル
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}