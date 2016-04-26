#include"camera.h"
#include"GraphicsDevice.h"


//==========================================
//CCameraクラスのコンストラクタ				
//機能：m_Distance
//		m_Base								
//		m_Up									
//		m_NormalizeObjectの初期化									
//==========================================
CCamera::CCamera()
{
	m_Distance = 5.0f;
	m_Base = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_NormalizeObject = D3DXVECTOR3(0.0f, 0.0f, -2.0f);
}

//====================================
//デストラクタ
//====================================
CCamera::~CCamera()
{

}

//===================================
//Initialize
//===================================
HRESULT CCamera::Initialize()
{
	if (this->Update() != S_OK)
	{
		return E_FAIL;
	}
	return S_OK;
}


//===================================
//Update
//===================================
HRESULT CCamera::Update()
{
	D3DXVec3Scale(&m_Object, &m_NormalizeObject, m_Distance);
	D3DXVec3Add(&m_Object, &m_Object, &m_Base);
	
	//2D視点
	if (GetAsyncKeyState('A'))
		m_NormalizeObject = D3DXVECTOR3(0.0f, 0.0f, -2.0f);
	//3D視点
	if (GetAsyncKeyState('D'))
		m_NormalizeObject = D3DXVECTOR3(-2.0f, 0.5f, 0.0f);

	return SetView(m_Object, m_Base, m_Up);
}


//======================================
//SetView
//機能：ビュー行列の設定
//引数：カメラの位置,視点,上方向
//返値：S_OK
//======================================
HRESULT CCamera::SetView(D3DXVECTOR3 &eye, D3DXVECTOR3 &at, D3DXVECTOR3 &up)
{
	
	m_Eye = eye;
	m_At = at;
	m_Up = up;
	D3DXMatrixLookAtLH(&m_View, &m_Eye, &m_At, &m_Up);
	(*graphicsDevice()).SetTransform(D3DTS_VIEW, &m_View);
	return S_OK;
}

//============================================================
//カメラと対象物の距離をSet
//============================================================
HRESULT CCamera::SetDistance(float fDistance)
{
	m_Distance = fDistance;
	return Update();
}



//============================================================
//対象物を中心に横に回転します。
//============================================================
HRESULT CCamera::RotTransversal(float roty)
{
	D3DXMATRIX tmp;
	D3DXMatrixRotationY(&tmp, roty);
	D3DXVec3TransformCoord(&m_NormalizeObject, &m_NormalizeObject, &tmp);
	return Update();
}

//============================================================
//対象物を中心に縦に回転します。
//============================================================
HRESULT CCamera::RotLongitudinal(float rotx)
{
	D3DXQUATERNION qua;
	D3DXMATRIX tmp;
	D3DXMatrixRotationX(&tmp, rotx);
	D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-m_NormalizeObject.z, 0, m_NormalizeObject.x), rotx);
	D3DXMatrixRotationQuaternion(&tmp, &qua);
	D3DXVec3TransformCoord(&m_NormalizeObject, &m_NormalizeObject, &tmp);
	return Update();
}

HRESULT CCamera::SerBase(D3DXVECTOR3 vec3Trans)
{
	m_Base.x = vec3Trans.x;
	m_Base.y = vec3Trans.y;
	m_Base.z = vec3Trans.z;
	return Update();
}