#include "GameCursor3D.h"
#include"..\Frame\Stage\CStageManager.h"

CGameCursor3D::~CGameCursor3D()
{
}

void CGameCursor3D::Initialize()
{
	m_SkinModel.Initialize("XFile\\Cursor3D.x");
	m_SkinModel.SetLuminance(true,0.2);

	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	state = nonselect;
}

void CGameCursor3D::Update()
{

	Move();//移動

}

void CGameCursor3D::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	if (state == select)//もし選択状態なら
	{
		//ビルボード
		D3DXMATRIX mat;
		D3DXMatrixInverse(&mat, NULL, &view);
		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
		m_SkinModel.Draw(mat * m_matWorld, view, proj,m_matRot);//回転してから
	}
	
}

void CGameCursor3D::Move()
{
	Ccamera* cam = STAGEMANEGER->GetStage()->GetCamera();
	D3DXMATRIX mCam = cam->GetViewMatrix();
	//カメラ行列を逆行列にすると、カメラのワールド行列になる。
	D3DXMatrixInverse(&mCam, NULL, &mCam);
	//Z座標
	D3DXVECTOR3 zAxisInCamera;
	zAxisInCamera.x = mCam.m[2][0];
	zAxisInCamera.y = mCam.m[2][1];
	zAxisInCamera.z = mCam.m[2][2];
	zAxisInCamera.y = 0.0f;
	D3DXVec3Normalize(&zAxisInCamera, &zAxisInCamera);

	//X座標
	D3DXVECTOR3 xAxisInCamera;
	xAxisInCamera.x = mCam.m[0][0];
	xAxisInCamera.y = mCam.m[0][1];
	xAxisInCamera.z = mCam.m[0][2];
	xAxisInCamera.y = 0.0f;
	D3DXVec3Normalize(&xAxisInCamera, &xAxisInCamera);

	//X座標
	D3DXVECTOR3 yAxisInCamera;
	yAxisInCamera.x = mCam.m[1][0];
	yAxisInCamera.y = mCam.m[1][1];
	yAxisInCamera.z = mCam.m[1][2];
	yAxisInCamera.x = 0.0f;
	yAxisInCamera.z = 0.0f;
	D3DXVec3Normalize(&yAxisInCamera, &yAxisInCamera);

	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	const float MOVE_SPEED = 0.2f;
	const float LENGTH = 20.0f;
	GAMEPAD(CGamepad)->UpdateControllerState();

	D3DXVECTOR3 add(0.0f, 0.0f, 0.0f);


	if (GAMEPAD(CGamepad)->GetTriggerL() > 128)
	{
		if (KEYDOWN(diks, DIK_UP) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() > 0)//上
		{
			add += yAxisInCamera * MOVE_SPEED;
		}
		if (KEYDOWN(diks, DIK_DOWN) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() < 0)//下
		{
			add -= yAxisInCamera * MOVE_SPEED;
		}
	}
	else
	{
		if (KEYDOWN(diks, DIK_RIGHT) & 0x80 || GAMEPAD(CGamepad)->GetStickL_X() > 0)//右
		{
			add += xAxisInCamera * MOVE_SPEED;
		}
		if (KEYDOWN(diks, DIK_UP) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() > 0)//奥
		{
			add += zAxisInCamera * MOVE_SPEED;
		}
		if (KEYDOWN(diks, DIK_LEFT) & 0x80 || GAMEPAD(CGamepad)->GetStickL_X() < 0)//左
		{
			add -= xAxisInCamera * MOVE_SPEED;
		}
		if (KEYDOWN(diks, DIK_DOWN) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() < 0)//手前
		{
			add -= zAxisInCamera * MOVE_SPEED;
		}
		else
		{
			(*GetKeyDevice()).Acquire();//キーデバイス取得
		}
	}
	

	m_position += add;

	D3DXVECTOR3 v;
	v = m_position - STAGEMANEGER->GetStage()->GetPlayer()->GetPosition();
	float length;
	length = D3DXVec3Length(&v);
	if (length >= LENGTH)
	{
		D3DXVec3Normalize(&v, &v);
		v *= LENGTH;
		m_position = STAGEMANEGER->GetStage()->GetPlayer()->GetPosition() + v;
	}
}