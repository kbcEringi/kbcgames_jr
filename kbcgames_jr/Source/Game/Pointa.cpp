#include "Pointa.h"

CPointa::CPointa()
{

}

CPointa::~CPointa()
{

}

void CPointa::Initialize()
{
	Obj.Initialize("XFile\\Pointa.x");	//�ۂ���X�t�@�C��
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X���W
	m_position.y = 5.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W

	m_moveSpeed.x = 0.0f;				//X���W
	m_moveSpeed.y = 5.0f;				//Y���W
	m_moveSpeed.z = 0.0f;				//Z���W
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);


}

void CPointa::Update()
{
	Move();//�ړ��֐�

}

void CPointa::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPointa::Move()//�ړ�
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);

	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//�E
	{
		m_position.x += 0.1f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//��
	{
		m_position.x -= 0.1f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//��
	{
		m_position.y += 0.1f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//��
	{
		m_position.y -= 0.1f;
	}
	else
	{
		(*GetKeyDevice()).Acquire();//�L�[�f�o�C�X�擾
	}
	
}
