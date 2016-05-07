#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"

struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;

	SweepResultGround()
	{
		isHit = false;
		hitPos.x = 0.0f;
		hitPos.y = 0.0f;
		hitPos.z = 0.0f;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//�����B
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		
		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();
		
		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

		float d = D3DXVec3Dot(&hitPointNormal, &Up);
		if (d < 0.0f) {
			//�������ĂȂ��B
			return 0.0f;
		}
		if (acosf(d) > PI * 0.2) {
			//�z���g�͒n�ʂ��ǂ����Ƃ��̑���������̂��x�X�g�Ȃ񂾂��ǁA����͊p�x�ŁB
			return 0.0f;
		}
		isHit = true;
		
		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.y = convexResult.m_hitPointLocal.y();
		hitPos.z = convexResult.m_hitPointLocal.z();

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
		
		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();
		
		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

		float d = D3DXVec3Dot(&hitPointNormal, &Up);
		if (acosf(d) < PI * 0.2) {
			//�z���g�͒n�ʂ��ǂ����Ƃ��̑���������̂��x�X�g�Ȃ񂾂��ǁA����͊p�x�ŁB
			return 0.0f;
		}
		isHit = true;
		//XZ���ʂł̖@���B
		hitNormalXZ.x = hitPointNormal.x;
		hitNormalXZ.y = 0.0f;
		hitNormalXZ.z = hitPointNormal.z;// hitPointNormal.z
		//D3DXVec3Normalize(&hitNormalXZ, &hitNormalXZ);
		//D3DXVec3Normalize(&hitNormalXZ, &hitPointNormal);


		btTransform transform = convexResult.m_hitCollisionObject->getWorldTransform();
		
		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.y = convexResult.m_hitPointLocal.y();
		hitPos.z = convexResult.m_hitPointLocal.z();

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
	m_position.x = -2.0f;				//X���W
	m_position.y = 2.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	m_Ground = true;					//���n�ʂɂ��Ă��邩�H�iTRUE�j
	NowPositionY = 0.0f;				//����Y�|�W�V����
	Gravity = -0.2;						//�d��
	MaxJump = 1.0f;						//�W�����v�����
	SpeedPower = 0.0f;					//���������
	m_radius = 1.0;						//�o�E���f�B���O�X�t�B�A�̔��a�B
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	m_moveSpeed.x = 0.0f;				//�ړ����x
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//�ړ����x
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	//�R���W�����������B
	m_collisionShape = new btSphereShape(m_radius);
	float mass = 1000.0f;
	btTransform rbTransform;
	rbTransform.setIdentity();
	rbTransform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(rbTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(0);
	//���[���h�ɒǉ��B
	g_bulletPhysics.AddRigidBody(m_rigidBody);

}

void CPlayer::Update()
{
	
	Move();//�ړ��֐�
	//Jump();//�v���C���[�W�����v�֐�
	static float deltaTime = 1.0f / 60.0f;
	static D3DXVECTOR3 gravity(0.0f, -9.8f, 0.0f);
	D3DXVECTOR3 addGravity = gravity;
	addGravity *= (deltaTime);
	m_moveSpeed += (addGravity);
	D3DXVECTOR3 addPos;
	addPos = m_moveSpeed;
	addPos *= (deltaTime);
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

	

	//XZ���ʂ𒲂ׂ�B
	{
		int loopCount = 0;
		while (true) {
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
			D3DXVECTOR3 newPos;
			SweepResultWall callback;
			D3DXVECTOR3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (D3DXVec3Length(&addPosXZ) > 0.0001f) {
				newPos = (m_position += addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
				g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
			}
			if (callback.isHit) {
				//���������B
				//�ǁB
				addPos.x = callback.hitPos.x - m_position.x;
				addPos.z = callback.hitPos.z - m_position.z;

				D3DXVECTOR3 t;
				t.x = -addPos.x;
				t.y = 0.0f;
				t.z = -addPos.z;
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				//���a�������߂��B
				t *= m_radius;
				addPos += t;
				//�����ĕǂɉ����Ċ��点��B
				//���点��������v�Z�B
				D3DXVec3Cross(&t , &callback.hitNormalXZ, &Up);
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				t *= D3DXVec3Dot(&t, &addPosXZ);
				addPos += t;	//���点��x�N�g�������Z�B
			}
			else {
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
				break;
			}
			loopCount++;
			if (loopCount == 5) {
				break;
			}
		}
	}
	//�������𒲂ׂ�B
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		start.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
		D3DXVECTOR3 newPos;
		SweepResultGround callback;
		if (fabsf(addPos.y) > 0.0001f) {
			newPos = m_position;
			newPos.y += addPos.y;


			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
		}
		if (callback.isHit) {
			//���������B
			//�n�ʁB
			m_moveSpeed.y = 0.0f;
			addPos.y = callback.hitPos.y - m_position.y;
			addPos.y += m_radius;
		}
	}

	m_position += addPos;

	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();

	m_rigidBody->getWorldTransform().setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

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
	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//�E
	{
		m_moveSpeed.x = 4.0f;
	//	m_position.x += 0.2f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//��
	{
		m_moveSpeed.x = -4.0f;
	//m_position.x -= 0.2f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//��
	{
		m_moveSpeed.y = 4.0f;
	//	m_position.y += 0.2f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//��
	{
		m_moveSpeed.y = -4.0f;
	//	m_position.y -= 0.2f;
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