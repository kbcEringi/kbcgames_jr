#pragma once
#include"DXCommon.h"

#define SAFE_RELEASE(p)	{ if(p) { (p)->Release(); (p) = NULL; } }	

class CGraphicsDevice
{
public:
	CGraphicsDevice(void);
	HRESULT InitD3d(HWND);	//Direct3D�I�u�W�F�N�g����уf�o�C�X������
	void FreeDX();		//Direct3D�f�o�C�X�E�I�u�W�F�N�g���
	//LPDIRECT3DDEVICE9�ւ̃L���X�g�Ɋւ���I�y���[�^���Z�q
	operator LPDIRECT3DDEVICE9() const { return this->m_pDevice; }
private:
	LPDIRECT3D9 m_pD3d;			//DIRECT3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pDevice;	//Direct3D�f�o�C�X
};

//�O���[�o���֐����`���Ăǂ����ɂ�����̂�Ԃ�(�����ł�����cGraphicsDevice�N���X�̃C���X�^���X��Ԃ�)
inline CGraphicsDevice& graphicsDevice()
{
	extern CGraphicsDevice g_graphicsDevice;
	return g_graphicsDevice;
}