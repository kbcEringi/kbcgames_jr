#include"Ccamera.h"
#include"..\Game\CGameFlg.h"
#include"GraphicsDevice.h"
#include"haba.h"

extern D3DXMATRIX viewMatrixRotInv;

void Ccamera::Initialize()
{
	m_vEyePt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_v3DNormal = D3DXVECTOR3(-0.5f, 0.5f, -1.0f);
	D3DXVec3Normalize(&m_NormalizeObject, &m_NormalizeObject);
	m_Distance = 7.0f;
	m_vFovy = D3DXToRadian(45.0f);
	m_vAspect = 960.0f / 580.0f;
	m_vNear = 1.0f;
	m_vFar = 1000.0f;
	Volume = DEFAULT_VOLUME;
	targetVolume = DEFAULT_VOLUME;
	m_viewVolumeW = Volume * m_vAspect;
	m_viewVolumeH = Volume;
	flg = !(GAMEFLG->Getflg());
	if (GAMEFLG->Getflg())
	{
		this->Set2DProj();
	}
	else
	{
		this->Set3DProj();
	}
}

void Ccamera::Update()
{
	m_vEyePt = m_NormalizeObject * m_Distance + m_vLookatPt;

	TargetVolume();

	D3DXVECTOR3 zaxis;//注視点から視点への方向（正規化）
	D3DXVec3Normalize(&zaxis, &D3DXVECTOR3(m_vLookatPt - m_vEyePt));
	D3DXVECTOR3 xaxis;//その方向と上方向の外積（正規化）
	D3DXVec3Normalize(&xaxis, D3DXVec3Cross(&xaxis, &m_vUpVec, &zaxis));
	D3DXVECTOR3 yaxis;//以上二つの外積
	D3DXVec3Cross(&yaxis, &zaxis, &xaxis);
	m_viewMatrix = D3DXMATRIX(
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-D3DXVec3Dot(&xaxis, &m_vEyePt), -D3DXVec3Dot(&yaxis, &m_vEyePt), -D3DXVec3Dot(&zaxis, &m_vEyePt), 1);

	D3DXMatrixInverse(&m_viewMatrixRotInv, NULL, &m_viewMatrix);
	m_RotationMatrix = m_viewMatrixRotInv;
	m_RotationMatrix.m[3][0] = 0.0f;
	m_RotationMatrix.m[3][1] = 0.0f;
	m_RotationMatrix.m[3][2] = 0.0f;
	m_RotationMatrix.m[3][3] = 1.0f;
	D3DXMatrixTranspose(&viewMatrixRotInv, &m_RotationMatrix);
}


//============================================================
//対象物を中心に横に回転します。
//============================================================
void Ccamera::RotTransversal(float roty)
{
	D3DXMATRIX tmp;
	D3DXMatrixRotationY(&tmp, roty);
	D3DXVec3TransformCoord(&m_NormalizeObject, &m_NormalizeObject, &tmp);
}

//============================================================
//対象物を中心に縦に回転します。
//============================================================
void Ccamera::RotLongitudinal(float rotx)
{
	D3DXQUATERNION qua;
	D3DXMATRIX tmp;
	D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-m_NormalizeObject.z,0,m_NormalizeObject.x), rotx);
	D3DXMatrixRotationQuaternion(&tmp, &qua);
	D3DXVec3TransformCoord(&m_NormalizeObject, &m_NormalizeObject, &tmp);
}

void Ccamera::TargetVolume()
{
	const float VOL = 0.5f;
	if (Volume < targetVolume)
	{
		Volume += VOL;
	}
	if (targetVolume < Volume)
	{
		Volume -= VOL;
	}
	if (flg == true)
	{
		m_viewVolumeW = Volume * m_vAspect;
		m_viewVolumeH = Volume;
		D3DXMatrixOrthoLH(&m_projectionMatrix, m_viewVolumeW, m_viewVolumeH, m_vNear, m_vFar);
	}
}
