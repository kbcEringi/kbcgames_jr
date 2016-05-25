#include"CAnimation.h"

void CAnimation::Init(ID3DXAnimationController* anim)
{
	m_pAnimController = anim;
	ID3DXAnimationSet* animSet;
	m_pAnimController->GetAnimationSet(0, &animSet);
	m_numAnimSet = m_pAnimController->GetMaxNumAnimationSets();
	m_numMaxTracks = m_pAnimController->GetMaxNumTracks();
	m_blendRateTable.reset(new float[m_numMaxTracks]);
	m_animationSets.reset(new ID3DXAnimationSet*[m_numAnimSet]);
	for (int i = 0; i < m_numMaxTracks; i++){
		m_blendRateTable[i] = 1.0f;
	}
	//�A�j���[�V�����Z�b�g���������B
	for (int i = 0; i < m_numAnimSet; i++) {
		m_pAnimController->GetAnimationSet(i, &m_animationSets[i]);
	}
}
#if 0
void CAnimation::BlendAnimation(int animationSetIndex)
{
	if (pAnimController){
		isBlending = true;
		currentTrackNo++;
		currentTrackNo %= numAnimSet;
		pAnimController->SetTrackWeight(0, 0.0f);
		pAnimController->SetTrackWeight(1, 1.0f);
		pAnimController->SetTrackSpeed(0, 1.0f);
		pAnimController->SetTrackSpeed(1, 1.0f);
		pAnimController->SetTrackEnable(currentTrackNo, TRUE);
		pAnimController->SetTrackAnimationSet(currentTrackNo, animationSets[animationSetIndex]);
	}
}
#endif
void CAnimation::PlayAnimation(int animationSetIndex)
{
	if (animationSetIndex < m_numAnimSet) {
		if (m_pAnimController) {
			m_currentAnimationSetNo = animationSetIndex;
			m_currentTrackNo = 0;
			//0�ԖڈȊO�̃g���b�N�͖����ɂ���B
			for (int i = 1; i < m_numMaxTracks; i++) {
				m_pAnimController->SetTrackEnable(i, FALSE);
			}
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_animationSets[m_currentAnimationSetNo]);
			m_pAnimController->SetTrackEnable(0, TRUE);
			m_pAnimController->SetTrackPosition(0, 0.0f);
		}
	}
}
void CAnimation::PlayAnimation(int animationSetIndex, float interpolateTime)
{
	if (animationSetIndex < m_numAnimSet) {
		if (m_pAnimController) {
			//��ԊJ�n�̈�B
			m_isInterpolate = true;
			this->m_interpolateTime = 0.0f;
			m_interpolateEndTime = interpolateTime;
			m_currentTrackNo = (m_currentTrackNo + 1) % m_numMaxTracks;
			m_pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_animationSets[animationSetIndex]);
			m_pAnimController->SetTrackEnable(m_currentTrackNo, TRUE);
			m_pAnimController->SetTrackSpeed(m_currentTrackNo, 1.0f);
			m_pAnimController->SetTrackPosition(m_currentTrackNo, 0.0f);
		}
	}
}
void CAnimation::Update(float deltaTime)
{
	if (m_pAnimController) {
		m_pAnimController->AdvanceTime(deltaTime, NULL);
		if (m_isInterpolate) {
			//��Ԓ��B
			m_interpolateTime += deltaTime;
			float weight = 0.0f;
			if (m_interpolateTime > m_interpolateEndTime) {
				//��ԏI���B
				m_isInterpolate = false;
				weight = 1.0f;
				//���݂̃g���b�N�ȊO�𖳌��ɂ���B
				for (int i = 0; i < m_numMaxTracks; i++) {
					if (i != m_currentTrackNo) {
						m_pAnimController->SetTrackEnable(i, FALSE);
					}
				}
			}
			else {
				weight = m_interpolateTime / m_interpolateEndTime;
				float invWeight = 1.0f - weight;
				//�E�F�C�g��ݒ肵�Ă����B
				for (int i = 0; i < m_numMaxTracks; i++) {
					if (i != m_currentTrackNo) {
						m_pAnimController->SetTrackWeight(i, m_blendRateTable[i] * invWeight);
					}
					else {
						m_pAnimController->SetTrackWeight(i, weight);
					}
				}
			}
		}
	}
}