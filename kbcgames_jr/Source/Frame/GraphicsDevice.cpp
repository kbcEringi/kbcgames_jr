#include "GraphicsDevice.h"

CGraphicsDevice::CGraphicsDevice(void)
{

}

/************************************************/
/*					InitD3d�֐�					*/
/*�@�\�FDirect3D�f�o�C�X�E�I�u�W�F�N�g�������@  */
/*�����F										*/
/*  hWnd�F�E�B���h�E�n���h��					*/
/*�߂�l�F����(S_OK)�����s(E_FAIL)��			*/
/************************************************/
HRESULT CGraphicsDevice::InitD3d(HWND hWnd)
{
	//Direct3D�I�u�W�F�N�g�����s���H
	if ((this->m_pD3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		MessageBox(0, TEXT("Direct3D���������s"), NULL, MB_OK);
		return E_FAIL;	//���s�ԋp
	}

	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//�v���[���e�[�V�����p�����[�^������

	//�o�b�N�o�b�t�@�t�H�[�}�b�g�𖢒�`�ɃZ�b�g
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;	//�o�b�N�o�b�t�@�����Z�b�g
	//�X���b�v�G�t�F�N�g���Z�b�g
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;//�E�B���h�E���[�h��TRUE(�E�B���h�E�T�C�Y)�ɃZ�b�g
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(this->m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &this->m_pDevice)))
	{
		if (FAILED(this->m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &this->m_pDevice)))
		{
			MessageBox(0,
				TEXT("HAL���[�h��Direct3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�"), NULL, MB_OK);
			if (FAILED(this->m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &this->m_pDevice)))
			{
				if (FAILED(this->m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &this->m_pDevice)))
				{
					MessageBox(0, TEXT("Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}



/************************************************/
/*		FreeDX�֐�								*/
/*�@�\�FDirect3D�f�o�C�X�E�I�u�W�F�N�g���		*/
/*�����F�Ȃ�									*/
/*�߂�l�F�Ȃ�									*/
/************************************************/
void CGraphicsDevice::FreeDX(void)
{
	SAFE_RELEASE(this->m_pDevice);	//Direct3D�f�o�C�X���
	SAFE_RELEASE(this->m_pD3d);	//Direct3D�I�u�W�F�N�g���
}
