/*
 *	�����_�[�^�[�Q�b�g
 *	�e�N�X�`���ɑ΂��ĕ`�悷��
 *	���߂́�����
 */

#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

#include"DXCommon.h"
#include"GraphicsDevice.h"

namespace Frame
{

	class CRenderTarget
	{
	public:
		/*
		 *	�R���X�g���N�^
		 */
		CRenderTarget();
		/*
		 *	�f�X�g���N�^
		 */
		~CRenderTarget();
		/*
		 *	�����_�[�^�[�Q�b�g�̍쐬
		 *	w					�����_�����O�^�[�Q�b�g�̕��B
		 *	h					�����_�����O�^�[�Q�b�g�̍����B
		 *	mipLevel			�~�b�v�}�b�v���x���B0���w�肵���ꍇ�̓~�b�v�}�b�v���T�|�[�g����Ă���GPU�ł�1*1�s�N�Z���܂ł̃~�b�v�}�b�v���쐬�����B
		 *	colorFormat			�J���[�o�b�t�@�̃t�H�[�}�b�g�B
		 *	depthStencilFormat	�[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
		 *	multiSampleType		�}���`�T���v�����O�̎�ށB
		 *	multiSampleQuality	�}���`�T���v�����O�̃N�I���e�B�B
		 */
		void Create(
			int w,
			int h,
			int mipLevel,
			D3DFORMAT colorFormat,
			D3DFORMAT depthStencilFormat,
			D3DMULTISAMPLE_TYPE multiSampleType,
			int multiSampleQuality
			);
		/*
		 *	�����_�����O�^�[�Q�b�g�̔j���B
		 */
		void Release();
		/*
		 *	�e�N�X�`�����擾�B
		 */
		IDirect3DTexture9* GetTexture()
		{
			return m_textureDX;
		}
		/*
		 *	�����_�����O�^�[�Q�b�g�̕����擾�B
		 */
		int GetWidth() const
		{
			return m_width;
		}
		/*
		 *	�����_�����O�^�[�Q�b�g�̍������擾�B
		 */
		int GetHeight() const
		{
			return m_height;
		}
		LPDIRECT3DSURFACE9 GetDepthSurfaceDx()
		{
			return m_depthSurface;
		}
		LPDIRECT3DSURFACE9 GetSurfaceDx()
		{
			return m_surface;
		}
		void SetDepthSurfaceDX(LPDIRECT3DSURFACE9 depthSurface)
		{
			m_depthSurface = depthSurface;
		}
		void SetSurfaceDX(LPDIRECT3DSURFACE9 surface)
		{
			m_surface = surface;
		}
	private:
		LPDIRECT3DSURFACE9		m_depthSurface;		//!<�[�x�o�b�t�@�p�̃T�[�t�F�C�X
		LPDIRECT3DSURFACE9		m_surface;			//!<�T�[�t�F�C�X
		IDirect3DTexture9*		m_textureDX;		//!<�������ݐ�̃e�N�X�`���B
		int						m_width;			//!<���B
		int						m_height;			//!<�����B
	};
}

#endif _RENDERTARGET_H_