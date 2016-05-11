#include"Ccamera.h"

void Ccamera::Initialize()
{
	m_vEyePt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_NormalizeObject = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_Distance = 10.0f;
	m_vFovy = D3DXToRadian(45.0f);
	m_vAspect = 960.0f / 580.0f;
	m_vNear = 1.0f;
	m_vFar = 100.0f;
}

void Ccamera::Update()
{
	m_vEyePt = m_NormalizeObject * m_Distance + m_vLookatPt;

	D3DXVECTOR3 zaxis;//�����_���王�_�ւ̕����i���K���j
	D3DXVec3Normalize(&zaxis, &D3DXVECTOR3(m_vLookatPt - m_vEyePt));
	D3DXVECTOR3 xaxis;//���̕����Ə�����̊O�ρi���K���j
	D3DXVec3Normalize(&xaxis, D3DXVec3Cross(&xaxis, &m_vUpVec, &zaxis));
	D3DXVECTOR3 yaxis;//�ȏ��̊O��
	D3DXVec3Cross(&yaxis, &zaxis, &xaxis);
	m_viewMatrix = D3DXMATRIX(
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-D3DXVec3Dot(&xaxis, &m_vEyePt),-D3DXVec3Dot(&yaxis, &m_vEyePt),-D3DXVec3Dot(&zaxis, &m_vEyePt), 1);
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
}


//============================================================
//�Ώە��𒆐S�ɉ��ɉ�]���܂��B
//============================================================
void Ccamera::RotTransversal(float roty)
{
	D3DXMATRIX tmp;
	D3DXMatrixRotationY(&tmp, roty);
	D3DXVec3TransformCoord(&m_NormalizeObject, &m_NormalizeObject, &tmp);
}

//============================================================
//�Ώە��𒆐S�ɏc�ɉ�]���܂��B
//============================================================
void Ccamera::RotLongitudinal(float rotx)
{
	D3DXQUATERNION qua;
	D3DXMATRIX tmp;
	D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-m_NormalizeObject.z,0,m_NormalizeObject.x), rotx);
	D3DXMatrixRotationQuaternion(&tmp, &qua);
	D3DXVec3TransformCoord(&m_NormalizeObject, &m_NormalizeObject, &tmp);
}


//void Ccamera::Initialize()
//{
//	m_vEyePt = D3DXVECTOR3(0.0f, 3.0f, -5.0f);
//	m_vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_vFovy = D3DXToRadian(45.0f);
//	m_vAspect = 1.0f;
//	m_vNear = 1.0f;
//	m_vFar = 100.0f;
//}
//
//void Ccamera::Update()
//{
//	D3DXVECTOR3 zaxis;//�����_���王�_�ւ̕����i���K���j
//	D3DXVec3Normalize(&zaxis, &D3DXVECTOR3(m_vLookatPt - m_vEyePt));
//	D3DXVECTOR3 xaxis;//���̕����Ə�����̊O�ρi���K���j
//	D3DXVec3Normalize(&xaxis, D3DXVec3Cross(&xaxis, &m_vUpVec, &zaxis));
//	D3DXVECTOR3 yaxis;//�ȏ��̊O��
//	D3DXVec3Cross(&yaxis, &zaxis, &xaxis);
//	m_viewMatrix = D3DXMATRIX(
//		xaxis.x, yaxis.x, zaxis.x, 0,
//		xaxis.y, yaxis.y, zaxis.y, 0,
//		xaxis.z, yaxis.z, zaxis.z, 0,
//		-D3DXVec3Dot(&xaxis, &m_vEyePt), -D3DXVec3Dot(&yaxis, &m_vEyePt), -D3DXVec3Dot(&zaxis, &m_vEyePt), 1);
//	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_vFovy, m_vAspect, m_vNear, m_vFar);
//}