#include "RayCursor.h"
#include "Ccamera.h"
#include"GraphicsDevice.h"
#include"Stage\CStageManager.h"
struct SCollisionResult : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;
	D3DXVECTOR3 startPos;
	float dist;
	SCollisionResult()
	{
		isHit = false;
		dist = FLT_MAX;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//�����B
			return 0.0f;
		}
		//��_�ƃ��C�̎n�_�Ƃ̋����𒲂ׂ�B
		D3DXVECTOR3 vDist;
		
		vDist.x = convexResult.m_hitPointLocal.x();
		vDist.y = convexResult.m_hitPointLocal.y();
		vDist.z = convexResult.m_hitPointLocal.z();
			
		vDist -= startPos;
		float distTmp = D3DXVec3LengthSq(&vDist);
		if (distTmp < dist) {
			//�������̂ق����߂��B
			
			hitPos.x = convexResult.m_hitPointLocal.x();
			hitPos.y = convexResult.m_hitPointLocal.y();
			hitPos.z = convexResult.m_hitPointLocal.z();
			dist = distTmp;

		}

		isHit = true;
		return 0.0f;
	}
};

CRayCursor::CRayCursor()
{

}

CRayCursor::~CRayCursor()
{

}

void CRayCursor::Initialize()
{
	m_interval = 0.0f;
	m_sphereColli = new btSphereShape(0.1f);
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	start = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	end = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
}

void CRayCursor::Update(D3DXVECTOR3 pos, D3DXMATRIX ViewMatrix, D3DXMATRIX ProjectionMatrix)
{
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		bool t = GAMEPAD(CGamepad)->isButtonsTrg(GAMEPAD_A);
		if (KEYDOWN(diks, DIK_SPACE) & 0x80 || GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_A)
			&& STAGEMANEGER->GetStage()->GetWind()->GetState() != STAGEMANEGER->GetStage()->GetWind()->State_DecideYPower)
		{
			//���C���΂��ăf�u���𐶐�������W�����߂�B

			start.x = pos.x;
			start.y = pos.y;
			start.z = 0.0f;
			start.w = 1.0f;
			end.x = pos.x;
			end.y = pos.y;
			end.z = 1.0f;
			end.w = 1.0f;

		/*	int screenW = 960;
			int screenH = 540;*/
			D3DXMATRIX mViewInv = ViewMatrix;
			D3DXMATRIX mProjInv = ProjectionMatrix;
#if 1 //DirectX�̊֐����g�p�����o�[�W�����B
			{
				D3DVIEWPORT9 vp;
				(*graphicsDevice()).GetViewport(&vp);
				D3DXVec3Unproject(
					reinterpret_cast<D3DXVECTOR3*>(&start),
					reinterpret_cast<const D3DXVECTOR3*>(&start),
					&vp,
					reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
					reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
					NULL
					);

				D3DXVec3Unproject(
					reinterpret_cast<D3DXVECTOR3*>(&end),
					reinterpret_cast<const D3DXVECTOR3*>(&end),
					&vp,
					reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
					reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
					NULL
					);
			}
#else
			CMatrix mVpInv = CMatrix::Identity;

			3D��Ԃ̍��W���X�N���[�����W�n�ɕϊ�����ɂ́A�J�����s��~�v���W�F�N�V�����s��~�X�N���[���s�����Z���Ă��΂����E�E�E
				�܂�A�X�N���[�����W�n����R�c��Ԃ̍��W�ɖ߂����߂ɂ́A�X�N���[���s��̋t�s��~�v���W�F�N�V�����s��̋t�s��~�J�����s��̋t�s���
				��Z���Ă��΂������ƂɂȂ�B(�t�s�����Z����Ƃ������Ƃ́A���̕ϊ���ł������Ƃ����Ӗ�������B�j

				�X�N���[�����W�n���琳�K�����W�n�ɕϊ����邽�߂̍s����v�Z����B
				mVpInv.m[0][0] = screenW / 2.0f;
			mVpInv.m[1][1] = -screenH / 2.0f;
			mVpInv.m[3][0] = screenW / 2.0f;
			mVpInv.m[3][1] = screenH / 2.0f;
			mVpInv.Inverse(mVpInv);		//���K�����W�n�ɕϊ����邽�߂ɂ̓X�N���[�����W�n�ɕϊ�����s��̋t�s������߂��炢���B
			���K�����W�n����J�������W�n�ɕϊ�����s����v�Z����B
				mProjInv.Inverse(mProjInv);	//�J�������W�n�ɕϊ�����ɂ́A�ˉe��Ԃɕϊ�����s��̋t�s������߂�B
			mViewInv.Inverse(mViewInv);	//���[���h���W�n�ɕϊ�����ɂ́A�J�����s��̋t�s������߂�B
			�X�N���[���s��̋t�s��~�v���W�F�N�V�����s��̋t�s��~�J�����s��̋t�s������߂�B
				CMatrix mInv;
			mInv.Mul(mVpInv, mProjInv);
			mInv.Mul(mInv, mViewInv);
			mInv.Mul(start);
			mInv.Mul(end);
			�v���W�F�N�V�����s����������w�Ŋ���K�v������̂ŁA���Z����B
				start.x /= start.w;
			start.y /= start.w;
			start.z /= start.w;
			end.x /= end.w;
			end.y /= end.w;
			end.z /= end.w;
#endif
			//������𒲂ׂ�
			btTransform btStart, btEnd;
			btStart.setIdentity();
			btEnd.setIdentity();
			btStart.setOrigin(btVector3(start.x, start.y, start.z));
			btEnd.setOrigin(btVector3(end.x, end.y, end.z));
			SCollisionResult callback;
			callback.startPos.x = start.x;
			callback.startPos.y = start.y;
			callback.startPos.z = start.z;
			g_bulletPhysics.ConvexSweepTest(m_sphereColli, btStart, btEnd, callback);
			if (callback.isHit) {//����������
				if (GAMEFLG->Getflg() == true)
				{
					//�q�b�g����XZ���W��Player�̑����ɐݒu(2D)
					D3DXVECTOR3 pos = D3DXVECTOR3(callback.hitPos.x, STAGEMANEGER->GetStage()->GetPlayer()->GetPosition().y - 0.5f, 0); //callback.hitPos.z);
					m_Pointa->SetPos(&pos);
				}
				else
				{
					//�q�b�g�����ꏊ�ɐݒu(3D)
					m_Pointa->SetPos(&callback.hitPos);
				}
				STAGEMANEGER->GetStage()->GetPointa()->SetDraw(true);
				STAGEMANEGER->GetStage()->GetPlayer()->StopRunAudio();
				STAGEMANEGER->GetStage()->GetPlayer()->SetRunAudio();
			}
		}
		else
		{
			(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
		}
	}
	GAMEPAD(CGamepad)->UpdateControllerState();
}