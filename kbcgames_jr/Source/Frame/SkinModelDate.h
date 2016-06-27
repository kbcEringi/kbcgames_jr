//�X�L�����f���f�[�^
#pragma once

#include"DXCommon.h"
#include<d3dx9anim.h>
#include"CAnimation.h"



struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//�����ςݍs��B
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	LPDIRECT3DTEXTURE9* ppTextures;
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;
};
class CAnimation;

class CSkinModelData
{
public:
	//�R���X�g���N�^
	CSkinModelData();
	//�f�X�g���N�^
	~CSkinModelData();
	//���f���f�[�^�����[�h
	void LoadModelData(const char* filepath,CAnimation* anim);
	//�����[�X
	void Release();
	//�t���[�����[�g�Q�b�^
	LPD3DXFRAME GetFrameRoot()
	{
		return m_FrameRoot;
	}
	//�A�j���[�V�����R���g���[���[�Q�b�^
	ID3DXAnimationController* GetAnimationController()
	{
		return m_pAnimController;
	}
	//�{�[���s����X�V
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);
private:
	//�t���[�����[�g
	LPD3DXFRAME m_FrameRoot;
	//�A�j���[�V�����R���g���[���[
	ID3DXAnimationController* m_pAnimController;
};