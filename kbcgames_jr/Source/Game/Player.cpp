#include "Player.h"
#include "bulletPhysics.h"

struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;

	SweepResultGround()
	{
		isHit = false;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//�����B
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.Set(
			convexResult.m_hitNormalLocal.x(),
			convexResult.m_hitNormalLocal.y(),
			convexResult.m_hitNormalLocal.z()
			);
		float d = hitPointNormal.Dot(D3DXVECTOR3::Up);
		if (d < 0.0f) {
			//�������ĂȂ��B
			return 0.0f;
		}
		if (acosf(d) > CMath::PI * 0.2) {
			//�z���g�͒n�ʂ��ǂ����Ƃ��̑���������̂��x�X�g�Ȃ񂾂��ǁA����͊p�x�ŁB
			return 0.0f;
		}
		isHit = true;
		hitPos.Set(
			convexResult.m_hitPointLocal.x(),
			convexResult.m_hitPointLocal.y(),
			convexResult.m_hitPointLocal.z());
		return 0.0f;
	}
};
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	D3DXVECTOR3 hitNormalXZ;
	bool isHit;
	D3DXVECTOR3 hitPos;
	SweepResultWall()
	{
		isHit = false;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//�����B
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.Set(
			convexResult.m_hitNormalLocal.x(),
			convexResult.m_hitNormalLocal.y(),
			convexResult.m_hitNormalLocal.z()
			);
		float d = hitPointNormal.Dot(D3DXVECTOR3::Up);
		if (acosf(d) < CMath::PI * 0.2) {
			//�z���g�͒n�ʂ��ǂ����Ƃ��̑���������̂��x�X�g�Ȃ񂾂��ǁA����͊p�x�ŁB
			return 0.0f;
		}
		isHit = true;
		//XZ���ʂł̖@���B
		hitNormalXZ.x = hitPointNormal.x;
		hitNormalXZ.y = 0.0f;
		hitNormalXZ.z = hitPointNormal.z;
		hitNormalXZ.Normalize();

		btTransform transform = convexResult.m_hitCollisionObject->getWorldTransform();
		hitPos.Set(
			convexResult.m_hitPointLocal.x(),
			convexResult.m_hitPointLocal.y(),
			convexResult.m_hitPointLocal.z());
		return 0.0f;
	}
};

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	Obj.Initialize("XFile\\Player.x");	//�v���C���[X�t�@�C��
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X���W
	m_position.y = 0.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	m_Ground = true;					//���n�ʂɂ��Ă��邩�H�iTRUE�j
	NowPositionY = 0.0f;				//����Y�|�W�V����
	Gravity = -0.2;						//�d��
	MaxJump = 1.0f;						//�W�����v�����
	SpeedPower = 0.0f;					//���������
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

}

void CPlayer::Update()
{
	
	Move();//�ړ��֐�
	//Jump();//�v���C���[�W�����v�֐�

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPlayer::Move()//�ړ�
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);
	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//�E
	{
		m_position.x += 0.2f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//��
	{
		m_position.x -= 0.2f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//��
	{
		m_position.y += 0.2f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//��
	{
		m_position.y -= 0.2f;
	}
	else
	{
		(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
	}
	
	
}

//void CPlayer::Jump()//�W�����v
//{
//	//�W�����v����(�n�ʂɂ��Ă��鎞)
//	if (m_Ground == true && KEYDOWN(diks, DIK_SPACE) & 0x80)
//	{
//		NowPositionY = m_position.y;//���̃|�W�V��������
//		m_Ground = false;
//		SpeedPower = MaxJump;
//		
//		
//	}
//	//�n�ʂɂ��Ă��Ȃ���
//	if (!m_Ground)
//	{
//		SpeedPower += Gravity;
//		m_position.y += SpeedPower;
//		if (NowPositionY >= m_position.y)
//			m_Ground = true;
//	}
//	
//}