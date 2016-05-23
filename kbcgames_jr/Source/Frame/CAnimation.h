#pragma once
#include"DXCommon.h"
#include<memory>
class CAnimation
{
public:
	/*
	 * コンストラクタ
	 */
	CAnimation() :
		m_pAnimController(nullptr),
		m_numAnimSet(0),
		m_isBlending(false),
		m_isInterpolate(false),
		m_numMaxTracks(0),
		m_interpolateTime(0.0f),
		m_interpolateEndTime(0.0f)
	{
	}
	/*
	* デストラクタ。
	*/
	~CAnimation()
	{
	}
	/*
	* 初期化。
	* アニメーションコントローラー。
	*/
	void Init(ID3DXAnimationController* anim);
	/*
	*アニメーションの再生。
	*再生したいアニメーションのインデックス。
	*/
	void PlayAnimation(int animationSetIndex);
	/*
	*アニメーションの再生。アニメーションの補完が行われます。
	*再生したいアニメーションのインデックス。
	*補間時間。
	*/
	void PlayAnimation(int animationSetIndex, float interpolateTime);
#if 0
	/*
	*アニメーションのブレンディング再生。
	*再生したいアニメーションのインデックス。
	*/
	void BlendAnimation(int animationSetIndex);
#endif
	/*
	*アニメーションセットの取得。
	*/
	int GetNumAnimationSet() const
	{
		return m_numAnimSet;
	}
	/*!
	*@brief	アニメーションの更新。
	*@param[in]		deltaTime	更新時間。単位は秒。
	*/
	void Update(float deltaTime);
private:
	ID3DXAnimationController* m_pAnimController;	//アニメーションコントローラ。
	int	m_numAnimSet;	//アニメーションセットの数。
	std::unique_ptr<ID3DXAnimationSet*[]> m_animationSets;	//アニメーションセットの配列。
	std::unique_ptr<float[]> m_blendRateTable;	//ブレンディングレートのテーブル。
	int	m_currentAnimationSetNo;	//現在再生中のアニメーショントラックの番号。
	int	m_currentTrackNo;	//現在のトラックの番号。
	int	m_numMaxTracks;	//アニメーショントラックの最大数。
	bool m_isBlending;	//アニメーションブレンディング中？
	bool m_isInterpolate;	//補間中？
	float m_interpolateEndTime;		//補間終了時間。
	float m_interpolateTime;	//補間時間。
};