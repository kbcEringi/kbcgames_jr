#include "CStage.h"

CShadowMap g_Shadow;

CStage::CStage()
{
	GAMEFLG->Set3D();
}
void CStage::Initialize()
{
	isButtomTriger = false;		//ボタンが押されているか？
	
}
void CStage::ExecuteChangeCamera(int araySize2D, int araySize3D)
{
	if (!(GAMEFLG->Getflg()))
	{
		if (GAMEPAD(CGamepad)->GetStickR_X() > 0)
		{
			m_camera.RotTransversal(-0.05f);
		}
		if (GAMEPAD(CGamepad)->GetStickR_X() < 0)
		{
			m_camera.RotTransversal(0.05f);
		}
	}
	if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_LEFT_SHOULDER) && !GAMEFLG->Getflg())
	{
		GAMEFLG->Set2D();
		m_camera.Set2DProj();
		Remove3DRigidBody(araySize3D);
		Add2DRigidBody(araySize2D);
	}
	if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_RIGHT_SHOULDER) && GAMEFLG->Getflg())
	{
		GAMEFLG->Set3D();
		m_camera.Set3DProj();
		Remove2DRigidBody(araySize2D);
		Add3DRigidBody(araySize3D);
	}
}

void CStage::Update()
{
	if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B))
	{
		if (GAMEFLG->Getflg() == true)
		{
			if (isButtomTriger == false)
			{
				m_GCursorWind.SetPosition(m_Player.GetPosition());
				m_GameCursor3D.SetPos(m_Player.GetPosition());
				isButtomTriger = true;
			}
			m_camera.SetLookat(m_Player.GetPosition());//Playerを追いかけるカメラ
		}
		else
		{
			if (isButtomTriger == false)
			{
				m_GCursorWind.SetPosition(m_Player.GetPosition());
				m_GameCursor3D.SetPos(m_Player.GetPosition());
				isButtomTriger = true;
			}
			m_camera.SetLookat(m_GameCursor3D.GetPos());//Playerを追いかけるカメラ
		}
	}
	else
	{
		isButtomTriger = false;
		m_camera.SetLookat(m_Player.GetPosition());//Playerを追いかけるカメラ
	}
}

void CStage::Draw()
{

}


void CStage::Add2DRigidBody(int arraySize)//ワールドに追加。
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
		}
	}
}

void CStage::Add3DRigidBody(int arraySize)//ワールドに追加。
{
	if (!m_isAdd3DCollision){
		m_isAdd3DCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody3D[i]);
		}
	}
}

void CStage::Remove2DRigidBody(int arraySize)//ワールドから削除
{
	if (m_isAdd2DCollision){
		m_isAdd2DCollision = false;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			if (m_rigidBody2D[i] != NULL)
				g_bulletPhysics.RemoveRigidBody(m_rigidBody2D[i]);
		}
	}
}

void CStage::Remove3DRigidBody(int arraySize)//ワールドから削除
{
	if (m_isAdd3DCollision){
		m_isAdd3DCollision = false;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			if (m_rigidBody3D[i] != NULL)
				g_bulletPhysics.RemoveRigidBody(m_rigidBody3D[i]);
		}
	}
}