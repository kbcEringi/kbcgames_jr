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
		pAnimController(nullptr),
		numAnimSet(0),
		isBlending(false),
		isInterpolate(false),
		numMaxTracks(0),
		interpolateTime(0.0f),
		interpolateEndTime(0.0f)
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
	/*!
	*@brief	アニメーションの終了タイムを設定する。
		*@param[in]	animationSetIndex		アニメーションインデックス。
		*@param[in] endTime					アニメーションの終了タイム。 - 1.0を設定するとアニメーションファイルに設定されている終了タイムになる。
		*/
	void SetAnimationEndTime(int animationSetIndex, double endTime)
	{
		animationEndTime[animationSetIndex] = endTime;
	}
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
		return numAnimSet;
	}
	/*!
	*@brief	アニメーションの更新。
	*@param[in]		deltaTime	更新時間。単位は秒。
	*/
	void Update(float deltaTime);
private:
	ID3DXAnimationController*				pAnimController;		//!<アニメーションコントローラ。
	int										numAnimSet;				//!<アニメーションセットの数。
	std::unique_ptr<ID3DXAnimationSet*[]>	animationSets;			//!<アニメーションセットの配列。
	std::unique_ptr<float[]>				blendRateTable;			//!<ブレンディングレートのテーブル。
	std::unique_ptr<double[]>				animationEndTime;		//!<アニメーションの終了タイム。デフォルトは-1.0が入っていて、-1.0が入っている場合はID3DXAnimationSetのアニメーション終了タイムが優先される。
	//!<DirectX9のアニメーションセットに１秒以下のアニメーションを入れる方法が見つからない。1秒以下のアニメーションはこいつを適時設定。
	double									localAnimationTime;		//!<ローカルアニメーションタイム。
	int										currentAnimationSetNo;	//!<現在再生中のアニメーショントラックの番号。
	int										currentTrackNo;			//!<現在のトラックの番号。
	int										numMaxTracks;			//!<アニメーショントラックの最大数。
	bool									isBlending;				//!<アニメーションブレンディング中？
	bool									isInterpolate;			//!<補間中？
	float									interpolateEndTime;		//!<補間終了時間。
	float									interpolateTime;		//!<補間時間。
};