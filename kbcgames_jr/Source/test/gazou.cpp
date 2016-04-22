#include"gazou.h"

void Cgazou::Initialize()
{
	m_2Dobj.Initialize("Texture\\ClearBack.jpg");
	vec3Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vec3Trans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vec3Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Cgazou::Update()
{

}

void Cgazou::Draw()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, vec3Scale.x, vec3Scale.y, vec3Scale.z);
	D3DXMatrixTranslation(&matTrans, vec3Trans.x, vec3Trans.y, vec3Trans.z);
	matWorld = matWorld * matScale * /*matRot **/ matTrans;
	m_2Dobj.Draw(matWorld);
}