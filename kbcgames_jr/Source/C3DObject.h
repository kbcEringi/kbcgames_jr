#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>

class C3DObject
{
public:
	/*
	*第一引数　Xファイル名（例："XFile\\kyu.x"）
	*第二引数　グラフィックパス（デフォルト＝０、スペキュラ＝１）
	*/
	void Initialize(LPCSTR , int pass = 0);
	/*
	*第一引数　ワールドマトリクス（自分の位置）
	*第二引数　ビューマトリクス（カメラの位置）
	*/
	void Draw(D3DXMATRIX, D3DXMATRIX);
	~C3DObject();
protected:
	LPD3DXBUFFER m_D3DXMtrlBuffer;	//マテリアル
	DWORD m_NumMaterials;		//マテリアル数
	LPD3DXMESH m_Mesh;			//メッシュ
	LPDIRECT3DTEXTURE9*  m_pMeshTextures;	//メッシュテクスチャ
	ID3DXEffect* m_pEffect;
	D3DXMATRIX  m_projMatrix;

	D3DXMATERIAL *materials;

	static const int LIGHT_NUM = 4;
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//ライトの色。
	D3DXVECTOR4	m_ambientLight;						//環境光

	int m_Graphicspass;
};