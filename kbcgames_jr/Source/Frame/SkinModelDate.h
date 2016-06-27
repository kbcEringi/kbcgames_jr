//スキンモデルデータ
#pragma once

#include"DXCommon.h"
#include<d3dx9anim.h>
#include"CAnimation.h"



struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
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
	//コンストラクタ
	CSkinModelData();
	//デストラクタ
	~CSkinModelData();
	//モデルデータをロード
	void LoadModelData(const char* filepath,CAnimation* anim);
	//リリース
	void Release();
	//フレームルートゲッタ
	LPD3DXFRAME GetFrameRoot()
	{
		return m_FrameRoot;
	}
	//アニメーションコントローラーゲッタ
	ID3DXAnimationController* GetAnimationController()
	{
		return m_pAnimController;
	}
	//ボーン行列を更新
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);
private:
	//フレームルート
	LPD3DXFRAME m_FrameRoot;
	//アニメーションコントローラー
	ID3DXAnimationController* m_pAnimController;
};